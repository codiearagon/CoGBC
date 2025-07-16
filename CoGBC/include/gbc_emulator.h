#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <wx/wx.h>

#include "wx/gbc_debugger.h"
#include "cpu.h"
#include "bus.h"
#include "wram.h"

class GBCEmulator {
    public:
        GBCEmulator();
        ~GBCEmulator();
        
        static bool is_debugging();

        void load_rom(std::string file_path, std::string file_name);
        void open_debugger();
        void close_debugger();

        void run(); // main loop
        void close();
    private:
        inline static bool debugging_enabled;
        bool emulator_running;

        GBCDebugger *gbc_debugger;
        CPU cpu;
        WRAM wram;
        Bus bus;

        void handle_events();
        void handle_window_events(SDL_Event& event);
};