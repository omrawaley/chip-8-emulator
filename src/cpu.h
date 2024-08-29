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

class CPU
{
    private:
        static constexpr uint8_t registerCount = 16;
        static constexpr uint8_t stackSize = 16;

    public:
        static constexpr uint16_t pcStart = 0x200;

    public:
        uint16_t sp; // Points to the top of the stack

        uint16_t i; // Stores memory addresses

        uint16_t pc; // Points at the current instruction in memory
    
        uint8_t delayTimer; // Used for timing the events of a game

        uint8_t soundTimer; // Used for generating sound

        uint8_t v[CPU::registerCount]; // Registers 0 to F

        uint16_t stack[CPU::stackSize]; // Stores return addresses
    
    public:
        CPU();

        void reset();
};
