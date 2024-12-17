#include "cpu.h"
#include "functionHandlers.h"
#include "instructions.h"



void InitializeInstructionTable() {
    CPU::instructionTable[0xA9] = &InstructionHandlers::LDA_IM_Handler;   // LDA Immediate
    CPU::instructionTable[0xA5] = &InstructionHandlers::LDA_ZP_Handler;   // LDA Zero Page
    CPU::instructionTable[0xA6] = &InstructionHandlers::LDX_ZP_Handler;   // LDX Zero Page
    CPU::instructionTable[0xB5] = &InstructionHandlers::LDA_ZPX_Handler;  // LDA Zero Page, X
    CPU::instructionTable[0xAD] = &InstructionHandlers::LDA_ABS_Handler;  // LDA Absolute
    CPU::instructionTable[0xA2] = &InstructionHandlers::LDX_IM_Handler;   // LDX Immediate
    CPU::instructionTable[0x85] = &InstructionHandlers::STA_ZP_Handler;   // STA Zero page
    CPU::instructionTable[0x8D] = &InstructionHandlers::STA_ABS_Handler;  // STA Absolute
    CPU::instructionTable[0x86] = &InstructionHandlers::STX_ZP_Handler;   // STX Zero Page
    CPU::instructionTable[0x8E] = &InstructionHandlers::STX_ABS_Handler;  // STX Absolute
    CPU::instructionTable[0xE8] = &InstructionHandlers::INX_Handler;      // INX
    CPU::instructionTable[0xA0] = &InstructionHandlers::LDY_IM_Handler;   // LDY Immediate
    CPU::instructionTable[0x98] = &InstructionHandlers::TAY_Handler;      // TAY
    CPU::instructionTable[0xA8] = &InstructionHandlers::TAY_Handler;      // TYA
    CPU::instructionTable[0xAA] = &InstructionHandlers::TAX_Handler;      // TAX
    CPU::instructionTable[0x65] = &InstructionHandlers::ADC_ZP_Handler;   // ADC Zero Page
    CPU::instructionTable[0xE5] = &InstructionHandlers::SBC_ZP_Handler;   // SBC Zero Page
    CPU::instructionTable[0x69] = &InstructionHandlers::ADC_Handler;      // ADC Immediate
    CPU::instructionTable[0xE9] = &InstructionHandlers::SBC_Handler;      // SBC Immediate
    CPU::instructionTable[0x29] = &InstructionHandlers::AND_Handler;      // AND
    CPU::instructionTable[0x49] = &InstructionHandlers::EOR_IM_Handler;   // EOR
    CPU::instructionTable[0x90] = &InstructionHandlers::BCC_Handler;      // BCC
    CPU::instructionTable[0xB0] = &InstructionHandlers::BCS_Handler;      // BCS
    CPU::instructionTable[0xF0] = &InstructionHandlers::BEQ_Handler;      // BEQ
    CPU::instructionTable[0x30] = &InstructionHandlers::BMI_Handler;      // BMI
    CPU::instructionTable[0xD0] = &InstructionHandlers::BNE_Handler;      // BNE
    CPU::instructionTable[0x10] = &InstructionHandlers::BPL_Handler;      // BPL
    CPU::instructionTable[0x50] = &InstructionHandlers::BVC_Handler;      // BVC
    CPU::instructionTable[0x70] = &InstructionHandlers::BVS_Handler;      // BVS
    CPU::instructionTable[0x38] = &InstructionHandlers::SEC_Handler;      // SEC
    CPU::instructionTable[0x18] = &InstructionHandlers::CLC_Handler;      // CLC
    CPU::instructionTable[0xD8] = &InstructionHandlers::CLD_Handler;      // CLD
    CPU::instructionTable[0x58] = &InstructionHandlers::CLI_Handler;      // CLI
    CPU::instructionTable[0xB8] = &InstructionHandlers::CLV_Handler;      // CLV
    CPU::instructionTable[0xC9] = &InstructionHandlers::CMP_Handler;      // CMP
    CPU::instructionTable[0xC6] = &InstructionHandlers::DEC_Handler;      // DEC
    CPU::instructionTable[0x88] = &InstructionHandlers::DEY_Handler;      // DEY
    CPU::instructionTable[0xE6] = &InstructionHandlers::INC_Handler;      // INC
    CPU::instructionTable[0x20] = &InstructionHandlers::JSR_Handler;      // JSR
    CPU::instructionTable[0x4C] = &InstructionHandlers::JMP_Handler;      // JMP
    CPU::instructionTable[0x60] = &InstructionHandlers::RTS_Handler;      // RTS
    CPU::instructionTable[0x48] = &InstructionHandlers::PHA_Handler;      // PHA
    CPU::instructionTable[0x68] = &InstructionHandlers::PLA_Handler;      // PLA
    CPU::instructionTable[0x28] = &InstructionHandlers::PLP_Handler;      // PLP
    CPU::instructionTable[0xEA] = &InstructionHandlers::NOP_Handler;      // NOP
    CPU::instructionTable[0x09] = &InstructionHandlers::ORA_Handler;      // ORA
    CPU::instructionTable[0x08] = &InstructionHandlers::PHP_Handler;      // PHP
}










