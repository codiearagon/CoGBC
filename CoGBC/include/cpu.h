#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "opcode_info.h"
#include "wx/gbc_debugger.h"
#include "bus.h"

class Bus;

class CPU {
    public:
        CPU();
        ~CPU();
        
        void connect_components(Bus *_bus, GBCDebugger *_gbc_debugger);
        uint16_t fetch();
        void decode();
        void alu(uint8_t in1, uint8_t in2, uint16_t output);
        void idu(uint16_t in1, uint16_t output); 

    private:
        std::unordered_map<uint8_t, opcode_info> inst_set;
        GBCDebugger *gbc_debugger;

        Bus *bus;

        uint16_t pc;
        uint16_t sp;

        // AF registers
        uint8_t a;
        uint8_t f;

        // general-purpose registers (BC, DE, HL)
        uint16_t bc;
        uint16_t de;
        uint16_t hl;

        // special-purpose registers (IR, IE)
        uint8_t inst_reg;
        uint8_t intr_enable;

        // helper methods
        void initialize_opcode_info();
};