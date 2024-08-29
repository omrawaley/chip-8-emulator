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

#include "memory.h"

Memory::Memory() : romLoaded(false)
{
    this->reset();

    this->loadFont();
}

void Memory::reset()
{
    for(auto& index : this->memory)
        index = 0;
}

uint8_t& Memory::operator[](uint16_t index)
{
    return this->memory[index];
}

uint8_t* Memory::getData()
{
    return this->memory;
}

uint16_t Memory::fetchWord(uint16_t pc)
{
    const uint8_t highByte = this->memory[pc + 0];
    const uint8_t lowByte = this->memory[pc + 1];

    const uint16_t word = (highByte << 8 | lowByte);

    return word;
}

void Memory::loadFont()
{
    if(sizeof(Memory::fontset0) / sizeof(Memory::fontset0[0]) > Memory::fontsetSize)
        return;

    for(int i = 0; i < Memory::fontsetSize; ++i)
        this->memory[i] = Memory::fontset0[i];
}

void Memory::loadROM(const char* romPath)
{
    std::ifstream rom(romPath, std::ios::binary | std::ios::ate);

    if(rom.is_open())
    {
        std::streampos size = rom.tellg();

        char* buffer = new char[size];

        rom.seekg(0, std::ios::beg);
        rom.read(buffer, size);
        rom.close();

        for(long i = 0; i < size; ++i)
        {
            this->memory[CPU::pcStart + i] = buffer[i];
        }

        delete[] buffer;

        this->romSize = size;

        this->romLoaded = true;
    }
    else
    {
        std::cout << "Couldn't open ROM" << std::endl;

        this->romLoaded = false;
    }
}
