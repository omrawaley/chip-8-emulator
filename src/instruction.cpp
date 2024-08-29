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

#include "instruction.h"

Instruction::Instruction(uint16_t word) : word(word)
{
}

uint16_t Instruction::getNNN()
{
    return (this->word & 0x0FFF);
}

uint8_t Instruction::getNN()
{
    return (this->word & 0x00FF);
}

uint8_t Instruction::getN()
{
    return (this->word & 0x000F);
}

uint8_t Instruction::getX()
{
    return ((this->word & 0x0F00) >> 8);
}

uint8_t Instruction::getY()
{
    return ((this->word & 0x00F0) >> 4);
}
