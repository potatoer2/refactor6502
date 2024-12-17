#pragma once
#pragma once

#include "cpu.h"
#include "memory.h"
#include "types.h"



struct InstructionHandlers
{
    static void LDA_IM_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.A = cpu.FetchByte(Cycles, memory);
        cpu.LDASetStatus();
    }
    static void LDX_IM_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.X = cpu.FetchByte(Cycles, memory);
        cpu.LDASetStatus();
    }

    static void LDA_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.A = cpu.ReadByte(Cycles, memory, cpu.FetchByte(Cycles, memory));
        cpu.LDASetStatus();
    }

    static void LDA_ZPX_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.A = cpu.ReadByte(Cycles, memory, cpu.FetchByte(Cycles, memory) + cpu.X);
        Cycles--;
        cpu.LDASetStatus();
    }
    static void LDX_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.X = cpu.ReadByte(Cycles, memory, cpu.FetchByte(Cycles, memory));
        cpu.Z = (cpu.X == 0);
        cpu.N = (cpu.X & 0b10000000) > 0;
    }
    static void TAX_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.X = cpu.A;
        cpu.Z = (cpu.X == 0);
        cpu.N = (cpu.X & 0b10000000) > 0;
    }
    static void TAY_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.Y = cpu.A;
        cpu.Z = (cpu.X == 0);
        cpu.N = (cpu.X & 0b10000000) > 0;
        cpu.printReg(cpu.Y);
    }
    static void DEY_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.Y -= 1;
        cpu.Z = (cpu.Y == 0);
        cpu.N = (cpu.Y & 0b10000000) > 0;
    }
    static void TYA_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.Y = cpu.A;
        cpu.Z = (cpu.A == 0);
        cpu.N = (cpu.A & 0b10000000) > 0;
    }
    static void LDY_IM_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.Y = cpu.FetchByte(Cycles, memory);
        cpu.Z = (cpu.Y == 0);
        cpu.N = (cpu.Y & 0b10000000) > 0;

    }
    static void STX_ABS_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        Word Adress = cpu.FetchWord(Cycles, memory);
        memory[Adress] = cpu.X;
    }
    static void INX_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.X += 1;
    }
    static void ADC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ADCSetStatus(cpu.FetchByte(Cycles, memory));
    }

    static void SBC_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        Byte Value = cpu.FetchByte(Cycles, memory);
        u32 Result = cpu.A - Value - ~cpu.C;
        cpu.C = (Result > 0xFF);
        cpu.Z = ((Result & 0xFF) == 0);
        cpu.N = ((Result & 0x80) != 0);
        cpu.V = (~(cpu.A ^Value) & (cpu.A ^ Result) & 0x80) != 0;
        cpu.A = Result & 0xFF;
    }
    static void SBC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.SBCSetStatus(cpu.FetchByte(Cycles, memory));
    }

    static void AND_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.A = cpu.A & cpu.FetchByte(Cycles, memory);
        cpu.AndSetStatus();
    }
    static void EOR_IM_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.A = cpu.A ^ cpu.FetchByte(Cycles, memory);
        cpu.AndSetStatus();
    }

    static void BCC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, !cpu.C);
    }

    static void BCS_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, cpu.C);
    }

    static void BEQ_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, cpu.Z);
    }

    static void BMI_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, cpu.N);
    }

    static void BNE_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, !cpu.Z);
    }

    static void BPL_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, !cpu.N);
    }

    static void BVC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, !cpu.V);
    }

    static void BVS_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.ExecuteBranch(Cycles, memory, cpu.V);
    }

    static void CLC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.C = 0;
    }

    static void CLD_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.D = 0;
    }

    static void CLI_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.I = 0;
    }

    static void CLV_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.V = 0;
    }

    static void SEC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.C = 1;
    }

    static void CMP_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        Byte Value = cpu.FetchByte(Cycles, memory);
        Byte Temp = cpu.A - Value;
        cpu.C = (cpu.A >= Value);
        cpu.Z = (Temp == 0x00);
        cpu.N = (Temp & 0b10000000) > 0;
        printf("CMP: A = 0x%02X, Value = 0x%02X, Z = %d, C = %d, N = %d\n", cpu.A, Value, cpu.Z, cpu.C, cpu.N);
    }

    static void DEC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        memory[cpu.PC - 1] = cpu.FetchByte(Cycles, memory) - 1;
        cpu.Z = (memory[cpu.PC - 1] == 0);
        cpu.N = (memory[cpu.PC - 1] & 0b10000000) > 0;
        Cycles -= 3;
    }

    static void INC_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        memory[cpu.PC - 1] = cpu.FetchByte(Cycles, memory) + 1;
        cpu.Z = (memory[cpu.PC - 1] == 0);
        cpu.N = (memory[cpu.PC - 1] & 0b10000000) > 0;
        Cycles -= 3;
    }

    static void JSR_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        memory.WriteWord(Cycles, cpu.PC - 1, cpu.SP - 2);
        cpu.SP -= 2;
        cpu.modifySP();
        cpu.PC = cpu.FetchWord(Cycles, memory);
    }

    static void JMP_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.PC = cpu.FetchWord(Cycles, memory);
        printf("JMP to 0x%X\n", cpu.PC);
        Cycles--;
        cpu.printReg(cpu.A);
    }

    static void RTS_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.PC = cpu.PullWord(Cycles, memory) + 1;
        Cycles--;
    }

    static void PHA_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        if (cpu.SP == 0x0100) {
            std::cerr << "Stack underflow!" << std::endl;
            exit(1);
        }
        cpu.SP--;
        cpu.modifySP();
        memory[cpu.SP] = cpu.A;
        Cycles -= 3;
    }

    static void PLA_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        if (cpu.SP == 0x01FF) {
            std::cerr << "Stack overflow!" << std::endl;
            exit(1);
        }
        cpu.A = memory[cpu.SP];
        cpu.SP++;
        cpu.modifySP();
        Cycles -= 3;
    }

    static void NOP_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        cpu.PC++;
    }

    static void ORA_Handler(CPU& cpu, u32& Cycles, Mem& memory) {
        Byte Value = cpu.FetchByte(Cycles, memory);
        cpu.A = cpu.A | Value;

        if (cpu.A == 0) {
            cpu.Z = 1;
        }
        if ((cpu.A & 0b10000000) > 0) {
            cpu.N = 1;
        }
    }

    static void PHP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.SP--;
        cpu.modifySP();
        if (cpu.C == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b00000001;
        }
        if (cpu.Z == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b00000010;
        }
        if (cpu.I == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b00000100;
        }
        if (cpu.D == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b00001000;
        }
        if (cpu.B == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b00010000;
        }
        if (cpu.V == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b01000000;
        }
        if (cpu.N == 1) {
            memory[cpu.SP] = memory[cpu.SP] & 0b10000000;
        }
        Cycles -= 3;
    }
    static void PLP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.SP++;
        cpu.modifySP();
        if (memory[cpu.SP] & (1 << 0))
        {
            cpu.C = 1;
        }
        if (memory[cpu.SP] & (1 << 1))
        {
            cpu.Z = 1;
        }
        if (memory[cpu.SP] & (1 << 2))
        {
            cpu.I = 1;
        }
        if (memory[cpu.SP] & (1 << 3))
        {
            cpu.D = 1;
        }
        if (memory[cpu.SP] & (1 << 4))
        {
            cpu.B = 1;
        }
        if (memory[cpu.SP] & (1 << 6))
        {
            cpu.V = 1;
        }
        if (memory[cpu.SP] & (1 << 7))
        {
            cpu.N = 1;
        }

    }
    static void LDA_ABS_Handler(CPU& cpu, u32& Cycles, Mem& memory) 
    {
        Word Adress = cpu.FetchWord(Cycles, memory);
        cpu.A = memory[Adress];
        cpu.LDASetStatus();
    }
    static void STA_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory) 
    {
        Byte Adress = cpu.FetchByte(Cycles, memory);
        memory[Adress] = cpu.A;
    }
    static void STA_ABS_Handler(CPU& cpu, u32& Cycles, Mem& memory) 
    {
        Word Adress = cpu.FetchWord(Cycles, memory);
        memory[Adress] = cpu.A;
    }

    static void STX_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        Word Adress = cpu.FetchByte(Cycles, memory);
        memory[Adress] = cpu.X;
    }
    static void ADC_ZP_Handler(CPU& cpu, u32& Cycles, Mem& memory)
    {
        cpu.ADCSetStatus(memory[cpu.FetchByte(Cycles, memory)]);

    }

    bool operator==(const InstructionHandlers& other) const
    {
        return false;
    }
};


