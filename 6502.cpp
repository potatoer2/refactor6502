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
	std::string filePath;
	std::cerr << "Pick program to execute"<<std::endl;
	std::cin >> filePath;
	mem.LoadMachineCodeFromFile(filePath);
	cpu.Reset(mem);
	InitializeInstructionTable();
	cpu.Execute(1, mem);
	system("pause");
}