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

enum class Opcode : uint8_t
{
    O00E0,
    O00EE,
    O1NNN,
    O2NNN,
    O3XNN,
    O4XNN,
    O5XY0,
    O6XNN,
    O7XNN,
    O8XY0,
    O8XY1,
    O8XY2,
    O8XY3,
    O8XY4,
    O8XY5,
    O8XY6,
    O8XY7,
    O8XYE,
    O9XY0,
    OANNN,
    OBNNN,
    OCXNN,
    ODXYN,
    OEX9E,
    OEXA1,
    OFX07,
    OFX0A,
    OFX15,
    OFX18,
    OFX1E,
    OFX29,
    OFX33,
    OFX55,
    OFX65,
    Invalid,
};
