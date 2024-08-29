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

#include "disassembler.h"
#include <sstream>
#include <iostream>

template<typename T>
std::string to_hexadecimal(T t)
{
    std::stringstream stream;

    stream << std::setfill('0') << std::uppercase << std::hex << t;

    return stream.str();
}

std::vector<std::string> Disassembler::disassemble(Memory& memory)
{
    uint16_t pc = CPU::pcStart;

    for(uint16_t i = 0; i < memory.romSize; i += 2)
    {
        Instruction instruction(memory.fetchWord(pc));

        pc += 2;

        instruction.opcode = Parser::parse(instruction);

        switch(instruction.opcode)
        {
            case Opcode::O00E0:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::CLS)]);
                break;

            case Opcode::O00EE:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::RET)]);
                break;

            case Opcode::O1NNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::JMP)] + " " + to_hexadecimal(instruction.getNNN()));
                break;

            case Opcode::O2NNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::JMP)] + " " + to_hexadecimal(instruction.getNNN()));
                break;

            case Opcode::O3XNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SE)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " " + to_hexadecimal(static_cast<size_t>(instruction.getNN())));
                break;

            case Opcode::O4XNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SNE)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " " + to_hexadecimal(static_cast<size_t>(instruction.getNN())));
                break;

            case Opcode::O5XY0:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SE)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O6XNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " " + to_hexadecimal(static_cast<size_t>(instruction.getNN())));
                break;

            case Opcode::O7XNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::ADD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " " + to_hexadecimal(static_cast<size_t>(instruction.getNN())));
                break;

            case Opcode::O8XY0:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY1:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::OR)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY2:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::AND)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY3:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::XOR)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY4:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::ADD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY5:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SUB)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY6:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SHR)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XY7:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SUBN)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O8XYE:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SHL)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::O9XY0:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SNE)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())));
                break;

            case Opcode::OANNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " " + to_hexadecimal(instruction.getNNN()));
                break;

            case Opcode::OBNNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::JMP)] + " V0 " + to_hexadecimal(instruction.getNNN()));
                break;

            case Opcode::OCXNN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::RND)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " " + to_hexadecimal(static_cast<size_t>(instruction.getNN())));
                break;

            case Opcode::ODXYN:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::DRW)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " V" + to_hexadecimal(static_cast<size_t>(instruction.getY())) + " " + to_hexadecimal(static_cast<size_t>(static_cast<size_t>(instruction.getN()))));
                break;

            case Opcode::OEX9E:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SKP)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OEXA1:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::SKNP)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX07:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " DT");
                break;

            case Opcode::OFX0A:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " K");
                break;

            case Opcode::OFX15:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " DT" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX18:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " ST" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX1E:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::ADD)] + " I" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX29:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " F" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX33:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " B" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX55:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " MI" + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())));
                break;

            case Opcode::OFX65:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + ": " + this->instructionStrings[static_cast<uint8_t>(Instructions::LD)] + " V" + to_hexadecimal(static_cast<size_t>(instruction.getX())) + " MI");
                break;

            case Opcode::Invalid:
                this->disassembledInstructions.push_back(to_hexadecimal(pc - 2) + " " + "DATA " + to_hexadecimal(instruction.word));
                break;
        }
    }

    return this->disassembledInstructions;
}