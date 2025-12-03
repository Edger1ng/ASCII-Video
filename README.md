# 🎮 ASCII Video Player

A cross-platform console-based video player that renders each frame as ASCII art. Now ships with Python **and C++17** implementations, performance-minded frame caching, enhanced gradients, and richer CLI controls.

---

## 🔧 Features

* 🎨 Color and grayscale rendering modes
* 📐 Adjustable resolution and framerate
* 🎞️ ASCII rendering with customizable detail level
* 🚀 Optimized mode to pre-cache frames for smoother playback
* 💻 Implemented in both **C# (.NET 8)** and **Python 3**

---

## 🚀 C++ Usage

### Build

```bash
cd cpp
cmake -S . -B build
cmake --build build --config Release
```

### Run

```bash
./cpp/build/ascii_video_player --file video.mp4 --mode enhanced-rgb --fps 60 --width 120 --height 40 --optimize --show-info
```

---

## 🧪 Command Line Arguments (Python & C++)

| Argument       | Description                                                                               |
| -------------- | ----------------------------------------------------------------------------------------- |
| `--file`       | Path to the input video file                                                              |
| `--mode`       | Rendering mode: `enhanced-rgb`, `mid-rgb`, `low-rgb`, `bw`, `enhanced-bw`                 |
| `--fps`        | Playback framerate                                                                        |
| `--width`      | Frame width (in characters)                                                               |
| `--height`     | Frame height (in characters)                                                              |
| `--optimize`   | Cache frames into memory for smoother playback                                            |
| `--charset`    | Custom character set for shading (defaults to balanced gradient)                          |
| `--invert`     | Invert the intensity mapping                                                              |
| `--start`      | Start rendering from this frame number                                                    |
| `--frames`     | Stop after rendering this many frames (0 = all)                                           |
| `--no-color`   | Force grayscale output even in RGB modes                                                  |
| `--downscale`  | Additional downscale factor to speed up rendering                                         |
| `--show-info`  | Show live FPS counter and progress information                                            |

### 🔹 Example 1: Basic Grayscale Playback

```bash
AsciiVideoPlayer.exe --file sample.mp4 --mode bw --width 100 --height 30
```

*Use this to render old black-and-white films or stylized videos in terminal.*

### 🔹 Example 2: Optimized Full-Color Playback

```bash
AsciiVideoPlayer.exe --file clip.mp4 --mode enhanced-rgb --fps 60 --optimize
```

*This mode is ideal for vibrant, fast-paced content and ensures smooth frame transitions.*

### 🔹 Example 3: Medium-Resolution RGB Playback

```bash
AsciiVideoPlayer.exe --file trailer.mp4 --mode mid-rgb --width 80 --height 24
```

*A good balance between detail and speed. Recommended for limited terminal sizes.*

### 🔹 Example 4: Low-Color Mode for Performance

```bash
AsciiVideoPlayer.exe --file musicvideo.mp4 --mode low-rgb --fps 30
```

*Use this on older machines or when prioritizing speed over quality.*

---

## 🖼️ Screenshots / Previews


![Color Mode Preview](assets/color_preview.png)

![Grayscale Terminal Screenshot](assets/bw_preview.png)

![Playback Info](assets/terminal_info.png)

Coming soon!


---

## 🐍 Python Version

The Python implementation mirrors the C++ features and adds quick prototyping convenience.

### ▶️ Python Usage

```bash
python ascii_video_player.py --file video.mp4 --mode enhanced-rgb --fps 60 --width 120 --height 40 --optimize --show-info
```

It uses OpenCV and `colorama` to render video frames as colorful ASCII blocks in the terminal. Use `--downscale 1.5` or `--no-color` to squeeze extra performance out of slower terminals.

---

## 📦 Dependencies

### C++ Version:

* [OpenCV](https://opencv.org/) (development headers)

### Python Version:

* `opencv-python`
* `colorama`

Install with:

```bash
pip install opencv-python colorama
```

---

## 💡 Example Output

```
                 ......:..:................ .....::::..         ...........::.....::::::..::::::::::..-
                 ...........................:::...:-:::            ........:.::....:::::::::::::::-----
                 .........................:.. . ...:-:--:            ..........::..::::::.::::::::-----
                 ........................  .....:::-:::::.             .......:::..::::::::::::::::::--
                 ..................... . ..::----====-:::--:            .......:::.::::::::::::::::::::
                 .....................:..:-+++++++=====-::---           ...:...::::::.:::::::::::::.
                 ........................-+=++=+++====+-::----.          ....:::::::::.::::::::::.
                 .......................:=====-=+=-::-==-:.----..         .......::::::::.:::::::
                 .......................:========--+===+-. .----. .       ...:::::::::::::::::::::.
                 ........................====-=+=======+==..-----.        ...:.....::::::::::::.:::.
                 ........................-=++++===+====++:-..----.         .::.:::::::::::::::: .:::
                 .......................-=====+=--:-===++=...----:     .   .:::::::.::::::::::...::::
                 .......................===========+=+++-::::--=-:...      .:::::::::::.::::::...:::-
                 ................:.......=+====-.:--=+++:::::====-..  ..   .:::::::::::::::::::..::::
                 .........................:===========++:::::---=:... ..   .:::::::::::::::::::..::::
                 .......................:+++=========+++:::-:-===:....... ...:..::.::::::::::::..:-::
                 .......................++*====-----=+==.:-+*+===:....... ..:::.::::::::::.:::...::::
                 ......................++**:.===-...:=: . ++*++==:.........::::.::::::::::::::...::-:
                 :....................=+***....:===-: .   +++++++++=.......::-::::::::::::::::...::-:
                 ..................::++****:.....         =+++++++++++:....:-:::::::::::::::::..:-:::
                 ::::..:...::::::::+******+-.. ....     ...++++++-++++++=..::::::::::::::::::::.---
                 .::...:::::..:::+*******++: .......... ...++++++++++++++++::::::::::::::::::::.---.
                 .::::.....:.::+**********+==..... ........+++++++-+++++++++:::::::::::::::-::::---.
                 ............:**********++=-+-............-+-==---:-+++++++++::::::::::-:--::::.---.
                 :::::::.:::=***********----*+=+..........:=-=+=+++-+++++++++++--:::------::::-:---..
                 .:::::::::+*********+*********+-.........+--=++++++++-+++*+++++--------::-:-------....
                 :..::.:::***********+*********++ ..... ..==++++-++=++=+++++++=++-----:------------....
                 ...:::.:+***********+*******++++  ..   ...-++++=+++++++++++++=+++----::-------:---....
                 ::::::::**********************++  .    ...-++++==+++++++*++++=+++++-::--------:::-....
                 :::::::*************+**+****++++  .   ....=++++=:++=++=+++++++++++++----------:::.....
                 :::::-*************++**+****++++      ..  -=++++-++-++=++*+++==++=++----:---::........
                 ::::=**************++**+****++++      .   .=++++--+=++=++=+==+++++++-------::-:::-----
                 :::+********#*+****++**+****++++     ..    :++++=:+=++++++++++++++++-----::::::--:....
                 ::+************+***++**+****+++=            +++++-+=+++-+++++++++++++::::-:...........
                 :+*************++**++**+***++++=     .      .++++--==++-++++++++++++++................
                 =******************++**+***++++-             =++=--==++-=+++++++++++++..............::
                 +*****+++++++*+-+**++**++*++=++.             =++==-=-++:+++++++++=+++:..:::...........
                 *******+++***+--+**++**+=++++++.             =+===---++++=++++++=++++...::............
                 ******+++++++**+***++**+=++++++.             =+=-=--=+++++===+++++++:..............
                 +++++*****++==++****+*++=++++++              ===-=-----=========+++=..................
[✓] Playing video as ASCII...
Frame: 137 / 241   |   FPS: 59.8   |   Elapsed: 00:03.2
```

---

## 📜 License

MIT License. Free to use, modify, and share.

---

## ❤️ Credits

Project by Edger1ng. Originally created for fun and experimentation with ASCII rendering and OpenCV.

If you enjoy this, consider leaving a ⭐ on the repo!
