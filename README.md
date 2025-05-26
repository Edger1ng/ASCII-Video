# 🎮 ASCII Video Player

A cross-platform console-based video player that renders each frame as ASCII art. Supports color rendering, FPS customization, frame caching optimization, and more.

---

## 🔧 Features

* 🎨 Color and grayscale rendering modes
* 📐 Adjustable resolution and framerate
* 🎞️ ASCII rendering with customizable detail level
* 🚀 Optimized mode to pre-cache frames for smoother playback
* 💻 Implemented in both **C# (.NET 8)** and **Python 3**

---

## 🚀 C# Usage

```bash
AsciiVideoPlayer.exe --file video.mp4 --mode enhanced-rgb --fps 60 --width 120 --height 40 --optimize
```

---

## 🧪 Command Line Arguments

| Argument     | Description                                                               |
| ------------ | ------------------------------------------------------------------------- |
| `--file`     | Path to the input video file                                              |
| `--mode`     | Rendering mode: `enhanced-rgb`, `mid-rgb`, `low-rgb`, `bw`, `enhanced-bw` |
| `--fps`      | Playback framerate                                                        |
| `--width`    | Frame width (in characters)                                               |
| `--height`   | Frame height (in characters)                                              |
| `--optimize` | Cache frames into memory for optimized playback                           |

### 🔹 Example 1: Basic Grayscale Playback

```bash
AsciiVideoPlayer.exe --file sample.mp4 --mode bw --width 100 --height 30
```

*Use this to render old black-and-white films or stylized videos in terminal.*

### 🔹 Example 2: Optimized Full-Color Playback

```bash
AsciiVideoPlayer.exe --file anime_clip.mp4 --mode enhanced-rgb --fps 60 --optimize
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

The Python implementation is available with identical behavior.

### ▶️ Python Usage

```bash
python ascii_video_player.py --file video.mp4 --mode enhanced-rgb --fps 60 --width 120 --height 40 --optimize
```

It uses OpenCV and `colorama` to render video frames as colorful ASCII blocks in the terminal.

---

## 📦 Dependencies

### C# Version:

* [.NET 8](https://dotnet.microsoft.com)
* [OpenCvSharp4](https://github.com/shimat/opencvsharp)

Install via NuGet:

```bash
Install-Package OpenCvSharp4
```

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
