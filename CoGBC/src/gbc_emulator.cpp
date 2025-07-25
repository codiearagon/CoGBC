#include "gbc_emulator.h"

#include <fstream>
#include <iostream>

GBCEmulator::GBCEmulator() {
    gbc_debugger = new GBCDebugger();
    debugging_enabled = false;

    cpu.connect_components(&bus, gbc_debugger);
    wram.connect_bus(&bus);
    bus.connect_components(&cpu, &wram);

    gbc_debugger->log_instruction(opcode_info{ "LD A B", 1, "2", 'Z', '0', '1', '-' });
    gbc_debugger->set_register("h", 101);
    gbc_debugger->set_flag("c", true);
    gbc_debugger->set_flag("p", false);
}

GBCEmulator::~GBCEmulator() {
}

bool GBCEmulator::is_debugging() {
    return debugging_enabled;
}

void GBCEmulator::load_rom(std::string file_path, std::string file_name) {
    gbc_debugger->log_message("Loading rom: " + file_name);

    std::ifstream file(file_path, std::ios::binary | std::ios::ate);

    if(!file) {
        gbc_debugger->log_message("Failed to load rom: " + file_name);
        return;
    }
    
    std::streamsize size = file.tellg();
    char* buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for(long i = 0; i < size; ++i) {
        
    }

    delete[] buffer;
}

void GBCEmulator::open_debugger() {
    debugging_enabled = true;
    gbc_debugger->Show();
}

void GBCEmulator::close_debugger() {
    debugging_enabled = false;
    gbc_debugger->Hide();
}

void GBCEmulator::run() {
    emulator_running = true;
    
    while(emulator_running) {
        handle_events();
    }
}

void GBCEmulator::close() {
    debugging_enabled = false;
    emulator_running = false;

    SDL_Quit();
}

void GBCEmulator::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                emulator_running = false;
            break;
        }
    }
}

void GBCEmulator::handle_window_events(SDL_Event& event) {

}