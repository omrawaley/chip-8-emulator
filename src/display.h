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

class Display
{
    public:
        static constexpr uint8_t displayWidth = 64;
        static constexpr uint8_t displayHeight = 32;
        static constexpr uint8_t displayScale = 24;
        static constexpr uint8_t displayScaleMinimized = 11;
        
        uint32_t onColor;
        uint32_t offColor;

    private:
        uint32_t display[Display::displayWidth * Display::displayHeight]; // Display with 2048 pixels 

    public:
        Display();

        void clear();

        uint32_t& operator[](uint32_t index);

        uint32_t* getData();
};
