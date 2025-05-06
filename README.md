# Tanchiki Game (Battle City Fan Prototype)

This is an early-stage **fan-made prototype** of a tank game inspired by Namco's classic *Battle City* (1985), developed for the **Sega Mega Drive / Genesis** using **C** and **SGDK (Sega Genesis Development Kit)**.

> ⚠️ **Disclaimer**:
> This project is a non-commercial fan work created for educational and entertainment purposes. It is not affiliated with or endorsed by Namco or Bandai Namco Entertainment. All rights to the original *Battle City* game and its assets belong to their respective copyright holders.

## 🚧 Project Status

The project is in early development.

### ✅ Implemented

* Title screen
* Basic screen transitions

### ❌ Not Yet Implemented

* Gameplay mechanics
* Sound and music
* Menus, scoring, player input

This is **not a complete game**, just a working prototype.

## ▶️ Running the Prototype

1. Download or clone this repository.
2. Go to the `out/` folder.
3. Load `rom.bin` in any Sega Mega Drive / Genesis emulator, such as:

   * [Kega Fusion](https://segaretro.org/Kega_Fusion)
   * [Gens](https://segaretro.org/Gens)
   * [Genesis Plus GX](https://github.com/ekeeke/Genesis-Plus-GX)
   * [BlastEm](https://www.retrodev.com/blastem/)

## 🛠 Building the ROM

To build the project yourself, you’ll need:

* [SGDK (Sega Genesis Development Kit)](https://github.com/Stephane-D/SGDK)
* GCC toolchain for 68k (e.g., `m68k-elf-gcc`)
* Java (required by SGDK tools)
* A build environment (Linux, macOS, or Windows with WSL or compatible shell)

### Build Steps

```bash
git clone https://github.com/Eugene2424/tanchiki-game.git
cd tanchiki-game
make
```

The compiled ROM will appear as `rom.bin` in the `out/` folder.

## 📁 Project Structure

```
tanchiki-game/
├── src/       # C source files
├── inc/       # Header files
├── res/       # Game resources (graphics, palettes, etc.)
├── out/       # Compiled ROM output
├── .vscode/   # Editor settings
├── Makefile
├── README.md
```
