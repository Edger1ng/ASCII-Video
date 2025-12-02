#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>

namespace {
const std::string ASCII_GRADIENT = " .:-=+*#%@";
const std::string HIGH_CONTRAST_GRADIENT =
    " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

struct Options {
    std::string file;
    std::string mode = "enhanced-rgb";
    double fps = 30.0;
    int width = 120;
    int height = 40;
    bool optimize = false;
    bool invert = false;
    bool noColor = false;
    int startFrame = 0;
    int maxFrames = 0;  // 0 = all
    double downscale = 1.0;
    std::string charset = ASCII_GRADIENT;
    bool showInfo = false;
};

Options parseArgs(int argc, char** argv) {
    Options opt;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto nextValue = [&](int& target) {
            if (i + 1 < argc)
                target = std::stoi(argv[++i]);
        };
        auto nextDouble = [&](double& target) {
            if (i + 1 < argc)
                target = std::stod(argv[++i]);
        };
        auto nextString = [&](std::string& target) {
            if (i + 1 < argc)
                target = argv[++i];
        };

        if (arg == "--file") {
            nextString(opt.file);
        } else if (arg == "--mode") {
            nextString(opt.mode);
        } else if (arg == "--fps") {
            nextDouble(opt.fps);
        } else if (arg == "--width") {
            nextValue(opt.width);
        } else if (arg == "--height") {
            nextValue(opt.height);
        } else if (arg == "--optimize") {
            opt.optimize = true;
        } else if (arg == "--invert") {
            opt.invert = true;
        } else if (arg == "--no-color") {
            opt.noColor = true;
        } else if (arg == "--start") {
            nextValue(opt.startFrame);
        } else if (arg == "--frames") {
            nextValue(opt.maxFrames);
        } else if (arg == "--downscale") {
            nextDouble(opt.downscale);
        } else if (arg == "--charset") {
            nextString(opt.charset);
        } else if (arg == "--show-info") {
            opt.showInfo = true;
        }
    }
    return opt;
}

std::string pickGradient(const Options& opt) {
    if (opt.mode == "enhanced-bw") {
        return HIGH_CONTRAST_GRADIENT;
    }
    return opt.charset;
}

cv::Mat quantizeColor(const cv::Mat& frame, const std::string& mode) {
    cv::Mat output;
    if (mode == "mid-rgb") {
        frame.convertTo(output, CV_8UC3);
        output = output / 32 * 32;
    } else if (mode == "low-rgb") {
        frame.convertTo(output, CV_8UC3);
        output = output / 64 * 64;
    } else {
        output = frame.clone();
    }
    return output;
}

std::string frameToAscii(const cv::Mat& frame, const Options& opt) {
    const int targetWidth = std::max(4, static_cast<int>(opt.width / opt.downscale));
    const int targetHeight = std::max(2, static_cast<int>(opt.height / opt.downscale));

    cv::Mat resized;
    cv::resize(frame, resized, cv::Size(targetWidth, targetHeight), 0, 0, cv::INTER_AREA);

    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    if (opt.mode == "enhanced-bw") {
        cv::equalizeHist(gray, gray);
    }

    const std::string gradient = pickGradient(opt);
    const int gradLen = static_cast<int>(gradient.size());

    std::ostringstream oss;

    auto pushAnsi = [&](int r, int g, int b, char ch) {
        oss << "\033[38;2;" << r << ';' << g << ';' << b << 'm' << ch;
    };

    cv::Mat colors = opt.noColor || opt.mode == "bw" || opt.mode == "enhanced-bw"
                         ? cv::Mat()
                         : quantizeColor(resized, opt.mode);

    for (int y = 0; y < gray.rows; ++y) {
        const uchar* row = gray.ptr<uchar>(y);
        const cv::Vec3b* colorRow = colors.empty() ? nullptr : colors.ptr<cv::Vec3b>(y);
        for (int x = 0; x < gray.cols; ++x) {
            float intensity = static_cast<float>(row[x]) / 255.0f;
            if (opt.invert) {
                intensity = 1.0f - intensity;
            }
            int idx = static_cast<int>(intensity * (gradLen - 1));
            idx = std::clamp(idx, 0, gradLen - 1);
            char ch = gradient[idx];
            if (colorRow) {
                const cv::Vec3b& pixel = colorRow[x];
                pushAnsi(pixel[2], pixel[1], pixel[0], ch);
            } else {
                oss << ch;
            }
        }
        if (colorRow) {
            oss << "\033[0m";
        }
        if (y + 1 < gray.rows) {
            oss << '\n';
        }
    }
    return oss.str();
}

std::vector<cv::Mat> loadFrames(cv::VideoCapture& cap, int startFrame) {
    std::vector<cv::Mat> frames;
    cap.set(cv::CAP_PROP_POS_FRAMES, startFrame);
    cv::Mat frame;
    while (cap.read(frame)) {
        frames.push_back(frame.clone());
    }
    return frames;
}

void render(const Options& opt) {
    if (opt.file.empty()) {
        throw std::runtime_error("--file is required");
    }

    cv::VideoCapture cap(opt.file);
    if (!cap.isOpened()) {
        throw std::runtime_error("Could not open video file: " + opt.file);
    }

    const int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    const double targetInterval = 1.0 / std::max(opt.fps, 0.001);

    std::vector<cv::Mat> cached;
    if (opt.optimize) {
        cached = loadFrames(cap, opt.startFrame);
    }

    auto iteratorFrames = [&](auto&& callback) {
        int processed = 0;
        if (!cached.empty()) {
            for (const auto& frame : cached) {
                callback(frame, ++processed);
                if (opt.maxFrames > 0 && processed >= opt.maxFrames)
                    return;
            }
            return;
        }

        cap.set(cv::CAP_PROP_POS_FRAMES, opt.startFrame);
        cv::Mat frame;
        while (cap.read(frame)) {
            callback(frame, ++processed);
            if (opt.maxFrames > 0 && processed >= opt.maxFrames)
                break;
        }
    };

    auto start = std::chrono::steady_clock::now();

    iteratorFrames([&](const cv::Mat& frame, int index) {
        auto frameStart = std::chrono::steady_clock::now();

        std::string ascii = frameToAscii(frame, opt);
        std::cout << "\033[H\033[J" << ascii;
        if (opt.showInfo) {
            auto elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
            double fps = index / std::max(0.0001, elapsed);
            std::cout << "\n[✓] Frame: " << index << " / " << (opt.maxFrames > 0 ? opt.maxFrames : totalFrames)
                      << " | FPS: " << std::fixed << std::setprecision(1) << fps
                      << " | Elapsed: " << std::setprecision(2) << elapsed << "s\n";
        }
        std::cout.flush();

        auto spent = std::chrono::duration<double>(std::chrono::steady_clock::now() - frameStart).count();
        double delay = targetInterval - spent;
        if (delay > 0) {
            std::this_thread::sleep_for(std::chrono::duration<double>(delay));
        }
    });
}
}  // namespace

int main(int argc, char** argv) {
    try {
        Options opt = parseArgs(argc, argv);
        render(opt);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
