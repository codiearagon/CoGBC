#include "gbc_emulator.h"

#include <fstream>
#include <iostream>

GBCEmulator::GBCEmulator() {
    std::cout << "Initializing GBC" << std::endl;
    
    gbc_debugger = new GBCDebugger();
    debugging_enabled = false;

    cpu.connect_bus(&bus);
    wram.connect_bus(&bus);
    bus.connect_components(&cpu, &wram);
}

GBCEmulator::~GBCEmulator() {
    close();
}

bool GBCEmulator::is_debugging() {
    return debugging_enabled;
}

void GBCEmulator::load_rom(std::string file_name) {
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);

    if(!file) {
        std::cerr << "Failed to open file\n";
        return;
    }
    
    std::streamsize size = file.tellg();
    char* buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for(long i = 0; i < size; ++i) {
        std::cout << "reading: " << buffer[i] << std::endl;
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
        
        if(debugging_enabled) gbc_debugger->Draw(); // only trigger debugger drawing if it debugger is open
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