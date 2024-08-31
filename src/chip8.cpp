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

#include "chip8.h"
#include "instructions.h"
#include <cstdlib>

Chip8::Chip8() : paused(false), instructionsPerSecond(11)
{
    this->reset(true);
}

void Chip8::reset(bool resetMemory)
{
    this->cpu.reset();
    this->display.clear();
    this->keypad.reset();

    if(!resetMemory)
        return;

    this->memory.reset();
    this->memory.loadFont();
}

void Chip8::emulateCycle(const Uint8* keys)
{
    if(!this->memory.romLoaded)
        return;

    if(this->paused)
        return;

    this->keypad.update(keys);

    for(uint8_t i = 0; i < this->instructionsPerSecond; ++i)
    {
        Instruction instruction(this->memory.fetchWord(this->cpu.pc));

        this->cpu.pc += 2;

        instruction.opcode = Parser::parse(instruction);

        this->execute(instruction);
    }

    if(this->cpu.delayTimer > 0)
        --this->cpu.delayTimer;

    if(this->cpu.soundTimer > 0)
        --this->cpu.soundTimer;
}

void Chip8::execute(Instruction& instruction)
{
    switch(instruction.opcode)
    {
        case Opcode::O00E0:
            Instructions::CLS(this->display);
            break;

        case Opcode::O00EE:
            Instructions::RET(this->cpu);
            break;

        case Opcode::O1NNN:
            Instructions::JMP_NNN(this->cpu, instruction.getNNN());
            break;

        case Opcode::O2NNN:
            Instructions::CALL(this->cpu, instruction.getNNN());
            break;

        case Opcode::O3XNN:
            Instructions::SE_VX_NN(this->cpu, instruction.getX(), instruction.getNN());
            break;

        case Opcode::O4XNN:
            Instructions::SNE_VX_NN(this->cpu, instruction.getX(), instruction.getNN());
            break;

        case Opcode::O5XY0:
            Instructions::SE_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O6XNN:
            Instructions::LD_VX_NN(this->cpu, instruction.getX(), instruction.getNN());
            break;

        case Opcode::O7XNN:
            Instructions::ADD_VX_NN(this->cpu, instruction.getX(), instruction.getNN());
            break;

        case Opcode::O8XY0:
            Instructions::LD_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY1:
            Instructions::OR(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY2:
            Instructions::AND(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY3:
            Instructions::XOR(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY4:
            Instructions::ADD_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY5:
            Instructions::SUB_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XY6:
            Instructions::SHR(this->cpu, instruction.getX());
            break;

        case Opcode::O8XY7:
            Instructions::SUBN_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::O8XYE:
            Instructions::SHL(this->cpu, instruction.getX());
            break;

        case Opcode::O9XY0:
            Instructions::SNE_VX_VY(this->cpu, instruction.getX(), instruction.getY());
            break;

        case Opcode::OANNN:
            Instructions::LD_NNN(this->cpu, instruction.getNNN());
            break;

        case Opcode::OBNNN:
            Instructions::JMP_V0(this->cpu, instruction.getNNN());
            break;

        case Opcode::OCXNN:
            Instructions::RND(this->cpu, instruction.getX(), instruction.getNN());
            break;

        case Opcode::ODXYN:
            Instructions::DRW(this->display, this->memory, this->cpu, instruction.getX(), instruction.getY(), instruction.getN());
            break;

        case Opcode::OEX9E:
            Instructions::SKP(this->keypad, this->cpu, instruction.getX());
            break;

        case Opcode::OEXA1:
            Instructions::SKNP(this->keypad, this->cpu, instruction.getX());
            break;

        case Opcode::OFX07:
            Instructions::LD_VX_DT(this->cpu, instruction.getX());
            break;

        case Opcode::OFX0A:
            Instructions::LD_VX_K(this->keypad, this->cpu, instruction.getX());
            break;

        case Opcode::OFX15:
            Instructions::LD_DT_VX(this->cpu, instruction.getX());
            break;

        case Opcode::OFX18:
            Instructions::LD_ST_VX(this->cpu, instruction.getX());
            break;

        case Opcode::OFX1E:
            Instructions::ADD_I_VX(this->cpu, instruction.getX());
            break;

        case Opcode::OFX29:
            Instructions::LD_F_VX(this->cpu, instruction.getX());
            break;

        case Opcode::OFX33:
            Instructions::LD_B_VX(this->memory, this->cpu, instruction.getX());
            break;

        case Opcode::OFX55:
            Instructions::LD_MI_VX(this->memory, this->cpu, instruction.getX());
            break;

        case Opcode::OFX65:
            Instructions::LD_VX_MI(this->memory, this->cpu, instruction.getX());
            break;

        case Opcode::Invalid:
            std::cerr << "Error: Invalid Opcode" << std::endl;

            std::exit(EXIT_FAILURE);
            break;
    }
}
