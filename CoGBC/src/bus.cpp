#include "bus.h"

Bus::Bus() {
}

Bus::~Bus() {}

void Bus::connect_components(CPU *_cpu, WRAM *_wram) {
    cpu = _cpu;
    wram = _wram;
}

uint8_t Bus::read(uint16_t addr) const {
    return 0;
}