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

#include "instructions.h"
#include "cpu.h"
#include "keypad.h"

using namespace Instructions;

void Instructions::CLS(Display& display)
{
    display.clear();
}

void Instructions::RET(CPU& cpu)
{
    --cpu.sp;

    cpu.pc = cpu.stack[cpu.sp];
}

void Instructions::JMP_NNN(CPU& cpu, uint16_t nnn)
{
    cpu.pc = nnn;
}

void Instructions::CALL(CPU& cpu, uint16_t nnn)
{
    cpu.stack[cpu.sp] = cpu.pc;

    ++cpu.sp;

    cpu.pc = nnn;
}

void Instructions::SE_VX_NN(CPU& cpu, uint8_t x, uint8_t nn)
{
    if(cpu.v[x] == nn)
        cpu.pc += 2;
}

void Instructions::SNE_VX_NN(CPU& cpu, uint8_t x, uint8_t nn)
{
    if(cpu.v[x] != nn)
        cpu.pc += 2;
}

void Instructions::SE_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    if(cpu.v[x] == cpu.v[y])
        cpu.pc += 2;
}

void Instructions::LD_VX_NN(CPU& cpu, uint8_t x, uint8_t nn)
{
    cpu.v[x] = nn;
}

void Instructions::ADD_VX_NN(CPU& cpu, uint8_t x, uint8_t nn)
{
    cpu.v[x] += nn;
}

void Instructions::LD_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    cpu.v[x] = cpu.v[y];
}

void Instructions::OR(CPU& cpu, uint8_t x, uint8_t y)
{
    cpu.v[x] |= cpu.v[y];
}

void Instructions::AND(CPU& cpu, uint8_t x, uint8_t y)
{
    cpu.v[x] &= cpu.v[y];
}

void Instructions::XOR(CPU& cpu, uint8_t x, uint8_t y)
{
    cpu.v[x] ^= cpu.v[y];
}

void Instructions::ADD_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    const bool carry {(cpu.v[x] + cpu.v[y]) > 255};

    cpu.v[x] += cpu.v[y] & 0xFF;

    cpu.v[0xF] = carry;
}

void Instructions::SUB_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    const bool notBorrow {cpu.v[x] >= cpu.v[y]};

    cpu.v[x] -= cpu.v[y];

    cpu.v[0xF] = notBorrow;
}

void Instructions::SHR(CPU& cpu, uint8_t x)
{
    uint8_t lsb = cpu.v[x] & 0x1;

    cpu.v[x] >>= 1;

    cpu.v[0xF] = lsb;
}

void Instructions::SUBN_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    const bool notBorrow {cpu.v[y] >= cpu.v[x]};

    cpu.v[x] = cpu.v[y] - cpu.v[x];

    cpu.v[0xF] = notBorrow;
}

void Instructions::SHL(CPU& cpu, uint8_t x)
{
    uint8_t msb = (cpu.v[x] & 0x80) >> 7;

    cpu.v[x] <<= 1;

    cpu.v[0xF] = msb;
}

void Instructions::SNE_VX_VY(CPU& cpu, uint8_t x, uint8_t y)
{
    if(cpu.v[x] != cpu.v[y])
        cpu.pc += 2;
}

void Instructions::LD_NNN(CPU& cpu, uint16_t nnn)
{
    cpu.i = nnn;
}

void Instructions::JMP_V0(CPU& cpu, uint16_t nnn)
{
    cpu.pc = nnn + cpu.v[0];
}

void Instructions::RND(CPU& cpu, uint8_t x, uint8_t nn)
{
    cpu.v[x] = rand() & nn;
}

void Instructions::DRW(Display& display, Memory& memory, CPU& cpu, uint8_t x, uint8_t y, uint8_t n)
{
    uint8_t xPos = cpu.v[x] % Display::displayWidth;
    uint8_t yPos = cpu.v[y] % Display::displayHeight;

    cpu.v[0xF] = 0;

    for(uint8_t row = 0; row < n; ++row)
    {
        if(yPos + row >= Display::displayHeight)
            break;

        uint8_t spriteByte = memory[cpu.i + row];

        for(uint8_t col = 0; col < 8; ++col)
        {
            if(xPos + col >= Display::displayWidth)
                break;

            if(!(spriteByte & (0x80 >> col)))
                continue;

            uint32_t& screenPixel = display[((yPos + row) * Display::displayWidth + (xPos + col))];

            if(screenPixel == display.onColor)
            {
                cpu.v[0xF] = 1;
            }

            screenPixel = screenPixel == display.offColor ? display.onColor : display.offColor;
        }
    }
}

void Instructions::SKP(Keypad& keypad, CPU& cpu, uint8_t x)
{
    if(keypad[(cpu.v[x] & 0xF)])
        cpu.pc += 2;
}

void Instructions::SKNP(Keypad& keypad, CPU& cpu, uint8_t x)
{
    if(!keypad[(cpu.v[x] & 0xF)])
        cpu.pc += 2;
}

void Instructions::LD_VX_DT(CPU& cpu, uint8_t x)
{
    cpu.v[x] = cpu.delayTimer;
}

void Instructions::LD_VX_K(Keypad& keypad, CPU& cpu, uint8_t x)
{
    bool released = false;

    for(uint8_t i = 0; i < Keypad::keyCount; ++i)
    {
        if(keypad.oldKeys[i] && !keypad[i])
        {
            cpu.v[x] = i;

            released = true;
        }
    }

    if(!released)
        cpu.pc -= 2;
}

void Instructions::LD_DT_VX(CPU& cpu, uint8_t x)
{
    cpu.delayTimer = cpu.v[x];
}

void Instructions::LD_ST_VX(CPU& cpu, uint8_t x)
{
    cpu.soundTimer = cpu.v[x];
}

void Instructions::ADD_I_VX(CPU& cpu, uint8_t x)
{
    cpu.i += cpu.v[x];
}

void Instructions::LD_F_VX(CPU& cpu, uint8_t x)
{
    cpu.i = (cpu.v[x] & 0xF) * 5;
}

void Instructions::LD_B_VX(Memory& memory, CPU& cpu, uint8_t x)
{
    memory[cpu.i + 2] = cpu.v[x] % 10;

    memory[cpu.i + 1] = (cpu.v[x] / 10) % 10;

    memory[cpu.i] = cpu.v[x] / 100;
}

void Instructions::LD_MI_VX(Memory& memory, CPU& cpu, uint8_t x)
{
    for(uint8_t i = 0; i <= x; ++i)
        memory[(cpu.i + i) & 0xFFF] = cpu.v[i];
}

void Instructions::LD_VX_MI(Memory& memory, CPU& cpu, uint8_t x)
{
    for(uint8_t i = 0; i <= x; ++i)
        cpu.v[i] = memory[(cpu.i + i) & 0xFFF];
}
