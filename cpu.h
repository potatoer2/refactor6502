#pragma once



#include "instructions.h"
#include "memory.h"
using namespace Instructions;

struct CPU
{
    Word PC; // program counter
    Word SP; // stack pointer

    Byte A, X, Y; // regs

    Byte C : 1; // carry
    Byte Z : 1; // zero
    Byte I : 1; // IR
    Byte D : 1; // decimal
    Byte B : 1; // break
    Byte V : 1; // overflow
    Byte N : 1; // negative

    typedef void (*InstructionHandler)(CPU& cpu, u32& Cycles, Mem& memory);
    static InstructionHandler instructionTable[256];


    void printReg(Byte reg);
    void modifySP();
    Byte FetchByte(u32& Cycles, Mem& memory);
    Word FetchWord(u32& Cycles, Mem& memory);
    Byte ReadByte(u32& Cycles, Mem& memory, Byte Adress);
    void Reset(Mem& memory);
    Word PullWord(u32& Cycles, Mem& memory);
    void ADCSetStatus(Byte Value);
    void SBCSetStatus(Byte Value);
    void ExecuteBranch(u32& Cycles, Mem& memory, bool Condition);
    void LDASetStatus();
    void AndSetStatus();
    void startProg(Mem& memory, u32 cycles);
    InstructionHandler GetInstructionHandler(Byte opcode);
    void InvokeInstruction(Byte opcode, u32& Cycles, Mem& memory);
    void Execute(u32 Cycles, Mem& memory);
};