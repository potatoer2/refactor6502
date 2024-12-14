#pragma once

#include "types.h"


namespace Instructions {
    enum : Byte {
        LDA_IM = 0xA9,
        LDA_ZP = 0xA5,
        LDA_ZPX = 0xB5,
        ADC = 0x69,
        AND = 0x29,
        BCC = 0x90,
        BCS = 0xB0,
        BEQ = 0xF0,
        BMI = 0x30,
        BNE = 0xD0,
        BPL = 0x10,
        BVC = 0x50,
        BVS = 0x70,
        CLC = 0x18,
        CLD = 0xD8,
        CLI = 0x58,
        CLV = 0xB8,
        CMP = 0xC9,
        DEC = 0xC6,
        INC = 0xE6,
        JSR = 0x20,
        JMP = 0x4C,
        RTS = 0x60,
        PHA = 0x48,
        PLA = 0x68,
        NOP = 0xEA,
        ORA = 0x09,
        PHP = 0x08

    };

}
