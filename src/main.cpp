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

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

#include "app.h"

int main(int argc, char* argv[])
{
    App app;

    app.start(argv[1]);

    auto lastCycleTime = std::chrono::steady_clock::now();

    while(!app.quit)
    {
        auto currentTime = std::chrono::steady_clock::now();

        float deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if(deltaTime > app.frameTime)
        {
            lastCycleTime = currentTime;

            app.eventLoop();

            app.update();

            app.draw();
        }
    }

    return 0;
}
