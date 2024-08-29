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

#include "parser.h"

Opcode Parser::parse(Instruction instruction)
{
    switch(instruction.word & 0xF000)
    {
        case 0x0000:
            switch(instruction.getNN())
            {
                case 0x00E0:
                    return Opcode::O00E0;
                    break;

                case 0x00EE:
                    return Opcode::O00EE;
                    break;
            }
            break;

        case 0x1000:
            return Opcode::O1NNN;
            break;

        case 0x2000:
            return Opcode::O2NNN;
            break;

        case 0x3000:
            return Opcode::O3XNN;
            break;

        case 0x4000:
            return Opcode::O4XNN;
            break;

        case 0x5000:
            return Opcode::O5XY0;
            break;

        case 0x6000:
            return Opcode::O6XNN;
            break;

        case 0x7000:
            return Opcode::O7XNN;
            break;

        case 0x8000:
            switch(instruction.getN())
            {
                case 0x0000:
                    return Opcode::O8XY0;
                    break;

                case 0x0001:
                    return Opcode::O8XY1;
                    break;

                case 0x0002:
                    return Opcode::O8XY2;
                    break;

                case 0x0003:
                    return Opcode::O8XY3; 
                    break;

                case 0x0004:
                    return Opcode::O8XY4; 
                    break;

                case 0x0005:
                    return Opcode::O8XY5;
                    break;

                case 0x0006:
                    return Opcode::O8XY6;
                    break;

                case 0x0007:
                    return Opcode::O8XY7;
                    break;

                case 0x000E:
                    return Opcode::O8XYE;
                    break;
            }
            break;

        case 0x9000:
            return Opcode::O9XY0;
            break;

        case 0xA000:
            return Opcode::OANNN;
            break;

        case 0xB000:
            return Opcode::OBNNN;
            break;

        case 0xC000:
            return Opcode::OCXNN;
            break;

        case 0xD000:
            return Opcode::ODXYN;
            break;

        case 0xE000:
            switch(instruction.getNN())
            {
                case 0x009E:
                    return Opcode::OEX9E;
                    break;

                case 0x00A1:
                    return Opcode::OEXA1;
                    break;
            }
            break;

        case 0xF000:
            switch(instruction.getNN())
            {
                case 0x0007:
                    return Opcode::OFX07;
                    break;

                case 0x000A:
                    return Opcode::OFX0A;
                    break;

                case 0x0015:
                    return Opcode::OFX15;
                    break;

                case 0x0018:
                    return Opcode::OFX18;
                    break;

                case 0x001E:
                    return Opcode::OFX1E;
                    break;

                case 0x0029:
                    return Opcode::OFX29;
                    break;

                case 0x0033:
                    return Opcode::OFX33;
                    break;

                case 0x0055:
                    return Opcode::OFX55;
                    break;

                case 0x0065:
                    return Opcode::OFX65;
                    break;
            }
            break;

        default:
            return Opcode::Invalid;
            break;
    }

    return Opcode::Invalid;
}