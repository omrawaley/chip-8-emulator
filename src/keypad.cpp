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

#include "keypad.h"

Keypad::Keypad()
{
    this->reset();
}

void Keypad::reset()
{
    for(auto& key : this->keys)
        key = false;

    for(auto& key : this->oldKeys)
        key = false;
}

bool& Keypad::operator[](uint8_t key)
{
    return this->keys.at(key);
}

void Keypad::setKey(uint8_t key, bool activated)
{
    if(key >= Keypad::keyCount)
        return;

    this->oldKeys.at(key) = this->keys.at(key);

    this->keys.at(key) = activated;
}

void Keypad::update(const Uint8* keys)
{
    for(uint8_t i = 0; i < this->keyCount; ++i)
    {
        this->setKey(i, keys[Keypad::scancodes.at(i)] != 0);
    }
}