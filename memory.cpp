#pragma once
#include "memory.h"

bool useCycles ;
static constexpr u32 MAX_MEM = 1024 * 64;
Byte Data[MAX_MEM];

void Mem::Initialise() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0; // SET MEMORY TO 0
    }
}

Byte Mem::operator[](u32 Address) const {
    return Data[Address];
}

Byte& Mem::operator[](u32 Address) {
    return Data[Address];
}

void Mem::WriteWord(u32& Cycle, Word DataToWrite, u32 Adress) {
    Data[Adress] = DataToWrite & 0xFF;
    Data[Adress + 1] = (DataToWrite >> 8);
    Cycle -= 2;
}
void Mem::LoadMachineCodeFromFile(const std::string& filename) {
    Initialise();
    /*do {
        std::cerr << "Do you want to utilise cycles? [Y/N]";
    } while (tolower(std::cin.get()) != 'y' || tolower(std::cin.get()) != 'n');
    if (tolower(std::cin.get()) == 'y')
    {
        useCycles == true;
    }
    else if (tolower(std::cin.get()) == 'n')
    {
        useCycles == false;
    }*/

    
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    // Get the file size
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Print the file size
    std::cout << "File size: " << fileSize << " bytes" << std::endl;

    if (fileSize > MAX_MEM) {
        std::cerr << "Error: File size exceeds memory capacity (" << MAX_MEM << " bytes)." << std::endl;
        return;
    }



    file.read(reinterpret_cast<char*>(Data), MAX_MEM);
}

