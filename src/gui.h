//     Chip-8 emulator, debugger, and disassembler.
//     Copyright (C) 2024 Om Rawaley (@omrawaley)

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <stdint.h>

#include <SDL2/SDL.h>

#include "../deps/imgui/imgui.h"
#include "../deps/imgui/backends/imgui_impl_sdl2.h"
#include "../deps/imgui/backends/imgui_impl_sdlrenderer2.h"
#include "../deps/imgui/imgui_memory_editor.h"

#include "disassembler.h"

namespace GUI
{
    extern bool showSettings;
    extern bool isROMInputActive;

    extern bool showDebugWindows;

    const ImVec2 memoryEditorSize = {418, Display::displayHeight * Display::displayScale};
    const ImVec2 disassemblySize = {418, Display::displayHeight * Display::displayScale};
    const ImVec2 cpuContentsSize = {Display::displayWidth * Display::displayScaleMinimized, (Display::displayHeight * Display::displayScale) - (Display::displayHeight * Display::displayScaleMinimized)};

    const std::array<std::string, 8> controlsText = 
    {
        "1  2  3  4    ",
        "1  2  3  C",
        "Q  W  E  R    ",
        "4  5  6  D",
        "A  S  D  F    ",
        "7  8  9  E",
        "Z  X  C  V    ",
        "A  0  B  F",
    };

    void init(SDL_Window* window, SDL_Renderer* renderer);

    void free();

    void processEvent(SDL_Event event);

    void drawSettings(Chip8& chip8, uint8_t& instructionsPerSecond, bool& takeScreenshot);

    void drawCPU(Chip8& chip8);

    void drawDisassembly(Chip8& chip8);

    void drawMemoryEditor(Memory& memory);

    void drawROMs(Chip8& chip8);

    void drawSpeed(uint8_t& frameTime);

    void drawImage(Display& display, bool& takeScreenshot);

    void drawHelp();

    void draw(SDL_Renderer* renderer, Chip8& chip8, uint8_t& frameTime, bool& takeScreenshot);
};