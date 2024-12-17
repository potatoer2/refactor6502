#include "cpu.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace Instructions;

int main(/*int argc, char* argv[]*/)
{
	Mem mem{};
	CPU cpu{};
	/*if (argc != 2)
	{
		std::cerr << "Se ruleaza programul <file_path>"<<std::endl;
		return 1;
	}
	std::string filePath = argv[1];*/
	mem.LoadMachineCodeFromFile("program.bin");
	cpu.Reset(mem);
	InitializeInstructionTable();
	cpu.Execute(1, mem);
	system("pause");
}