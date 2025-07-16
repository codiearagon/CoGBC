#include "cpu.h"

CPU::CPU() {
    initialize_opcode_info();

    pc = 0x0;
}

CPU::~CPU() {}

void CPU::connect_components(Bus *_bus, GBCDebugger *_gbc_debugger) {
    bus = _bus;
    gbc_debugger = _gbc_debugger;
}

uint16_t CPU::fetch() {
    uint8_t inst1 = bus->read(pc);
    uint8_t inst2 = bus->read(pc + 1);
    uint16_t full_inst = (inst1 << 8) | inst2;

    return full_inst;
}

void CPU::decode() {
    uint16_t instruction = fetch();
}

// -------helper methods--------

void CPU::initialize_opcode_info() {

    // misc/control instructions
    inst_set[0x00] = opcode_info{"NOP", 1, "4", '-', '-', '-', '-'};
    inst_set[0x10] = opcode_info{"STOP n8", 2, "4", '-', '-', '-', '-'};
    inst_set[0x76] = opcode_info{"HALT", 1, "4", '-', '-', '-', '-'};
    inst_set[0xCB] = opcode_info{"PREFIX", 1, "4", '-', '-', '-', '-'};
    inst_set[0xF3] = opcode_info{"DI", 1, "4", '-', '-', '-', '-'};
    inst_set[0xF8] = opcode_info{"EI", 1, "4", '-', '-', '-', '-'};
    
    // jumps/calls instructions
    inst_set[0x20] = opcode_info{"JR NZ, e8", 2, "12/8", '-', '-', '-', '-'};
    inst_set[0x20] = opcode_info{"JR NZ, e8", 2, "12/8", '-', '-', '-', '-'};
    inst_set[0xC0] = opcode_info{"RET NZ, e8", 1, "20/8", '-', '-', '-', '-'};
    inst_set[0xD0] = opcode_info{"RET NC, e8", 1, "20/8", '-', '-', '-', '-'};

    inst_set[0xC2] = opcode_info{"JP NZ, a16", 3, "16/12", '-', '-', '-', '-'};
    inst_set[0xD2] = opcode_info{"JP NC, a16", 3, "16/12", '-', '-', '-', '-'};

    inst_set[0xC3] = opcode_info{"JP a16", 3, "16", '-', '-', '-', '-'};

    inst_set[0xC4] = opcode_info{"CALL NZ, a16", 3, "24/12", '-', '-', '-', '-'};
    inst_set[0xD4] = opcode_info{"CALL NC, a16", 3, "24/12", '-', '-', '-', '-'};

    inst_set[0xC7] = opcode_info{"RST $00", 1, "16", '-', '-', '-', '-'};
    inst_set[0xD7] = opcode_info{"RST $10", 1, "16", '-', '-', '-', '-'};
    inst_set[0xE7] = opcode_info{"RST $20", 1, "16", '-', '-', '-', '-'};
    inst_set[0xF7] = opcode_info{"RST $30", 1, "16", '-', '-', '-', '-'};

    inst_set[0x18] = opcode_info{"JR e8", 2, "12", '-', '-', '-', '-'};
    inst_set[0x28] = opcode_info{"JR Z, e8", 2, "12/8", '-', '-', '-', '-'};
    inst_set[0x38] = opcode_info{"JR C, e8", 2, "12/8", '-', '-', '-', '-'};
    inst_set[0xC8] = opcode_info{"RET Z", 1, "20/8", '-', '-', '-', '-'};
    inst_set[0xD8] = opcode_info{"RET C", 1, "20/8", '-', '-', '-', '-'};

    inst_set[0xC9] = opcode_info{"RET", 1, "16", '-', '-', '-', '-'};
    inst_set[0xD9] = opcode_info{"RETI", 1, "16", '-', '-', '-', '-'};
    inst_set[0xE9] = opcode_info{"JP HL", 1, "4", '-', '-', '-', '-'};

    inst_set[0xCA] = opcode_info{"JP Z, a16", 3, "16/12", '-', '-', '-', '-'};
    inst_set[0xDA] = opcode_info{"JP C, a16", 3, "16/12", '-', '-', '-', '-'};

    inst_set[0xCC] = opcode_info{"CALL Z, a16", 3, "24/12", '-', '-', '-', '-'};
    inst_set[0xDC] = opcode_info{"CALL C, a16", 3, "24/12", '-', '-', '-', '-'};

    inst_set[0xCD] = opcode_info{"CALL a16", 3, "24", '-', '-', '-', '-'};

    inst_set[0xCF] = opcode_info{"RST $08", 1, "16", '-', '-', '-', '-'};
    inst_set[0xDF] = opcode_info{"RST $18", 1, "16", '-', '-', '-', '-'};
    inst_set[0xEF] = opcode_info{"RST $28", 1, "16", '-', '-', '-', '-'};
    inst_set[0xFF] = opcode_info{"RST $38", 1, "16", '-', '-', '-', '-'};
    
    // 8-bit load instructions
    inst_set[0x40] = opcode_info{"LD B, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x50] = opcode_info{"LD D, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x60] = opcode_info{"LD H, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x70] = opcode_info{"LD [HL], B", 1, "8", '-', '-', '-', '-'};
    inst_set[0xE0] = opcode_info{"LDH [a8], A", 2, "12", '-', '-', '-', '-'};
    inst_set[0xF0] = opcode_info{"LDH A, [a8]", 2, "12", '-', '-', '-', '-'};
    
    inst_set[0x41] = opcode_info{"LD B, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x51] = opcode_info{"LD D, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x61] = opcode_info{"LD H, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x71] = opcode_info{"LD [HL], C", 1, "8", '-', '-', '-', '-'};

    inst_set[0x02] = opcode_info{"LD [BC], A", 1, "8", '-', '-', '-', '-'};
    inst_set[0x12] = opcode_info{"LD [DE], A", 1, "8", '-', '-', '-', '-'};
    inst_set[0x22] = opcode_info{"LD [HL+], A", 1, "8", '-', '-', '-', '-'};
    inst_set[0x32] = opcode_info{"LD [HL-], A", 1, "8", '-', '-', '-', '-'};
    inst_set[0x42] = opcode_info{"LD B, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x52] = opcode_info{"LD D, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x62] = opcode_info{"LD H, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x72] = opcode_info{"LD [HL], D", 1, "8", '-', '-', '-', '-'};
    inst_set[0xE2] = opcode_info{"LDH [C], A", 1, "8", '-', '-', '-', '-'};
    inst_set[0xF2] = opcode_info{"LDH A, [C]", 1, "8", '-', '-', '-', '-'};

    inst_set[0x43] = opcode_info{"LD B, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x53] = opcode_info{"LD D, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x63] = opcode_info{"LD H, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x73] = opcode_info{"LD [HL], E", 1, "8", '-', '-', '-', '-'};

    inst_set[0x44] = opcode_info{"LD B, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x54] = opcode_info{"LD D, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x64] = opcode_info{"LD H, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x74] = opcode_info{"LD [HL], H", 1, "8", '-', '-', '-', '-'};

    inst_set[0x45] = opcode_info{"LD B, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x55] = opcode_info{"LD D, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x65] = opcode_info{"LD H, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x75] = opcode_info{"LD [HL], L", 1, "8", '-', '-', '-', '-'};

    inst_set[0x06] = opcode_info{"LD B, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x16] = opcode_info{"LD D, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x26] = opcode_info{"LD H, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x36] = opcode_info{"LD [HL], n8", 1, "12", '-', '-', '-', '-'};
    inst_set[0x46] = opcode_info{"LD B, [HL]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x56] = opcode_info{"LD D, [HL]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x66] = opcode_info{"LD H, [HL]", 1, "8", '-', '-', '-', '-'};

    inst_set[0x47] = opcode_info{"LD B, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x57] = opcode_info{"LD D, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x67] = opcode_info{"LD H, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x77] = opcode_info{"LD [HL], A", 1, "8", '-', '-', '-', '-'};

    inst_set[0x48] = opcode_info{"LD C, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x58] = opcode_info{"LD E, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x68] = opcode_info{"LD L, B", 1, "4", '-', '-', '-', '-'};
    inst_set[0x78] = opcode_info{"LD A, B", 1, "4", '-', '-', '-', '-'};

    inst_set[0x49] = opcode_info{"LD C, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x59] = opcode_info{"LD E, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x69] = opcode_info{"LD L, C", 1, "4", '-', '-', '-', '-'};
    inst_set[0x79] = opcode_info{"LD A, C", 1, "4", '-', '-', '-', '-'};

    inst_set[0x0A] = opcode_info{"LD A, [BC]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x1A] = opcode_info{"LD A, [DE]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x2A] = opcode_info{"LD A, [HL+]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x3A] = opcode_info{"LD A, [HL-]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x4A] = opcode_info{"LD C, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x5A] = opcode_info{"LD E, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x6A] = opcode_info{"LD L, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0x7A] = opcode_info{"LD A, D", 1, "4", '-', '-', '-', '-'};
    inst_set[0xEA] = opcode_info{"LD [a16], A", 3, "16", '-', '-', '-', '-'};
    inst_set[0xFA] = opcode_info{"LD A, [a16]", 3, "16", '-', '-', '-', '-'};

    inst_set[0x4B] = opcode_info{"LD C, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x5B] = opcode_info{"LD E, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x6B] = opcode_info{"LD L, E", 1, "4", '-', '-', '-', '-'};
    inst_set[0x7B] = opcode_info{"LD A, E", 1, "4", '-', '-', '-', '-'};

    inst_set[0x4C] = opcode_info{"LD C, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x5C] = opcode_info{"LD E, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x6C] = opcode_info{"LD L, H", 1, "4", '-', '-', '-', '-'};
    inst_set[0x7C] = opcode_info{"LD A, H", 1, "4", '-', '-', '-', '-'};

    inst_set[0x4D] = opcode_info{"LD C, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x5D] = opcode_info{"LD E, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x6D] = opcode_info{"LD L, L", 1, "4", '-', '-', '-', '-'};
    inst_set[0x7D] = opcode_info{"LD A, L", 1, "4", '-', '-', '-', '-'};

    inst_set[0x0E] = opcode_info{"LD C, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x1E] = opcode_info{"LD E, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x2E] = opcode_info{"LD L, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x3E] = opcode_info{"LD A, n8", 2, "8", '-', '-', '-', '-'};
    inst_set[0x4E] = opcode_info{"LD C, [HL]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x5E] = opcode_info{"LD E, [HL]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x6E] = opcode_info{"LD L, [HL]", 1, "8", '-', '-', '-', '-'};
    inst_set[0x7E] = opcode_info{"LD A, [HL]", 1, "8", '-', '-', '-', '-'};

    inst_set[0x4F] = opcode_info{"LD C, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x5F] = opcode_info{"LD E, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x6F] = opcode_info{"LD L, A", 1, "4", '-', '-', '-', '-'};
    inst_set[0x7F] = opcode_info{"LD A, A", 1, "4", '-', '-', '-', '-'};
    
    // 16-bit load instructions
    inst_set[0x01] = opcode_info{"LD BC, n16", 3, "12", '-', '-', '-', '-'};
    inst_set[0x11] = opcode_info{"LD DE, n16", 3, "12", '-', '-', '-', '-'};
    inst_set[0x21] = opcode_info{"LD HL, n16", 3, "12", '-', '-', '-', '-'};
    inst_set[0x31] = opcode_info{"LD SP, n16", 3, "12", '-', '-', '-', '-'};
    inst_set[0xC1] = opcode_info{"POP BC", 1, "12", '-', '-', '-', '-'};
    inst_set[0xD1] = opcode_info{"POP DE", 1, "12", '-', '-', '-', '-'};
    inst_set[0xE1] = opcode_info{"POP HL", 1, "12", '-', '-', '-', '-'};
    inst_set[0xF1] = opcode_info{"POP AF", 1, "12", 'Z', 'N', 'H', 'C'};

    inst_set[0xC5] = opcode_info{"PUSH BC", 1, "16", '-', '-', '-', '-'};
    inst_set[0xD5] = opcode_info{"PUSH DE", 1, "16", '-', '-', '-', '-'};
    inst_set[0xE5] = opcode_info{"PUSH HL", 1, "16", '-', '-', '-', '-'};
    inst_set[0xF5] = opcode_info{"PUSH AF", 1, "16", '-', '-', '-', '-'};

    inst_set[0x08] = opcode_info{"LD [a16], SP", 3, "20", '-', '-', '-', '-'};
    inst_set[0xF8] = opcode_info{"POP HL, SP + e8", 2, "12", '0', '0', 'H', 'C'};

    inst_set[0xF9] = opcode_info{"LD SP, HL", 1, "8", '-', '-', '-', '-'};

    // 8-bit arithmetic / logical instructions
    inst_set[0x80] = opcode_info{"ADD A, B", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x90] = opcode_info{"SUB A, B", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA0] = opcode_info{"AND A, B", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB0] = opcode_info{"OR A, B", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x81] = opcode_info{"ADD A, C", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x91] = opcode_info{"SUB A, C", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA1] = opcode_info{"AND A, C", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB1] = opcode_info{"OR A, C", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x82] = opcode_info{"ADD A, D", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x92] = opcode_info{"SUB A, D", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA2] = opcode_info{"AND A, D", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB2] = opcode_info{"OR A, D", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x83] = opcode_info{"ADD A, E", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x93] = opcode_info{"SUB A, E", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA3] = opcode_info{"AND A, E", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB3] = opcode_info{"OR A, E", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x04] = opcode_info{"INC B", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x14] = opcode_info{"INC D", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x24] = opcode_info{"INC H", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x34] = opcode_info{"INC [HL]", 1, "12", 'Z', '0', 'H', '-'};
    inst_set[0x84] = opcode_info{"ADD A, H", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x94] = opcode_info{"SUB A, H", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA4] = opcode_info{"AND A, H", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB4] = opcode_info{"OR A, H", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x05] = opcode_info{"DEC B", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x15] = opcode_info{"DEC D", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x25] = opcode_info{"DEC H", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x35] = opcode_info{"DEC [HL]", 1, "12", 'Z', '1', 'H', '-'};
    inst_set[0x85] = opcode_info{"ADD A, L", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x95] = opcode_info{"SUB A, L", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA5] = opcode_info{"AND A, L", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB5] = opcode_info{"OR A, L", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x86] = opcode_info{"ADD A, [HL]", 1, "8", 'Z', '0', 'H', 'C'};
    inst_set[0x96] = opcode_info{"SUB A, [HL]", 1, "8", 'Z', '1', 'H', 'C'};
    inst_set[0xA6] = opcode_info{"AND A, [HL]", 1, "8", 'Z', '0', '1', '0'};
    inst_set[0xB6] = opcode_info{"OR A, [HL]", 1, "8", 'Z', '0', '0', '0'};
    inst_set[0xC6] = opcode_info{"ADD A, n8", 2, "8", 'Z', '0', 'H', 'C'};
    inst_set[0xD6] = opcode_info{"SUB A, n8", 2, "8", 'Z', '1', 'H', 'C'};
    inst_set[0xE6] = opcode_info{"AND A, n8", 2, "8", 'Z', '0', '1', '0'};
    inst_set[0xF6] = opcode_info{"OR A, n8", 2, "8", 'Z', '0', '0', '0'};

    inst_set[0x27] = opcode_info{"DAA", 1, "4", 'Z', '-', '0', 'C'};
    inst_set[0x37] = opcode_info{"SCF", 1, "4", '-', '0', '0', '1'};
    inst_set[0x87] = opcode_info{"ADD A, A", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x97] = opcode_info{"SUB A, A", 1, "4", '1', '1', '0', '0'};
    inst_set[0xA7] = opcode_info{"AND A, A", 1, "4", 'Z', '0', '1', '0'};
    inst_set[0xB7] = opcode_info{"OR A, A", 1, "4", 'Z', '0', '0', '0'};

    inst_set[0x88] = opcode_info{"ADC A, B", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x98] = opcode_info{"SBC A, B", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA8] = opcode_info{"XOR A, B", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xB8] = opcode_info{"CP A, B", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x89] = opcode_info{"ADC A, C", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x99] = opcode_info{"SBC A, C", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xA9] = opcode_info{"XOR A, C", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xB9] = opcode_info{"CP A, C", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x8A] = opcode_info{"ADC A, D", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x9A] = opcode_info{"SBC A, D", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xAA] = opcode_info{"XOR A, D", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xBA] = opcode_info{"CP A, D", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x8B] = opcode_info{"ADC A, E", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x9B] = opcode_info{"SBC A, E", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xAB] = opcode_info{"XOR A, E", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xBB] = opcode_info{"CP A, E", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x0C] = opcode_info{"INC C", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x1C] = opcode_info{"INC E", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x2C] = opcode_info{"INC L", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x3C] = opcode_info{"INC A", 1, "4", 'Z', '0', 'H', '-'};
    inst_set[0x8C] = opcode_info{"ADC A, H", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x9C] = opcode_info{"SBC A, H", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xAC] = opcode_info{"XOR A, H", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xBC] = opcode_info{"CP A, H", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x0D] = opcode_info{"DEC C", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x1D] = opcode_info{"DEC E", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x2D] = opcode_info{"DEC L", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x3D] = opcode_info{"DEC A", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0x8D] = opcode_info{"ADC A, L", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x9D] = opcode_info{"SBC A, L", 1, "4", 'Z', '1', 'H', 'C'};
    inst_set[0xAD] = opcode_info{"XOR A, L", 1, "4", 'Z', '0', '0', '0'};
    inst_set[0xBD] = opcode_info{"CP A, L", 1, "4", 'Z', '1', 'H', 'C'};

    inst_set[0x8E] = opcode_info{"ADC A, [HL]", 1, "8", 'Z', '0', 'H', 'C'};
    inst_set[0x9E] = opcode_info{"SBC A, [HL]", 1, "8", 'Z', '1', 'H', 'C'};
    inst_set[0xAE] = opcode_info{"XOR A, [HL]", 1, "8", 'Z', '0', '0', '0'};
    inst_set[0xBE] = opcode_info{"CP A, [HL]", 1, "8", 'Z', '1', 'H', 'C'};
    inst_set[0xCE] = opcode_info{"ADC A, n8", 2, "8", 'Z', '0', 'H', 'C'};
    inst_set[0xDE] = opcode_info{"SBC A, n8", 2, "8", 'Z', '1', 'H', 'C'};
    inst_set[0xEE] = opcode_info{"XOR A, n8", 2, "8", 'Z', '0', '0', '0'};
    inst_set[0xFE] = opcode_info{"CP  A, n8", 2, "8", 'Z', '1', 'H', 'C'};

    inst_set[0x2F] = opcode_info{"CPL", 1, "4", '-', '1', '1', '-'};
    inst_set[0x3F] = opcode_info{"CCF", 1, "4", '-', '0', '0', 'C'};
    inst_set[0x8F] = opcode_info{"ADC A, A", 1, "4", 'Z', '0', 'H', 'C'};
    inst_set[0x9F] = opcode_info{"SBC A, A", 1, "4", 'Z', '1', 'H', '-'};
    inst_set[0xAF] = opcode_info{"XOR A, A", 1, "4", '1', '0', '0', '0'};
    inst_set[0xBF] = opcode_info{"CP A, A", 1, "4", '1', '1', '0', '0'};

    // 16-bit arithmetic / logical instructions
    inst_set[0x03] = opcode_info{"INC BC", 1, "8", '-', '-', '-', '-'};
    inst_set[0x13] = opcode_info{"INC DE", 1, "8", '-', '-', '-', '-'};
    inst_set[0x23] = opcode_info{"INC HL", 1, "8", '-', '-', '-', '-'};
    inst_set[0x33] = opcode_info{"INC SP", 1, "8", '-', '-', '-', '-'};

    inst_set[0xE8] = opcode_info{"ADD SP, e8", 2, "16", '0', '0', 'H', 'C'};

    inst_set[0x09] = opcode_info{"ADD HL, BC", 1, "8", '-', '0', 'H', 'C'};
    inst_set[0x19] = opcode_info{"ADD HL, DE", 1, "8", '-', '0', 'H', 'C'};
    inst_set[0x29] = opcode_info{"ADD HL, HL", 1, "8", '-', '0', 'H', 'C'};
    inst_set[0x39] = opcode_info{"ADD HL, SP", 1, "8", '-', '0', 'H', 'C'};

    inst_set[0x0B] = opcode_info{"DEC BC", 1, "8", '-', '-', '-', '-'};
    inst_set[0x1B] = opcode_info{"DEC DE", 1, "8", '-', '-', '-', '-'};
    inst_set[0x2B] = opcode_info{"DEC HL", 1, "8", '-', '-', '-', '-'};
    inst_set[0x3B] = opcode_info{"DEC SP", 1, "8", '-', '-', '-', '-'};

    // 8-bit shift, rotate, and bit instructions (unprefixed)
    inst_set[0x07] = opcode_info{"RLCA", 1, "4", '0', '0', '0', 'C'};
    inst_set[0x17] = opcode_info{"RLC", 1, "4", '0', '0', '0', 'C'};

    inst_set[0x0F] = opcode_info{"RRCA", 1, "4", '0', '0', '0', 'C'};
    inst_set[0x1F] = opcode_info{"RRA", 1, "4", '0', '0', '0', 'C'};
}
