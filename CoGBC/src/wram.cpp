#include "wram.h"

WRAM::WRAM() {}

WRAM::~WRAM() {}

void WRAM::connect_bus(Bus *_bus) {
    bus = _bus;
}