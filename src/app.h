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

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <cstdlib>

#include "chip8.h"
#include "gui.h"

class App
{
    private:
        const Uint8* keys;

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

    public:
        Chip8 chip8;

    private:
        void loadMedia();
        void freeMedia();

    public:
        bool quit;

        bool takeScreenshot;

    private:
        void screenshot();

    public:
        App();
        ~App();

        void start(const char* romPath);
        void eventLoop();
        void update();
        void draw();
};
