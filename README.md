
# Chip-8 Emulator

This project was my first foray into interpreters, emulators, and virtual machines. It's a fairly basic Chip-8 emulator with debugging tools that focuses on customizability. 
## Authors

- [@omrawaley](https://www.github.com/omrawaley)


## Demo

![demo](https://raw.githubusercontent.com/omrawaley/chip-8-emulator/main/demo.gif)


## Features

- Load ROMs from CLI or GUI
- Reset ROMs
- Adjust ROM speed
- Pause ROMs
- Customize display colors
- Take screenshots
- Edit and view memory
- View registers, stack, and timers at runtime
- Adjust program counter while paused


## Installation

Use the provided `CMakeLists.txt` and compile with `make`.

```bash
  cmake CMakeLists.txt
  make
```
    
## Usage

```bash
./bin/chip8 <path-to-rom>
```

### Keys
P - Pause ROM.

M - Open settings menu.

N - Open debug panes.
## License

Chip-8 emulator - [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)

[Dear ImGui](https://github.com/ocornut/imgui) - [MIT](https://choosealicense.com/licenses/mit/)

[stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h) - Public Domain

