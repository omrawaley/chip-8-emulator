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
#include <array>

#include <SDL2/SDL.h>

class Keypad
{
    public:
        static constexpr uint8_t keyCount = 16; 

    private:
        static constexpr std::array<SDL_Scancode, Keypad::keyCount> scancodes
        {
            SDL_SCANCODE_X,
            SDL_SCANCODE_1,
            SDL_SCANCODE_2,
            SDL_SCANCODE_3,
            SDL_SCANCODE_Q,
            SDL_SCANCODE_W,
            SDL_SCANCODE_E,
            SDL_SCANCODE_A,
            SDL_SCANCODE_S,
            SDL_SCANCODE_D,
            SDL_SCANCODE_Z,
            SDL_SCANCODE_C,
            SDL_SCANCODE_4,
            SDL_SCANCODE_R,
            SDL_SCANCODE_F,
            SDL_SCANCODE_V,
        };

    private:
        std::array<bool, Keypad::keyCount> keys;

    public:
        std::array<bool, Keypad::keyCount> oldKeys;

    public:
        Keypad();

        void reset();

        bool& operator[](uint8_t key);

        void setKey(uint8_t key, bool activated);

        void update(const Uint8* keys);
};
