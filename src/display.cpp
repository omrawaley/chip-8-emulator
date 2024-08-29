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

#include "display.h"

Display::Display()
{
    // Display::onColor = 0xA0FFA0FF;
    // Display::offColor = 0x000000FF;

    Display::onColor = 0xFFA0FFA0;
    Display::offColor = 0xFF000000;

    this->clear();
}

void Display::clear()
{
    for(auto& pixel : this->display)
        pixel = this->offColor;
}

uint32_t& Display::operator[](uint32_t index)
{
    return this->display[index];
}

uint32_t* Display::getData()
{
    return this->display;
}
