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

#include "cpu.h"

CPU::CPU()
{
    this->reset();
}

void CPU::reset()
{
    this->sp = 0;
    this->i = 0;
    this->pc = CPU::pcStart;
    this->delayTimer = 0;
    this->soundTimer = 0;

    for(auto& reg : this->v)
        reg = 0;
    
    for(auto& layer : this->stack)
        layer = 0;
}
