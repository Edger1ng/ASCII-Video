import argparse
import sys
import time
from typing import Iterable, List, Sequence

import cv2
import numpy as np
from colorama import Style, init as colorama_init

# Ensure ANSI escape codes are reset properly on exit
colorama_init()

ASCII_GRADIENT = " .:-=+*#%@"
HIGH_CONTRAST_GRADIENT = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"


class FrameCache:
    def __init__(self, optimize: bool):
        self.optimize = optimize
        self.frames: List[np.ndarray] = []

    def load(self, capture: cv2.VideoCapture) -> None:
        if not self.optimize:
            return
        success, frame = capture.read()
        while success:
            self.frames.append(frame)
            success, frame = capture.read()

    def __iter__(self) -> Iterable[np.ndarray]:
        return iter(self.frames)

    def __len__(self) -> int:  # pragma: no cover - convenience
        return len(self.frames)


def parse_args(argv: Sequence[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Render a video as colorful ASCII in the terminal.")
    parser.add_argument("--file", required=True, help="Path to the input video file")
    parser.add_argument("--mode", default="enhanced-rgb", choices=[
        "enhanced-rgb",
        "mid-rgb",
        "low-rgb",
        "bw",
        "enhanced-bw",
    ], help="Rendering mode")
    parser.add_argument("--fps", type=float, default=30.0, help="Target playback FPS")
    parser.add_argument("--width", type=int, default=120, help="Frame width in characters")
    parser.add_argument("--height", type=int, default=40, help="Frame height in characters")
    parser.add_argument("--optimize", action="store_true", help="Pre-cache frames for smoother playback")
    parser.add_argument("--charset", default=ASCII_GRADIENT, help="Custom characters to use for shading")
    parser.add_argument("--invert", action="store_true", help="Invert the intensity mapping")
    parser.add_argument("--start", type=int, default=0, help="Start rendering from this frame number")
    parser.add_argument("--frames", type=int, default=0, help="Limit playback to this many frames (0 = all)")
    parser.add_argument("--no-color", action="store_true", help="Force grayscale even in RGB modes")
    parser.add_argument("--downscale", type=float, default=1.0, help="Additional downscale factor for performance")
    parser.add_argument("--show-info", action="store_true", help="Show FPS counter and progress")
    return parser.parse_args(argv)


def quantize_color(frame: np.ndarray, mode: str) -> np.ndarray:
    if mode == "enhanced-rgb":
        return frame
    if mode == "mid-rgb":
        return (frame // 32) * 32
    if mode == "low-rgb":
        return (frame // 64) * 64
    return frame


def intensity_map(gray: np.ndarray, charset: str, invert: bool) -> np.ndarray:
    gradient = charset
    indices = (gray.astype(np.float32) / 255.0) * (len(gradient) - 1)
    if invert:
        indices = (len(gradient) - 1) - indices
    return indices.astype(np.int16)


def frame_to_ascii(frame: np.ndarray, mode: str, width: int, height: int, charset: str, invert: bool, use_color: bool) -> str:
    # Downscale first for speed
    resized = cv2.resize(frame, (width, height), interpolation=cv2.INTER_AREA)
    gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
    if mode == "enhanced-bw":
        gray = cv2.equalizeHist(gray)
        gradient = HIGH_CONTRAST_GRADIENT
    else:
        gradient = charset

    idx = intensity_map(gray, gradient, invert)
    chars = np.array(list(gradient))[idx]

    if not use_color or mode in {"bw", "enhanced-bw"}:
        lines = ["".join(row.tolist()) for row in chars]
        return "\n".join(lines)

    colored = quantize_color(resized, mode)
    flat_chars = chars.reshape(-1)
    flat_colors = colored.reshape(-1, 3)
    fragments: List[str] = []
    for (b, g, r), ch in zip(flat_colors, flat_chars):
        fragments.append(f"\033[38;2;{r};{g};{b}m{ch}")
    lines = []
    for y in range(height):
        start = y * width
        end = start + width
        lines.append("".join(fragments[start:end]) + Style.RESET_ALL)
    return "\n".join(lines)


def render_video(options: argparse.Namespace) -> None:
    capture = cv2.VideoCapture(options.file)
    if not capture.isOpened():
        raise SystemExit(f"Could not open video file: {options.file}")

    total_frames = int(capture.get(cv2.CAP_PROP_FRAME_COUNT))
    target_interval = 1.0 / max(options.fps, 1e-3)
    charset = options.charset

    cache = FrameCache(options.optimize)
    if options.optimize:
        capture.set(cv2.CAP_PROP_POS_FRAMES, options.start)
        cache.load(capture)
        frames_iter: Iterable[np.ndarray] = cache
    else:
        capture.set(cv2.CAP_PROP_POS_FRAMES, options.start)
        frames_iter = iter(lambda: capture.read()[1] if capture.isOpened() else None, None)

    processed = 0
    start_time = time.perf_counter()
    for frame in frames_iter:
        if frame is None:
            break
        processed += 1
        if options.frames and processed > options.frames:
            break

        ascii_frame = frame_to_ascii(
            frame,
            mode=options.mode,
            width=max(4, int(options.width / options.downscale)),
            height=max(2, int(options.height / options.downscale)),
            charset=charset,
            invert=options.invert,
            use_color=not options.no_color,
        )

        frame_start = time.perf_counter()
        sys.stdout.write("\033[H\033[J")
        sys.stdout.write(ascii_frame)
        if options.show_info:
            elapsed = time.perf_counter() - start_time
            fps = processed / elapsed if elapsed > 0 else 0.0
            sys.stdout.write(
                f"\n[✓] Frame: {processed} / {options.frames or total_frames} | FPS: {fps:5.1f} | Elapsed: {elapsed:6.2f}s\n"
            )
        sys.stdout.flush()

        spent = time.perf_counter() - frame_start
        delay = target_interval - spent
        if delay > 0:
            time.sleep(delay)

    capture.release()


if __name__ == "__main__":
    opts = parse_args(sys.argv[1:])
    render_video(opts)
