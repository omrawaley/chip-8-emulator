cmake_minimum_required(VERSION 3.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

project(chip8_emulator)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

set(SRC_DIR src)
set(IMGUI_DIR deps/imgui)
set(IMGUI_BACKENDS_DIR deps/imgui/backends)
add_executable(chip8 ${SRC_DIR}/main.cpp ${SRC_DIR}/app.cpp ${SRC_DIR}/chip8.cpp ${SRC_DIR}/cpu.cpp ${SRC_DIR}/memory.cpp ${SRC_DIR}/display.cpp ${SRC_DIR}/instruction.cpp ${SRC_DIR}/instructions.cpp ${SRC_DIR}/parser.cpp ${SRC_DIR}/keypad.cpp ${SRC_DIR}/gui.cpp ${SRC_DIR}/disassembler.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_BACKENDS_DIR}/imgui_impl_sdl2.cpp ${IMGUI_BACKENDS_DIR}/imgui_impl_sdlrenderer2.cpp)

target_link_libraries(chip8 PRIVATE SDL2::SDL2)
