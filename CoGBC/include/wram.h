#pragma once

#include <array>

#include "bus.h"

class Bus;

class WRAM {
    public:
        WRAM();
        ~WRAM();

        void connect_bus(Bus *_bus);
    private:
        Bus *bus;

        std::array<uint8_t, 32768> data;
};