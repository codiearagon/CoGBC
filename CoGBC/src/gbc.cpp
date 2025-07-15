#include "gbc.h"

#include <fstream>
#include <iostream>

GBC::GBC() {
    std::cout << "Initializing GBC" << std::endl;

    debugging_enabled = false;

    cpu.connect_bus(&bus);
    wram.connect_bus(&bus);
    bus.connect_components(&cpu, &wram);
}

GBC::~GBC() {
    close();
}

bool GBC::is_debugging() {
    return debugging_enabled;
}

void GBC::load_rom(std::string file_name) {
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
    }

    delete[] buffer;
}

void GBC::open_debugger() {
    debugging_enabled = true;
    gbc_debugger.show_debugger();
}

void GBC::close_debugger() {
    debugging_enabled = false;
    gbc_debugger.hide_debugger();
}

void GBC::run() {
    emulator_running = true;
    open_debugger();
    
    while(emulator_running) {
        handle_events();
        
        if(debugging_enabled) gbc_debugger.draw(); // only trigger debugger drawing if it debugger is open
    }
}

void GBC::close() {
    debugging_enabled = false;
    emulator_running = false;

    SDL_Quit();
}

void GBC::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                emulator_running = false;
            break;
        }
    }
}

void GBC::handle_window_events(SDL_Event& event) {

}