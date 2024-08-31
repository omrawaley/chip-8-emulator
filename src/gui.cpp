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

#include "gui.h"

bool GUI::showSettings = false;
bool GUI::isROMInputActive = false;

bool GUI::showDebugWindows = false;

void GUI::init(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void GUI::free()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUI::processEvent(SDL_Event event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void GUI::drawSettings(Chip8& chip8, uint8_t& frameTime, bool& takeScreenshot)
{
    if(!GUI::showSettings)
        return;
        
    ImGui::Begin("Menu", &GUI::showSettings);

    if(ImGui::BeginTabBar("Tabs"))
    {
        if(ImGui::BeginTabItem("ROMs"))
        {
            GUI::drawROMs(chip8);

            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Speed"))
        {
            GUI::drawSpeed(frameTime);

            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Image"))
        {
            GUI::drawImage(chip8.display, takeScreenshot);

            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Help"))
        {
            GUI::drawHelp();

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void GUI::drawCPU(Chip8& chip8)
{
    if(!GUI::showDebugWindows)
        return;

    ImGui::SetNextWindowSize(GUI::cpuContentsSize);

    ImVec2 pos = {0, Display::displayHeight * Display::displayScaleMinimized};

    ImGui::SetNextWindowPos(pos);

    ImGui::Begin("CPU Contents", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    if(ImGui::BeginTable("Registers", 4))
    {
        ImGui::TableNextColumn();

        ImGui::SeparatorText("Regs");

        ImGui::Spacing();

        for(int i = 0; i < 16; ++i)
        {
            ImGui::Text("Reg %X: %X", i, chip8.cpu.v[i]);
            ImGui::Spacing();
        }

        ImGui::Text("Index: %X", chip8.cpu.i);

        ImGui::TableNextColumn();

        ImGui::SeparatorText("Stack");

        ImGui::Spacing();

        for(int i = 0; i < 16; ++i)
        {
            ImGui::Text("Level %X: %X", i, chip8.cpu.stack[i]);
            ImGui::Spacing();
        }

        ImGui::Text("SP: %X", chip8.cpu.sp);

        ImGui::TableNextColumn();

        ImGui::SeparatorText("Timers");

        ImGui::Spacing();

        ImGui::Text("Delay: %X", chip8.cpu.delayTimer);

        ImGui::Spacing();

        ImGui::Text("Sound: %X", chip8.cpu.soundTimer);

        ImGui::Spacing();

        ImGui::TableNextColumn();

        ImGui::SeparatorText("Program");

        ImGui::Spacing();

        ImGui::Checkbox("Paused", &chip8.paused);

        ImGui::Spacing();

        ImGui::Text("PC: %X", chip8.cpu.pc);

        ImGui::SameLine();

        if(chip8.paused)
        {
            if(ImGui::Button("-"))
            {
                chip8.cpu.pc -= 2;
            }

            ImGui::SameLine();

            if(ImGui::Button("+"))
            {
                chip8.cpu.pc += 2;
            }

            static int newPC;

            ImGui::InputInt("", &newPC, 0, 0, ImGuiInputTextFlags_CharsHexadecimal);

            if(ImGui::Button("Apply"))
                chip8.cpu.pc = static_cast<uint16_t>(newPC);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void GUI::drawDisassembly(Chip8& chip8)
{
    if(!GUI::showDebugWindows)
        return;

    ImGui::SetNextWindowSize(GUI::disassemblySize);

    ImVec2 pos = {Display::displayWidth * Display::displayScaleMinimized, 0};

    ImGui::SetNextWindowPos(pos);

    ImGui::Begin("Disassembly", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    Disassembler disassembler;

    std::vector<std::string> instructions = disassembler.disassemble(chip8.memory);

    for(uint16_t i = 0; i < instructions.size(); ++i)
    {
        if(i == (chip8.cpu.pc - CPU::pcStart) / 2)
        {
            ImGui::TextColored(ImColor{255, 0, 0, 255}, "%s", instructions.at(i).c_str());
            ImGui::SetScrollHereY();
        }
        else
            ImGui::Text("%s", instructions.at(i).c_str());
    }

    ImGui::End();
}

void GUI::drawMemoryEditor(Memory& memory)
{   
    if(!GUI::showDebugWindows)
        return;

    static MemoryEditor memoryEditor;

    ImGui::SetNextWindowSize(GUI::memoryEditorSize);

    ImVec2 pos = {(Display::displayWidth * Display::displayScale) - GUI::memoryEditorSize[0], 0};

    ImGui::SetNextWindowPos(pos);

    ImGui::Begin("Memory Editor", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    memoryEditor.DrawContents(memory.getData(), Memory::memorySize);

    ImGui::End();
}

void GUI::drawROMs(Chip8& chip8)
{
    static char rom[64];

    ImGui::InputTextWithHint("ROM path", "e.g. /Users/user/Downloads/rom.ch8", rom, IM_ARRAYSIZE(rom));

    if(ImGui::IsItemActive())
    {
        GUI::isROMInputActive = true;
    }
    else
    {
        GUI::isROMInputActive = false;
    }

    if(rom[0] != 0)
    {
        if(ImGui::Button("Load"))
        {
            chip8.reset(true);

            chip8.memory.loadROM(rom);
        }
    }

    ImGui::Separator();

    if(ImGui::Button("Reset ROM"))
        chip8.reset(false);
}

void GUI::drawSpeed(uint8_t& instructionsPerSecond)
{
    static bool applyImmediately;

    static int value = 11;

    ImGui::DragInt("Instructions Per Second", &value, 0.1, 0, 64);

    ImGui::Checkbox("Apply Immediately", &applyImmediately);

    if(applyImmediately)
    {
        instructionsPerSecond = value;
    }

    else
    {
        if(ImGui::Button("Apply"))
        {
            instructionsPerSecond = value;
        }
    }
}

void GUI::drawImage(Display& display, bool& takeScreenshot)
{
    bool applyColor;

    static float onColor[3]
    {
        static_cast<float>((display.onColor >> 0) & 0xFF) / 255, 
        static_cast<float>((display.onColor >> 8) & 0xFF) / 255, 
        static_cast<float>((display.onColor >> 16) & 0xFF) / 255,
    };

    static float offColor[3]
    {
        static_cast<float>((display.offColor >> 0) & 0xFF) / 255, 
        static_cast<float>((display.offColor >> 8) & 0xFF) / 255, 
        static_cast<float>((display.offColor >> 16) & 0xFF) / 255,
    };

    ImGui::ColorEdit3("Pixel On Color", onColor);

    ImGui::ColorEdit3("Pixel Off Color", offColor);

    if(ImGui::Button("Apply"))
        applyColor = true;

    if(applyColor)
    {
        uint32_t oldOnColor = display.onColor;
        uint32_t oldOffColor = display.offColor;

        display.onColor = static_cast<uint8_t>((onColor[0] * 255)) << 0 | static_cast<uint8_t>((onColor[1] * 255)) << 8 | static_cast<uint8_t>((onColor[2] * 255)) << 16;

        display.offColor = static_cast<uint8_t>((offColor[0] * 255)) << 0 | static_cast<uint8_t>((offColor[1] * 255)) << 8 | static_cast<uint8_t>((offColor[2] * 255)) << 16;

        for(uint16_t i = 0; i < Display::displayWidth * Display::displayHeight; ++i)
        {
            if(display[i] == oldOnColor)
            {
                display[i] = display.onColor;
            }

            if(display[i] == oldOffColor)
            {
                display[i] = display.offColor;
            }
        }

        applyColor = false;
    }

    ImGui::Separator();

    if(ImGui::Button("Take Screenshot"))
        takeScreenshot = true;
}

void GUI::drawHelp()
{
    ImGui::SeparatorText("Controls");

    ImGui::Spacing();

    ImGui::Text(" Emulator   |  Cosmac VIP");

    for(uint8_t i = 0; i < 8; i += 2)
    {
        ImGui::Text("%s", GUI::controlsText.at(i).c_str());

        ImGui::SameLine();

        ImGui::Text("%s", GUI::controlsText.at(i + 1).c_str());
    }
}

void GUI::draw(SDL_Renderer* renderer, Chip8& chip8, uint8_t& instructionsPerSecond, bool& takeScreenshot)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    GUI::drawSettings(chip8, instructionsPerSecond, takeScreenshot);
    
    GUI::drawMemoryEditor(chip8.memory);

    GUI::drawDisassembly(chip8);

    GUI::drawCPU(chip8);

    ImGui::Render();

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}