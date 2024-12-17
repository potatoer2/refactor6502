/*/#include <fstream>
#include <cstdint>

int main()
{
	uint8_t zero = 0x00;
	std::ofstream file("program.bin", std::ios::binary);

	for (int i = 0; i <= 0xFFC; i++)
	{
		file << zero;
	}
	file << 0x80;
	file << zero;
	file << zero;
}*/