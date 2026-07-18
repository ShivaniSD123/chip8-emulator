# 🎮 CHIP-8 Emulator

A CHIP-8 Emulator built in **C++** using **SDL2** for graphics, keyboard input, and audio.

This project emulates the original CHIP-8 virtual machine, supporting instruction execution, sprite rendering, keypad input, delay timers, and sound timers.

---

## ✨ Features

* ✅ Complete CHIP-8 CPU implementation
* ✅ 35 CHIP-8 instructions
* ✅ 4 KB memory
* ✅ 16 general-purpose registers (V0-VF)
* ✅ Stack and subroutine support
* ✅ Delay Timer (60 Hz)
* ✅ Sound Timer (60 Hz)
* ✅ 64×32 monochrome display
* ✅ SDL2-based rendering
* ✅ Hexadecimal keypad input
* ✅ ROM loading support
* ✅ Sprite collision detection

---

## 🏗️ Architecture

| Component      | Specification         |
| -------------- | --------------------- |
| Memory         | 4096 Bytes            |
| Registers      | V0-VF                 |
| Index Register | I                     |
| Stack          | 16 Levels             |
| Display        | 64 × 32               |
| Keyboard       | 16 Keys               |
| Timers         | Delay (60 Hz) |

---

## 📁 Project Structure

```text
chip8-emulator/
│
├── src/
│   ├── chip8.cpp
│   ├── chip8.hpp
│   ├── renderer.cpp
│   ├── renderer.hpp
│   ├── keypad.cpp
│   ├── keypad.hpp
│   ├── audio.cpp
│   ├── audio.hpp
│   └── main.cpp
│
├── roms/
├── assets/
├── CMakeLists.txt
└── README.md
```

## 🎮 Key Mapping

```text
CHIP-8        Keyboard

1 2 3 C       1 2 3 4
4 5 6 D  -->  Q W E R
7 8 9 E       A S D F
A 0 B F       Z X C V
```

---

## ⚙️ Build Instructions

### Linux

```bash
mkdir build
cd build
cmake ..
make
./chip8
```

### macOS

```bash
brew install sdl2

mkdir build
cd build
cmake ..
make
./chip8
```

---

## 🚀 Running a ROM

```bash
./chip8 roms/PONG.ch8
```

---

## 🔄 Emulation Cycle

1. Fetch Opcode
2. Decode Opcode
3. Execute Instruction
4. Update Timers
5. Handle Input
6. Render Display

---

## 📸 Screenshots

### Space Invaders

![Space Invaders Screenshot](/Users/shivanidwivedi/Desktop/SpaceInvaders1.png)

### IBM Logo

![IBM Logo](/Users/shivanidwivedi/Desktop/IBM.png)

---

## 📚 What I Learned

* Emulator Development
* CPU Instruction Decoding
* Memory Management
* Bitwise Operations
* SDL2 Graphics Programming
* Keyboard Event Handling
* Real-Time Timing

---

## 🔮 Future Improvements

* Super CHIP-8 Support
* Save States
* Debugger
* Instruction Tracing
* Adjustable CPU Frequency
* ROM Browser

---


## 👨‍💻 Author

**Shivani Dwivedi**

Built as a learning project to explore emulator development and low-level system design.

⭐ If you found this project interesting, consider giving it a star!
