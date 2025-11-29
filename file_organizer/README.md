# 📁 File Organizer

A tiny, self-contained CLI tool that tidies up any directory by moving files into sub-folders based on their extensions.  
No installation frenzy—just **one source file**, **one header**, **one config file**, and **CMake**.

## ✨ What it does

```text
Downloads/
├─ thesis.pdf        →  Documents/thesis.pdf
├─ holiday.jpg       →  Images/holiday.jpg
├─ soundtrack.mp3    →  Music/soundtrack.mp3
└─ random.txt        →  Documents/random.txt
```

Dry-run first, flip the switch when you're happy.

## 🎌 Command-line flags

| Flag           | Meaning                                  |
| -------------- | ---------------------------------------- |
| `-d` `--dry`   | **Preview** mode – nothing is moved.     |
| `-v` `--verbose` | **Chatty** mode – print each move.       |

They can be placed anywhere:  
`./organizer -v -d ~/Pictures`

## ⚙️ Customize categories

Edit `categories.json` (same folder as the binary):

```json
{
  "Documents": [".pdf", ".doc", ".docx", ".txt", ".md"],
  "Images":    [".jpg", ".jpeg", ".png", ".gif", ".bmp"],
  "Videos":    [".mp4", ".avi", ".mov", ".mkv"],
  "Music":     [".mp3", ".wav", ".flac"],
  "Misc":      []
}
```

*Add, delete or reorder as you like—no recompile needed.*

## 🛠️ Build manually

```bash
./build.sh
```

CMake ≥ 3.14 and a C++17 compiler are the only requirements.  
The header `json.hpp` is downloaded automatically if missing.

## 📚 File tree

```text
.
├── CMakeLists.txt      # pulls json.hpp if absent
├── organizer.cpp       # all logic in one file
├── categories.json     # editable extension map
├── build.sh            # one-touch build script
└── build/              # generated binaries
```

## 🧪 Example session

```bash
$ ./organizer -d ~/Pictures
[dry] would move: "DSC0001.jpg"  ->  "./Images/DSC0001.jpg"
[dry] would move: "clip.mkv"     ->  "./Videos/clip.mkv"

$ ./organizer -v ~/Pictures
moved: DSC0001.jpg
moved: clip.mkv
```

## 🙋‍♂️ License

MIT – do what you want, just keep the credit line.