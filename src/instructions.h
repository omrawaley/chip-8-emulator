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
#include <cstdlib>

#include "keypad.h"
#include "display.h"
#include "memory.h"
#include "cpu.h"

namespace Instructions
{
    void CLS(Display& display); // Clear display
    void RET(CPU& cpu); // Return from subroutine
    void JMP_NNN(CPU& cpu, uint16_t nnn); // Jump to address
    void CALL(CPU& cpu, uint16_t nnn); // Call subroutine
    void SE_VX_NN(CPU& cpu, uint8_t x, uint8_t nn); // Skip if reg x == byte
    void SNE_VX_NN(CPU& cpu, uint8_t x, uint8_t nn); // Skip if reg x != byte
    void SE_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Skip if reg x == reg y
    void LD_VX_NN(CPU& cpu, uint8_t x, uint8_t nn); // Set reg x to nn
    void ADD_VX_NN(CPU& cpu, uint8_t x, uint8_t nn); // Adds nn to reg x
    void LD_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Set reg x to reg y
    void OR(CPU& cpu, uint8_t x, uint8_t y); // Binary OR
    void AND(CPU& cpu, uint8_t x, uint8_t y); // Binary AND
    void XOR(CPU& cpu, uint8_t x, uint8_t y); // Binary XOR
    void ADD_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Adds reg y to reg x
    void SUB_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Subtracts reg y from reg x
    void SHR(CPU& cpu, uint8_t x); // Shift reg x one bit to the right
    void SUBN_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Subtracts reg x from reg y
    void SHL(CPU& cpu, uint8_t x); // Shift reg x one bit to the left
    void SNE_VX_VY(CPU& cpu, uint8_t x, uint8_t y); // Skip the next instruction if reg x != reg y
    void LD_NNN(CPU& cpu, uint16_t nnn); // Set reg i to nnn
    void JMP_V0(CPU& cpu, uint16_t nnn); // Set reg i to nnn + reg 0
    void RND(CPU& cpu, uint8_t x, uint8_t nn); // Sets reg x to random number & nn
    void DRW(Display& display, Memory& memory, CPU& cpu, uint8_t x, uint8_t y, uint8_t n); // Draws sprite at coords (reg x, reg y)
    void SKP(Keypad& keypad, CPU& cpu, uint8_t x); // Skip the next instruction if the key stored in reg x is pressed
    void SKNP(Keypad& keypad, CPU& cpu, uint8_t x); // Skip the next instruction if the key stored in reg x is not pressed
    void LD_VX_DT(CPU& cpu, uint8_t x); // Set reg x to the value of the delay timer
    void LD_VX_K(Keypad& keypad, CPU& cpu, uint8_t x); // Set reg x to the value of an awaited key release
    void LD_DT_VX(CPU& cpu, uint8_t x); // Set the delay timer to reg x
    void LD_ST_VX(CPU& cpu, uint8_t x); // Set the sound timer to reg x
    void ADD_I_VX(CPU& cpu, uint8_t x); // Add the value of reg x to the index register
    void LD_F_VX(CPU& cpu, uint8_t x); // Set the index register to the location of the sprite for the char in reg x
    void LD_B_VX(Memory& memory, CPU& cpu, uint8_t x); // Set memory locations i, i + 1, and i + 2 to the BCD representation of reg x
    void LD_MI_VX(Memory& memory, CPU& cpu, uint8_t x); // Set memory starting at location i to reg 0 to reg x
    void LD_VX_MI(Memory& memory, CPU& cpu, uint8_t x); // Set reg 0 to reg x with values from memory starting at location i
};
