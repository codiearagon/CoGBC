#pragma once

#include <string>

struct opcode_info {
    std::string mnemonic;
    int bytes;
    std::string ticks;
    char z;
    char n;
    char h;
    char c;
};