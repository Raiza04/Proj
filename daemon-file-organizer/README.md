# 🧹 File Organizer Daemon

A lightweight, invisible C++ background service (daemon) that automatically organizes your messy folders. Set it up once, and it will quietly sort your files into categorized subfolders based on their file extensions.

## ✨ Features

* **👻 Invisible Background Process:** Runs as a true Linux daemon detached from the terminal.
* **⚙️ JSON Configuration:** Easily map file extensions to specific folders.
* **📝 Auto-Logging:** Captures all operations and errors into a dedicated log file.
* **⚡ C++17 Powered:** Fast, efficient, and uses modern filesystem libraries.
* **🛠️ One-Click Build:** Comes with a simple bash script to handle CMake and dependencies automatically.

---

## 📋 Prerequisites

Before you begin, ensure you have the following installed on your system:

* A C++ compiler that supports **C++17** (e.g., `g++` or `clang`)
* **CMake** (version 3.10 or higher)

*(Note: The required `nlohmann/json` library is downloaded automatically during the build process!)*

---

## 🛠️ Configuration (Do this first!)

Before starting the daemon, you need to tell it **where** to look and **how** to sort. Create these two files in your project's root directory:

### 1. `paths.txt` 📂

List the absolute paths of the directories you want the daemon to watch (one path per line).

```text
/home/username/Downloads
/home/username/Desktop/MessyFolder
```

### 2. `extensions.json` 🗂️

Define which file extensions belong in which subfolder.

```json
{
    "Images": [".jpg", ".jpeg", ".png", ".gif"],
    "Documents": [".pdf", ".docx", ".txt"],
    "Archives": [".zip", ".tar", ".gz", ".rar"],
    "Code": [".cpp", ".hpp", ".js", ".py"]
}
```

*(Files with extensions not listed here will be moved to a default "Misc" folder).*

---

## 🚀 How to Build and Run

I made this as idiot-proof as possible. Just open your terminal in the project directory and follow these steps:

*(Note: these steps are for linux system but you can easily find the corresponding command for you system by googling it)*

### Step 1: Make the build script executable (One-time only)

```bash
chmod +x build.sh
```

### Step 2: Build the project

This script will create the build environment, download dependencies, and compile the code.

*(Note: Internet access is required to download necessary libraries)*

```bash
./build.sh
```

### Step 3: Start the Daemon

Run the compiled executable. It will instantly move to the background and return your terminal to you.

```bash
./build/file_daemon
```

🎉 **That's it! Your folders are now being organized automatically.**

---

## 🔍 Monitoring & Logs

Since the program runs invisibly in the background, you won't see terminal outputs. Instead, it writes everything to a log file.

**To see what the daemon is doing in real-time, run:**

```bash
tail -f organizer_daemon.log
```

*(Press `Ctrl + C` to exit the log viewer).*

---

## 🛑 How to Stop the Daemon

Because it's a background process, closing the terminal **will not** stop it. If you need to kill the daemon, use the process ID or kill it by name:

```bash
pkill file_daemon
```

---

## 🔄 Running on System Startup (Optional, Systemd)

If you want this daemon to start automatically every time you turn on your PC:

1. Create a service file: `sudo nano /etc/systemd/system/file_organizer.service`
2. Paste this configuration (Replace `/path/to/your/project` with your actual absolute path!):

```ini
[Unit]
Description=My Custom File Organizer Daemon
After=network.target

[Service]
Type=forking
WorkingDirectory=/path/to/your/project
ExecStart=/path/to/your/project/build/file_daemon
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

3. Enable and start the service:

```bash
sudo systemctl daemon-reload
sudo systemctl enable file_organizer.service
sudo systemctl start file_organizer.service
```