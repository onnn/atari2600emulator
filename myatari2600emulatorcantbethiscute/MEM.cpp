#include <iostream>
#include <fstream>
#include "MEM.h"

class CPU;

unsigned char* MEM::mem;

void MEM::AllocateMemory(const char* filename) {

		int fileSize = 0;
		//open the file
		std::fstream infile(filename, std::ios::in | std::ios::binary);
		if (infile.good())
		{

			//Seek to the end of the file, get the last position. This tells the filesize
			infile.seekg(0, std::fstream::end);
			fileSize = infile.tellg();
		}
		else { std::cout << "bad file" << std::endl; }

		//allocate the memory the size of the file
		mem = new unsigned char[65536] {0};

		infile.seekg(0);
		
		for (int i = 0xFFFF-fileSize + 1; i <= 0xFFFF; i++)
		{
			mem[i] = infile.get();
		}
		infile.close();
}


unsigned char MEM::getByte(unsigned short address) {

	return mem[address];

}

void MEM::setByte(unsigned short address, unsigned char value)
{
	mem[address] = value;
}

void MEM::PrintByte(unsigned short address)
{
	std::cout << "Value at " << address << " is " << mem[address] << std::endl;
}

void MEM::CleanUp() {
	delete[] mem;
}

