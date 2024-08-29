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

#include "app.h"
#include "display.h"
#include <SDL2/SDL_render.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../deps/stb_image_write.h"

App::App() : quit(false), keys(nullptr), window(nullptr), renderer(nullptr), texture(nullptr), frameTime(16.6)
{
    this->loadMedia();
}

App::~App()
{
    this->freeMedia();
}

void App::loadMedia()
{
    SDL_Init(SDL_INIT_EVERYTHING);

	this->window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Display::displayWidth * Display::displayScale, Display::displayHeight * Display::displayScale, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, Display::displayWidth, Display::displayHeight);
}

void App::freeMedia()
{
    GUI::free();

    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
}

void App::screenshot()
{
    stbi_write_jpg("capture.png", Display::displayWidth, Display::displayHeight, 4, this->chip8.display.getData(), Display::displayWidth * 4);

    this->takeScreenshot = false;
}

void App::start(const char* romPath)
{
    this->chip8.memory.loadROM(romPath);
    
    srand(time(nullptr));

    GUI::init(this->window, this->renderer);
}

void App::eventLoop()
{
    SDL_Event event;
	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				this->quit = true;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						this->quit = true;
						break;

                    case SDLK_p:
                        if(!GUI::showSettings)
                            this->chip8.paused = !this->chip8.paused;
                        break;

                    case SDLK_m:
                        if(!GUI::isROMInputActive)
                            GUI::showSettings = !GUI::showSettings;
                        break;

                    case SDLK_n:
                        if(!GUI::isROMInputActive)
                            GUI::showDebugWindows = !GUI::showDebugWindows;

                        if(!GUI::showDebugWindows)
                        {
                            SDL_Rect viewportRect {0, 0, Display::displayWidth * Display::displayScale, Display::displayHeight * Display::displayScale};

                            SDL_RenderSetViewport(this->renderer, &viewportRect);
                        }
                        else
                        {
                            SDL_Rect viewportRect {0, 0, Display::displayWidth * Display::displayScaleMinimized, Display::displayHeight * Display::displayScaleMinimized};

                            SDL_RenderSetViewport(this->renderer, &viewportRect);
                        }
                        break;
				}
				break;
		}

        GUI::processEvent(event);
	}
}

void App::update()
{
    this->keys = SDL_GetKeyboardState(nullptr);

    this->chip8.emulateCycle(this->keys);

    if(!this->takeScreenshot)
        return;

    this->screenshot();
}

void App::draw()
{
    SDL_RenderClear(this->renderer);

    SDL_UpdateTexture(this->texture, nullptr, this->chip8.display.getData(), sizeof(this->chip8.display[0]) * Display::displayWidth);

    SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);

    GUI::draw(this->renderer, this->chip8, this->frameTime, this->takeScreenshot);

    SDL_RenderPresent(this->renderer);
}
