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
#include <string>
#include <vector>

#include "chip8.h"

struct Disassembler
{
    private:
        enum class Instructions : uint8_t
        {
            CLS,
            RET,
            JMP,
            CALL,
            SE,
            SNE,
            LD,
            ADD,
            OR,
            AND,
            XOR,
            SUB,
            SHR,
            SUBN,
            SHL,
            RND,
            DRW,
            SKP,
            SKNP,
        };

        const std::array<std::string, 19> instructionStrings
        {
            "CLS",
            "RET",
            "JMP",
            "CALL",
            "SE",
            "SNE",
            "LD",
            "ADD",
            "OR",
            "AND",
            "XOR",
            "SUB",
            "SHR",
            "SUBN",
            "SHL",
            "RND",
            "DRW",
            "SKP",
            "SKNP",
        };

        std::vector<std::string> disassembledInstructions;

    public:
        std::vector<std::string> disassemble(Memory& memory);
};