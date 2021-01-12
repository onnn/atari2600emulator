#pragma once

class MEM {

private:
    static unsigned char* mem;
    unsigned char memSize;

public:
    void AllocateMemory(const char* filename);
    static unsigned char getByte(unsigned short key);
    static void setByte(unsigned short address, unsigned char value);
    static void PrintByte(unsigned short address);
    void CleanUp();
};