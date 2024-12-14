#include "cpu.h"




// 6502 proccesor emulation,
// some procceses are skiped for simplification issue



//TODO Fix Branches not working, make an assembler
//The compiler has issues findinf the 






CPU::InstructionHandler CPU::instructionTable[256] = { nullptr };
void CPU::printA() {
    if (A == 0xFF) {
        std::cout << "A Register is NULL (uninitialized)" << std::endl;
    }
    else {
        std::cout << "A Register: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(A) << std::dec << std::endl;
    }
}

void CPU::modifySP()
{
    if (SP < 0x0100) {
        SP = 0x01FF;
    }
    else if (SP > 0x01FF) {
        SP = 0x0100;
    }
}

Byte CPU::FetchByte(u32& Cycles, Mem& memory) {
    if (PC >= memory.MAX_MEM) {
        std::cerr << "Program Counter out of bounds: " << std::hex << PC << std::dec << std::endl;
        exit(1); // Or handle error appropriately
    }
    Byte Data = memory[PC];
    printf("Fetching byte: 0x%X at PC: 0x%X\n", Data, PC);
    PC++;
    Cycles--;
    return Data;
}



Word CPU::FetchWord(u32& Cycles, Mem& memory) {
    Word Data = memory[PC];
    PC++;
    Data |= (memory[PC] << 8);
    PC++;
    Cycles -= 2;
    return Data;
}

Byte CPU::ReadByte(u32& Cycles, Mem& memory, Byte Adress) {
    Byte Data = memory[Adress];
    Cycles--;
    return Data;
}

void CPU::Reset(Mem& memory) {
    PC = memory[0xFFFC] | (memory[0xFFFD] << 8);
    printf("Memory[0xFFFC]: 0x%X\n", memory[0xFFFC]);
    printf("Memory[0xFFFD]: 0x%X\n", memory[0xFFFD]);

    printf("Reset Vector: 0x%X\n", PC);
    SP = 0x01FF;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;

    // InitializeInstructionTable();

}

Word CPU::PullWord(u32& Cycles, Mem& memory) {
    Byte LowByte = memory[SP];
    SP++;
    modifySP();
    Byte HighByte = memory[SP];
    SP++;
    modifySP();
    Cycles -= 2;

    return static_cast<Word>(HighByte) << 8 | LowByte;
}

void CPU::ADCSetStatus(Byte Value) {
    u32 Result = A + Value + C;
    C = (Result > 0xFF);
    Z = ((Result & 0xFF) == 0);
    N = ((Result & 0x80) != 0);
    V = (~(A ^ Value) & (A ^ Result) & 0x80) != 0;
    A = Result & 0xFF;
}

void CPU::ExecuteBranch(u32& Cycles, Mem& memory, bool Condition) {
    Byte Offset = FetchByte(Cycles, memory);

    if (Condition) {
        Word TargetPC = PC + static_cast<int8_t>(Offset);
        Cycles--;
        if ((PC & 0xFF00) != (TargetPC & 0xFF00)) {
            Cycles--;
        }
        PC = TargetPC;

    }
}

void CPU::LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::AndSetStatus() {
    LDASetStatus();
}
void CPU::startProg(Mem& memory, u32 cycles)
{



    Reset(memory);
    Execute(cycles, memory);


}
CPU::InstructionHandler CPU::GetInstructionHandler(Byte opcode) {

    if (opcode < 256) {
        return instructionTable[opcode];
    }
    else {

        std::cout << "Invalid opcode: " << (opcode) << std::endl;
        return nullptr;
    }
}

void CPU::InvokeInstruction(Byte opcode, u32& Cycles, Mem& memory) {
    CPU::InstructionHandler handler = CPU::GetInstructionHandler(opcode);
    if (handler != nullptr) {
        handler(*this, Cycles, memory);
    }
    else {
        std::cout << "No handler found for opcode: " << static_cast<int>(opcode) << std::endl;
    }
}

void CPU::Execute(u32 Cycles, Mem& memory) {
    while (true) {
        int Instruction = FetchByte(Cycles, memory);
        InvokeInstruction(Instruction, Cycles, memory);

        if (std::cin.get() == ' ') {
            continue;
        }
    }
}









