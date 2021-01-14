#include <iostream>
#include <intrin.h>
#include <map>
#include "CPU.h"
#include "MEM.h"

class MEM;

unsigned short CPU::programCounter;
unsigned char CPU::accumulator;
unsigned short CPU::stackPointer;
unsigned char CPU::indexRegisterX;
unsigned char CPU::indexRegisterY;
unsigned char CPU::status;
unsigned char CPU::addressBus;
unsigned int CPU::step;

void CPU::Init() {

	programCounter = MEM::getByte(0xFFFC) + MEM::getByte(0xFFFD) * 256;
	accumulator = 0;
	stackPointer = 0x01FF; 
	indexRegisterX = 0;
	indexRegisterX = 0;
	status = 0;
	addressBus = 0;
	step = 0;
}

void CPU::Step() {
	
	void (*p[256]) () = { BRKImplied, ORAIndirectX, NOPImplied, NOPImplied, NOPImplied, 
		ORAZeroPage, ASLZeroPage, NOPImplied, PHPImplied, ORAImmediate, ASLAccumulator,
		NOPImplied, NOPImplied, ORAAbsolute, ASLAbsolute, NOPImplied, BPLRelative,
		ORAIndirectY, NOPImplied, NOPImplied, NOPImplied, ORAZeroPageX, ASLZeroPageX,
		NOPImplied, CLCImplied, ORAAbsoluteY, NOPImplied, NOPImplied, NOPImplied, 
		ORAAbsoluteX, ASLAbsoluteX, NOPImplied, JSRAbsolute, ANDIndirectX, NOPImplied,
		NOPImplied, BITZeroPage, ANDZeroPage, ROLZeroPage, NOPImplied, PLPImplied, 
		ANDImmediate, ROLAccumulator, NOPImplied, BITAbsolute, ANDAbsolute, ROLAbsolute, 
		NOPImplied, BMIRelative, ANDIndirectY, NOPImplied, NOPImplied, NOPImplied, 
		ANDZeroPageX, ROLZeroPageX, NOPImplied, SECImplied, ANDAbsoluteY, NOPImplied, 
		NOPImplied, NOPImplied, ANDAbsoluteX, ROLAbsoluteX, NOPImplied, RTIImplied,
		EORIndirectX, NOPImplied, NOPImplied, NOPImplied, EORZeroPage, LSRZeroPage,
		NOPImplied, PHAImplied, EORImmediate, LSRAccumulator, NOPImplied, JMPAbsolute,
		EORAbsolute, LSRAbsolute, NOPImplied, BVCRelative, EORIndirectY, NOPImplied,
		NOPImplied, NOPImplied, EORZeroPageX, LSRZeroPageX, NOPImplied, CLIImplied, 
		EORAbsoluteY, NOPImplied, NOPImplied, NOPImplied, EORAbsoluteX, LSRAbsoluteX,
		NOPImplied, RTSImplied, ADCIndirectX, NOPImplied, NOPImplied, NOPImplied,
		ADCZeroPage, RORZeroPage, NOPImplied, PLAImplied, ADCImmediate, RORAccumulator,
		NOPImplied, JMPIndirect, ADCAbsolute, RORAbsolute, NOPImplied, BVSRelative,
		ADCIndirectY, NOPImplied, NOPImplied, NOPImplied, ADCZeroPageX, RORZeroPageX,
		NOPImplied, SEIImplied, ADCAbsoluteY, NOPImplied, NOPImplied, NOPImplied, 
		ADCAbsoluteX, RORAbsoluteX, NOPImplied, NOPImplied, STAIndirectX, NOPImplied,
		NOPImplied, STYZeroPage, STAZeroPage, STXZeroPage, NOPImplied, DEYImplied, 
		NOPImplied, TXAImplied, NOPImplied, STYAbsolute, STAAbsolute, STXAbsolute,
		NOPImplied, BCCRelative, STAIndirectY, NOPImplied, NOPImplied, STYZeroPageX,
		STAZeroPageX, STXZeroPageY, NOPImplied, TYAImplied, STAAbsoluteY, TXSImplied,
		NOPImplied, NOPImplied, STAAbsoluteX, NOPImplied, NOPImplied, LDYImmediate,
		LDAIndirectX, LDXImmediate, NOPImplied, LDYZeroPage, LDAZeroPage, LDXZeroPage, 
		NOPImplied, TAYImplied, LDAImmediate, TAXImplied, NOPImplied, LDYAbsolute, 
		LDAAbsolute, LDXAbsolute, NOPImplied, BCSRelative, LDAIndirectY, NOPImplied,
		NOPImplied, LDYZeroPageX, LDAZeroPageX, LDXZeroPageY, NOPImplied, CLVImplied,
		LDAAbsoluteY, TSXImplied, NOPImplied, LDYAbsoluteX, LDAAbsoluteX, LDXAbsoluteY,
		NOPImplied, CPYImmediate, CMPIndirectX, NOPImplied, NOPImplied, CPYZeroPage,
		CMPZeroPage, DECZeroPage, NOPImplied, INYImplied, CMPImmediate, DEXImplied, 
		NOPImplied, CPYAbsolute, CMPAbsolute, DECAbsolute, NOPImplied, BNERelative,
		CMPIndirectY, NOPImplied, NOPImplied, NOPImplied, CMPZeroPageX, DECZeroPageX,
		NOPImplied, CLDImplied, CMPAbsoluteY, NOPImplied, NOPImplied, NOPImplied,
		CMPAbsoluteX, DECAbsoluteX, NOPImplied, CPXImmediate, SBCIndirectX, NOPImplied, 
		NOPImplied, CPXZeroPage, SBCZeroPage, INCZeroPage, NOPImplied, INXImplied,
		SBCImmediate, NOPRealImplied, NOPImplied, CPXAbsolute, SBCAbsolute, INCAbsolute, 
		NOPImplied, BEQRelative, SBCIndirectY, NOPImplied, NOPImplied, NOPImplied, 
		SBCZeroPageX, INCZeroPageX, NOPImplied, SEDImplied, SBCAbsoluteY, NOPImplied, 
		NOPImplied, NOPImplied, SBCAbsoluteX, INCAbsoluteX, NOPImplied};
	PrintValues();
	if (step != 0) { ++programCounter; }

	std::cout << std::dec << "step: " << step << std::endl;
	

	std::cout << std::hex << (int)programCounter << std::endl;
	std::cout << std::hex << (int)programCounter - 0xf000 ;

	unsigned char instruction = MEM::getByte(programCounter);

	std::cout << "instruction: " << std::hex << (int)instruction << " " << std::endl;
	std::cout << "next bytes: " << std::hex << (int)MEM::getByte(programCounter + 1) << " " << (int)MEM::getByte(programCounter + 2) << " " << (int)MEM::getByte(programCounter + 3) << std::endl;
	
	if (step == 550) {
	
		interrupt();
	
	}
	if (step == 650) {
		interrupt();
	}
	if (step == 901) {

		interrupt();
	}
	if (step == 1400) {
		interrupt();
	}
	

	(*p[instruction])();

	if (step >= 900) {
	}
	std::cout << std::endl;
	++step;
}

void CPU::PrintValues()
{
	unsigned char carry = (status >> 0) & 1U;
	unsigned char zero = (status >> 1) & 1U;
	unsigned char interruptDisable = (status >> 2) & 1U;
	unsigned char decimalMode = (status >> 3) & 1U;
	unsigned char breakCommand = (status >> 4) & 1U;
	unsigned char expansion = (status >> 5) & 1U;
	unsigned char overflow = (status >> 6) & 1U;
	unsigned char negative = (status >> 7) & 1U;

		std::cout << "PC: " << std::hex << (int)programCounter << std::endl;
	std::cout << "SP: " << std::hex << (int)stackPointer << std::endl;
	std::cout << "A: " << std::hex <<  (int)accumulator << std::endl;
	std::cout << "IX: " << std::hex << (int)indexRegisterX << std::endl;
	std::cout << "IY: " << std::hex << (int)indexRegisterY << std::endl;
	std::cout << "status: " << (unsigned short)status << std::endl;
	std::cout << "negative: " << (unsigned short)negative << std::endl;
	std::cout << "zero: " << (unsigned short)zero << std::endl;
	std::cout << "carry: " << (unsigned short)carry << std::endl;
	std::cout << "overflow: " << (unsigned short)overflow << std::endl;
	std::cout << "interruptdisable " << (unsigned short)interruptDisable << std::endl;
	std::cout << "decimalMode: " << (unsigned short)decimalMode << std::endl;
	std::cout << "breakCommand: " << (unsigned short)breakCommand << std::endl;
	std::cout << "stack: " << std::hex <<
		(int)MEM::getByte(0x00FF) << " " <<  
		(int)MEM::getByte(0x00FE) << " " <<
		(int)MEM::getByte(0x00FD) << " " <<
		(int)MEM::getByte(0x00FC) << " " <<
		(int)MEM::getByte(0x00FB) << " " <<
		(int)MEM::getByte(0x00FA) << " " <<
		(int)MEM::getByte(0x00F9) << " " <<
		(int)MEM::getByte(0x00F8) << " " <<
		(int)MEM::getByte(0x00F7) << " " <<
		(int)MEM::getByte(0x00F6) << " " <<
		(int)MEM::getByte(0x00F5) << " " << std::endl;
	std::cout << "=============================================" << std::endl;
}

void CPU::LDAImmediate() {

	//Currently the program counter is on the byte with the instruction. For this instruction,
	//the operand is on the next byte, so increment it then operate on that.
	accumulator = MEM::getByte(++programCounter); 


	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) { 

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;
}

void CPU::LDAZeroPage() {

	//high byte is zero, low byte is operand (address where the new accumulator value lies)
	accumulator = MEM::getByte(++programCounter + 0 * 256);
		if (accumulator == 0) {

			status |= 1U << 1;
		}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAZeroPageX() {

	accumulator = MEM::getByte(++programCounter + 0 * 256 + indexRegisterX);
	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAAbsolute() {

	accumulator = MEM::getByte(++programCounter + ++programCounter * 256);
	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAAbsoluteX() {

	accumulator = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);

	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAAbsoluteY() {

	accumulator = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterY);

	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAIndirectX() {

	unsigned short address = MEM::getByte(++programCounter + 0 * 256 + indexRegisterX);
	accumulator = MEM::getByte(address);

	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::LDAIndirectY() {


	unsigned short address = MEM::getByte(++programCounter + 0 * 256);
	accumulator = MEM::getByte(address) + indexRegisterY;

	if (accumulator == 0) {

		status |= 1U << 1;
	}
	if (((accumulator >> 7) & 1U) == 1) {

		status |= 1U << 7;
	}
	std::cout << "LDA" << std::endl;

}

void CPU::STAAbsolute()
{
	//example Acc value
	//accumulator = 0x86;

	//take next two bytes and make an address
	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	
	
	MEM::setByte(address, accumulator);
	std::cout << "STA" << std::endl;

}

void CPU::STAZeroPage() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256;

	MEM::setByte(address, accumulator);
	
	std::cout << "STA" << std::endl;

}

void CPU::STAZeroPageX() {


	unsigned short address = MEM::getByte(++programCounter) + 0 * 256 + indexRegisterX;

	MEM::setByte(address, accumulator);
	std::cout << "STA" << std::endl;

}

void CPU::STAAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;


	MEM::setByte(address + indexRegisterX, accumulator);
	std::cout << "STA" << std::endl;

}

void CPU::STAAbsoluteY() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;

	MEM::setByte(address + indexRegisterY, accumulator);
	std::cout << "STA" << std::endl;

}

void CPU::STAIndirectX() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256 + indexRegisterX;


	MEM::setByte(MEM::getByte(address), accumulator);
	std::cout << "STA" << std::endl;

}


void CPU::STAIndirectY() {


	unsigned short address = MEM::getByte(++programCounter) + 0 * 256;


	MEM::setByte(MEM::getByte(address) + indexRegisterY, accumulator);
	std::cout << "STA" << std::endl;

}



void CPU::ADCImmediate()
{	
	unsigned char startingAccumulator = accumulator;
	unsigned char addend = MEM::getByte(++programCounter);
	accumulator = accumulator + addend;

	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}
	
	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;
	
	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCZeroPage()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + 0 * 256);
	int addend = MEM::getByte(address);
	accumulator = accumulator + addend;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCZeroPageX()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + 0 * 256 + indexRegisterX);
	int addend = MEM::getByte(address);
	accumulator = accumulator + addend;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCAbsolute()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256);
	int addend = MEM::getByte(address);
	accumulator = accumulator + addend;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCAbsoluteX()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);
	int addend = MEM::getByte(address);
	accumulator = accumulator + addend;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCAbsoluteY()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterY);
	int addend = MEM::getByte(address);
	accumulator = accumulator + addend;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::ADCIndirectX()
{


	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);
	int addendAddress = MEM::getByte(address);
	int addend = MEM::getByte(addendAddress);
	accumulator = accumulator + addend; 

	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}


void CPU::ADCIndirectY()
{


	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256);
	int addendAddress = MEM::getByte(address);
	int addend = MEM::getByte(addendAddress);
	accumulator = accumulator + addend + indexRegisterY;


	//add one for carry
	if (((status >> 0) & 1U) == 1)
	{
		accumulator = accumulator + 1;
	}

	//set carry if it surpasses 255
	if ((startingAccumulator + addend) > 255)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && ((startingAccumulator + addend < -128) || (startingAccumulator + addend > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ADC" << std::endl;

}

void CPU::SBCImmediate() {

	int startingAccumulator = accumulator;
	int subtrahend = MEM::getByte(++programCounter);

	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}

	
	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}


	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}
void CPU::SBCZeroPage()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + 0 * 256);
	int subtrahend = MEM::getByte(address);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}

void CPU::SBCZeroPageX()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + 0 * 256 + indexRegisterX);
	int subtrahend = MEM::getByte(address);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}

void CPU::SBCAbsolute()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256);
	int subtrahend = MEM::getByte(address);
	accumulator = accumulator - subtrahend;



	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}

void CPU::SBCAbsoluteX()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);
	int subtrahend = MEM::getByte(address);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC AbsoluteX" << std::endl;

}

void CPU::SBCAbsoluteY()
{
	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterY);
	int subtrahend = MEM::getByte(address);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit

	std::cout << "SBC" << std::endl;

}

void CPU::SBCIndirectX()
{


	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);
	int subtrahendAddress = MEM::getByte(address);
	int subtrahend = MEM::getByte(subtrahendAddress);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}


void CPU::SBCIndirectY()
{


	int startingAccumulator = accumulator;
	unsigned short address = MEM::getByte(++programCounter + ++programCounter * 256);
	int subtrahendAddress = MEM::getByte(address);
	int subtrahend = MEM::getByte(subtrahendAddress + indexRegisterY);
	accumulator = accumulator - subtrahend;


	//take away if no carry
	if (!(((status >> 0) & 1U) == 1))
	{
		accumulator = accumulator - 1;
	}


	//set carry if it surpasses 255
	if ((startingAccumulator - subtrahend) >= 0)
	{
		status |= 1U << 0;

	}
	else { status &= ~(1UL << 0); } //clear the carry bit (zeroth) of status

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	bool potentialOverflow = false;

	if ((startingAccumulator < -128) || (startingAccumulator > 127))
	{
		potentialOverflow = true;
	}

	if ((potentialOverflow == true) && (((startingAccumulator - subtrahend) < -128) || ((startingAccumulator - subtrahend) > 127)))
	{
		status |= 1U << 6; //set overflow bit

	}
	else { status &= ~(1UL << 6); } //clear the overflow bit 

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "SBC" << std::endl;

}

void CPU::ANDImmediate() {

	accumulator = accumulator & MEM::getByte(++programCounter);
	

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
		std::cout << "AND" << std::endl;

}


void CPU::ANDZeroPage() { 

	unsigned short address = MEM::getByte(++programCounter + (0 * 256));
	accumulator = accumulator & MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}

void CPU::ANDZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	accumulator = accumulator & MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}
void CPU::ANDAbsolute() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256));
	accumulator = accumulator & MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}

void CPU::ANDAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterX);
	accumulator = accumulator & MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}

void CPU::ANDAbsoluteY() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterY);
	accumulator = accumulator & MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}


void CPU::ANDIndirectX() {

	unsigned short address1 = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator & MEM::getByte(address2);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}

void CPU::ANDIndirectY() {

	unsigned short address1 = MEM::getByte(++programCounter + (++programCounter * 256));
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator & MEM::getByte(address2 + indexRegisterY);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "AND" << std::endl;

}


void CPU::ORAImmediate() {

	accumulator = accumulator | MEM::getByte(++programCounter);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}


void CPU::ORAZeroPage() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256));
	accumulator = accumulator | MEM::getByte(address);
	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}

void CPU::ORAZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	accumulator = accumulator | MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}
void CPU::ORAAbsolute() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256));
	accumulator = accumulator | MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}

void CPU::ORAAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterX);
	accumulator = accumulator | MEM::getByte(address);
	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}

void CPU::ORAAbsoluteY() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterY);
	accumulator = accumulator | MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}


void CPU::ORAIndirectX() {

	unsigned short address1 = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator | MEM::getByte(address2);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}

void CPU::ORAIndirectY() {

	unsigned short address1 = MEM::getByte(++programCounter + (++programCounter * 256));
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator | MEM::getByte(address2 + indexRegisterY);
	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "ORA" << std::endl;

}


void CPU::EORImmediate() {

	accumulator = accumulator ^ MEM::getByte(++programCounter);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}


void CPU::EORZeroPage() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256));
	accumulator = accumulator ^ MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}

void CPU::EORZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	accumulator = accumulator ^ MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}
void CPU::EORAbsolute() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256));
	accumulator = accumulator ^ MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}

void CPU::EORAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterX);
	accumulator = accumulator ^ MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}

void CPU::EORAbsoluteY() {

	unsigned short address = MEM::getByte(++programCounter + (++programCounter * 256) + indexRegisterY);
	accumulator = accumulator ^ MEM::getByte(address);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}


void CPU::EORIndirectX() {

	unsigned short address1 = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator ^ MEM::getByte(address2);

	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}

void CPU::EORIndirectY() {

	unsigned short address1 = MEM::getByte(++programCounter + (++programCounter * 256));
	unsigned short address2 = MEM::getByte(address1);
	accumulator = accumulator ^ MEM::getByte(address2 + indexRegisterY);
	//set zero if A is zero
	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((accumulator >> 7) & 1U) == 1) { //if accumulator bit 7 is set

		status |= 1U << 7; //set negative status
	}
	else { status &= ~(1UL << 7); } //clear the negative bit
	std::cout << "EOR" << std::endl;

}




void CPU::SECImplied() {

	status |= 1U << 7;
	std::cout << "SEC" << std::endl;

}

void CPU::CLCImplied() {
	status &= ~(1UL << 7); 
	std::cout << "CLC" << std::endl;

}

void CPU::SEIImplied() {
	status |= 1U << 2;
	std::cout << "SEI" << std::endl;

}

void CPU::CLIImplied() {
	status &= ~(1UL << 2); 
	std::cout << "CLI" << std::endl;

}

void CPU::SEDImplied() {
	status |= 1U << 3;
	std::cout << "SED" << std::endl;

}

void CPU::CLDImplied() {
	status &= ~(1UL << 3);
	std::cout << "CLD" << std::endl;

}

void CPU::CLVImplied() {
	status &= ~(1UL << 6);
	std::cout << "CLV" << std::endl;

}

void CPU::JMPAbsolute() {
	
	unsigned char lowByte = MEM::getByte(++programCounter);
	unsigned char highByte = MEM::getByte(++programCounter);

	programCounter = (lowByte + highByte * 256) -1;
	std::cout << "JMP Absolute" << std::endl;
}

void CPU::JMPIndirect() {

	int pointer = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	unsigned short address = MEM::getByte(pointer);
	programCounter = MEM::getByte(address);

	std::cout << "JMP Indirect" << std::endl;

}

void CPU::BMIRelative() {

	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 7) & 1U) == 1)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BMI" << std::endl;

}

void CPU::BPLRelative() {

	char offset = MEM::getByte(++programCounter);

	if ((((status >> 7) & 1U) == 0)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BPL" << std::endl;

}

void CPU::BCCRelative() {

	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 0) & 1U) == 0)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BCC" << std::endl;

}

void CPU::BCSRelative() {
	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 0) & 1U) == 1)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BCS" << std::endl;

}

void CPU::BEQRelative() {
	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 1) & 1U) == 1)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BEQ" << std::endl;

}

void CPU::BNERelative() {

	signed char offset = MEM::getByte(++programCounter);
	
	if ((((status >> 1) & 1U) == 0)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BNE" << std::endl;

}


void CPU::BVSRelative() {

	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 6) & 1U) == 1)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BVS" << std::endl;

}

void CPU::BVCRelative() {

	signed char offset = MEM::getByte(++programCounter);

	if ((((status >> 6) & 1U) == 0)) {
		programCounter = ++programCounter + offset - 1;
	}

	std::cout << "BVC" << std::endl;

}

void CPU::CMPImmediate() {

	unsigned char value = MEM::getByte(++programCounter);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}
void CPU::CMPZeroPage() {

	unsigned short address = MEM::getByte(++programCounter);
	int value = MEM::getByte(address + (0 * 256));
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}
void CPU::CMPZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address + (0 * 256) + indexRegisterX);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}

void CPU::CMPAbsolute() {

	unsigned char value = MEM::getByte(++programCounter + ++programCounter * 256);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}


void CPU::CMPAbsoluteX() {

	unsigned char value = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterX);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}



void CPU::CMPAbsoluteY() {

	unsigned char value = MEM::getByte(++programCounter + ++programCounter * 256 + indexRegisterY);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}



void CPU::CMPIndirectX() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256) + indexRegisterX);
	unsigned char value = MEM::getByte(address);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}

void CPU::CMPIndirectY() {

	unsigned short address = MEM::getByte(++programCounter + (0 * 256));
	unsigned char value = MEM::getByte(address + indexRegisterY);
	unsigned char test = accumulator - value;


	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (value <= accumulator) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }
	std::cout << "CMP" << std::endl;

}

void CPU::BITZeroPage() {

	unsigned short address = MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address + (0 * 256));
	unsigned char test = accumulator & value;

	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (((test >> 6) & 1U) == 1)
	{
		status |= 1U << 6;
	}
	else { status &= ~(1UL << 6); }
	std::cout << "BIT" << std::endl;

}



void CPU::BITAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	unsigned char value = MEM::getByte(address);
	unsigned char test = accumulator & value;

	if (test == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((test >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (((test >> 6) & 1U) == 1)
	{
		status |= 1U << 6;
	}
	else { status &= ~(1UL << 6); }
	std::cout << "BIT" << std::endl;

}


void CPU::LDXImmediate() {

	//Currently the program counter is on the byte with the instruction. For this instruction,
	//the operand is on the next byte, so increment it then operate on that.
	unsigned char value = MEM::getByte(++programCounter);
	indexRegisterX = value;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDX" << std::endl;

}

void CPU::LDXZeroPage() {

	//high byte is zero, low byte is operand (address where the new accumulator value lies)
	unsigned short address = MEM::getByte(++programCounter + 0 * 256);
	unsigned char value = MEM::getByte(address);
	indexRegisterX = value;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDX" << std::endl;

}

void CPU::LDXZeroPageY() {

	unsigned short address = MEM::getByte(++programCounter + 0 * 256) + indexRegisterY;
	unsigned char value = MEM::getByte(address);
	indexRegisterX = value;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDX" << std::endl;


}

void CPU::LDXAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address);
	indexRegisterX = value;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	std::cout << "LDX" << std::endl;

}

void CPU::LDXAbsoluteY() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) + indexRegisterY;
	unsigned char value = MEM::getByte(address);
	indexRegisterX = value;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDX" << std::endl;

}

void CPU::LDYImmediate() {

	//Currently the program counter is on the byte with the instruction. For this instruction,
//the operand is on the next byte, so increment it then operate on that.
	unsigned char value = MEM::getByte(++programCounter);
	indexRegisterY = value;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDX" << std::endl;

}

void CPU::LDYZeroPage() {
	
	unsigned char address = MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address);
	indexRegisterY = value;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDY" << std::endl;

}

void CPU::LDYZeroPageX() {

	unsigned char address = MEM::getByte(++programCounter) + indexRegisterX;
	unsigned char value = MEM::getByte(address);
	indexRegisterY = value;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDY" << std::endl;

}


void CPU::LDYAbsolute() {

	unsigned char address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	unsigned char value = MEM::getByte(address);
	indexRegisterY = value;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDY" << std::endl;

}

void CPU::LDYAbsoluteX() {

	unsigned char address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterY;
	unsigned char value = MEM::getByte(address);
	indexRegisterY = value;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "LDY" << std::endl;

}

void CPU::STXAbsolute()
{
	//example Acc value
	//accumulator = 0x86;

	//take next two bytes and make an address
	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	

	MEM::setByte(address, indexRegisterX);
	std::cout << "STX" << std::endl;

}

void CPU::STXZeroPage() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256;

	MEM::setByte(address, indexRegisterX);
	std::cout << "STX" << std::endl;

}

void CPU::STXZeroPageY() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256 + indexRegisterY;

	MEM::setByte(address, indexRegisterX);
	std::cout << "STX" << std::endl;

}


void CPU::STYAbsolute()
{
	//example Acc value
	//accumulator = 0x86;

	//take next two bytes and make an address
	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;


	MEM::setByte(address, indexRegisterY);
	std::cout << "STY" << std::endl;

}

void CPU::STYZeroPage() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256;

	MEM::setByte(address, indexRegisterY);
	std::cout << "STY" << std::endl;

}

void CPU::STYZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + 0 * 256 + indexRegisterX;

	MEM::setByte(address, indexRegisterY);
	std::cout << "STY" << std::endl;

}

void CPU::INCZeroPage() {

	unsigned short address = MEM::getByte(++programCounter) + (0 * 256);
	int value = MEM::getByte(address) + 1; 
	MEM::setByte(address, value);

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value>> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INC" << std::endl;

}


void CPU::INCZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + (0 * 256) + indexRegisterX;
	int value = MEM::getByte(address) + 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INC" << std::endl;

}

void CPU::INCAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int value = MEM::getByte(address) + 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INC" << std::endl;

}


void CPU::INCAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterX;
	int value = MEM::getByte(address) + 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INC" << std::endl;

}

void CPU::INXImplied() {

	++indexRegisterX;
	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INX" << std::endl;


}

void CPU::INYImplied() {

	++indexRegisterY;
	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "INY" << std::endl;

}

void CPU::DECZeroPage() {

	unsigned short address = MEM::getByte(++programCounter) + (0 * 256);
	int value = MEM::getByte(address) - 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEC" << std::endl;

}


void CPU::DECZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + (0 * 256) + indexRegisterX;
	int value = MEM::getByte(address) + 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEC" << std::endl;

}

void CPU::DECAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int value = MEM::getByte(address) - 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEC" << std::endl;

}


void CPU::DECAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterX;
	int value = MEM::getByte(address) - 1;
	MEM::setByte(address, value);
	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEC" << std::endl;

}

void CPU::DEXImplied() {

	--indexRegisterX;
	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEX" << std::endl;

}

void CPU::DEYImplied() {

	--indexRegisterY;
	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "DEY" << std::endl;

}


void CPU::CPXImmediate() {

	int compare = MEM::getByte(++programCounter);
	int value = indexRegisterX - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterX) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPX" << std::endl;


}
void CPU::CPXZeroPage() {
	unsigned short address = MEM::getByte(++programCounter);
	int compare = MEM::getByte(address);
	int value = indexRegisterX - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterX) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPX" << std::endl;

}

void CPU::CPXAbsolute() {
	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int compare = MEM::getByte(address);
	int value = indexRegisterX - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterX) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPX" << std::endl;

}

void CPU::CPYImmediate() {

	int compare = MEM::getByte(++programCounter);
	int value = indexRegisterY - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterY) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPY" << std::endl;

}
void CPU::CPYZeroPage() {
	unsigned short address = MEM::getByte(++programCounter);
	int compare = MEM::getByte(address);
	int value = indexRegisterY - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterY) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPY" << std::endl;

}

void CPU::CPYAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int compare = MEM::getByte(address);
	int value = indexRegisterY - compare;

	if (value == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((value >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	if (((abs(indexRegisterY) >= compare))) {
		status |= 1U << 0;
	}
	else { status &= 1U << 0; }
	std::cout << "CPY" << std::endl;

}

void CPU::TAXImplied() {

	indexRegisterX = accumulator;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "TAX" << std::endl;

}

void CPU::TXAImplied() {

	accumulator = indexRegisterX;

	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((accumulator >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "TXA" << std::endl;

}



void CPU::TAYImplied() {


	indexRegisterY = accumulator;

	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }

	std::cout << "TAY" << std::endl;

}

void CPU::TYAImplied() {

	accumulator = indexRegisterY;

	if (accumulator == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((accumulator >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "TYA" << std::endl;


}

void CPU::JSRAbsolute() {

	unsigned short newLowByte = MEM::getByte(++programCounter);
	unsigned short newHighByte = MEM::getByte(++programCounter);

	unsigned short firstLowByte = programCounter & 0xFF;
	unsigned short firstHighByte = (programCounter >> 8) & 0xFF;

	MEM::setByte(stackPointer, firstLowByte);
	--stackPointer;
	MEM::setByte(stackPointer, firstHighByte);
	--stackPointer;


	programCounter = newLowByte + newHighByte * 256 - 1;
	std::cout << "JSR Absolute" << std::endl;

}

void CPU::RTSImplied() {
	++stackPointer;

	unsigned char highByte = MEM::getByte(stackPointer);
	++stackPointer;
	unsigned char lowByte = MEM::getByte(stackPointer);


	programCounter = (lowByte + highByte * 256);
	std::cout << "RTS" << std::endl;

}

void CPU::PHAImplied() {

	MEM::setByte(stackPointer, accumulator);
	--stackPointer;
	std::cout << "PHA" << std::endl;

}

void CPU::PLAImplied() {

	accumulator = MEM::getByte(++stackPointer);
	if (indexRegisterY == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterY >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "PLA" << std::endl;

}

void CPU::TXSImplied() {

	stackPointer = indexRegisterX;
	std::cout << "TXS" << std::endl;


}

void CPU::TSXImplied() {

	indexRegisterX = stackPointer;

	if (indexRegisterX == 0)
	{
		status |= 1U << 1;
	}
	else { (status &= ~(1UL << 0)); }

	if (((indexRegisterX >> 7) & 1U) == 1)
	{
		status |= 1U << 7;
	}
	else { status &= 1U << 7; }
	std::cout << "TSX" << std::endl;

}

void CPU::PHPImplied() {

	MEM::setByte(stackPointer, status);
	--stackPointer;
	std::cout << "PHP" << std::endl;

}

void CPU::PLPImplied() {

	status = MEM::getByte(stackPointer);
	++stackPointer;
	std::cout << "PLP" << std::endl;

}

void CPU::RTIImplied() {
	std::cout << "RTI" << std::endl;

}

void CPU::BRKImplied() {
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++BRK+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

}

void CPU::LSRAccumulator() {

	int inputValue = accumulator;
	int n = 1;
	int mask = (1 << sizeof(int) - n) - 1;
	unsigned char inputBit0Value = ((inputValue >> 0) & 1U);
	unsigned char shiftedValue = inputValue >> n & mask;

	shiftedValue &= ~(1UL << 0);
	if (shiftedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 0); }

	accumulator = shiftedValue;

	if (inputBit0Value == 1) {

		status |= 1U << 0;
	}
	std::cout << "LSR" << std::endl;


}


void CPU::LSRZeroPage() {

	unsigned short address = MEM::getByte(++programCounter);
	int inputValue = MEM::getByte(address);
	int n = 1;
	int mask = (1 << sizeof(int) - n) - 1;
	unsigned char inputBit0Value = ((inputValue >> 0) & 1U);
	unsigned char shiftedValue = inputValue >> n & mask;

	shiftedValue &= ~(1UL << 0);
	if (shiftedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 0); }

	accumulator = shiftedValue;

	if (inputBit0Value == 1) {

		status |= 1U << 0;
	}

	std::cout << "LSR" << std::endl;

}
void CPU::LSRZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + indexRegisterX;
	int inputValue = MEM::getByte(address);
	int n = 1;
	int mask = (1 << sizeof(int) - n) - 1;
	unsigned char inputBit0Value = ((inputValue >> 0) & 1U);
	unsigned char shiftedValue = inputValue >> n & mask;

	shiftedValue &= ~(1UL << 0);
	if (shiftedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 0); }

	accumulator = shiftedValue;

	if (inputBit0Value == 1) {

		status |= 1U << 0;
	}
	std::cout << "LSR" << std::endl;

}

void CPU::LSRAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;

	int inputValue = MEM::getByte(address);
	int n = 1;
	int mask = (1 << sizeof(int) - n) - 1;
	unsigned char inputBit0Value = ((inputValue >> 0) & 1U);
	unsigned char shiftedValue = inputValue >> n & mask;

	shiftedValue &= ~(1UL << 0);
	if (shiftedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 0); }

	accumulator = shiftedValue;

	if (inputBit0Value == 1) {

		status |= 1U << 0;
	}
	std::cout << "LSR" << std::endl;

}


void CPU::LSRAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterX;
	int inputValue = MEM::getByte(address);
	int n = 1;
	int mask = (1 << sizeof(int) - n) - 1;
	unsigned char inputBit0Value = ((inputValue >> 0) & 1U);
	unsigned char shiftedValue = inputValue >> n & mask;

	shiftedValue &= ~(1UL << 0);
	if (shiftedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 0); }

	accumulator = shiftedValue;

	if (inputBit0Value == 1) {

		status |= 1U << 0;
	}
	std::cout << "LSR" << std::endl;

}

void CPU::ASLAccumulator() {

	unsigned char valueBit7 = ((accumulator >> 7) & 1U);
	accumulator = accumulator << 1;

	if (valueBit7 == 1) {
		status |= 1U << 0;
	}

	else { accumulator &= ~(1UL << 0); }
	if (valueBit7 == 1) {
		status |= 1U << 7;
	}
	else { accumulator &= ~(1UL << 7); }

	if (accumulator == 0) {

		status |= 1U << 1;
	}
	std::cout << "ASL" << std::endl;

}


void CPU::ASLZeroPage() {

	unsigned short address = MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address);

	unsigned char valueBit7 = ((value >> 7) & 1U);
	value = value << 1;

	if (valueBit7 == 1) {
		status |= 1U << 0;
	}

	else { accumulator &= ~(1UL << 0); }
	if (valueBit7 == 1) {
		status |= 1U << 7;
	}
	else { accumulator &= ~(1UL << 7); }

	if (value == 0) {

		status |= 1U << 1;
	}

	MEM::setByte(address, value);
	std::cout << "ASL" << std::endl;

}


void CPU::ASLZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter);
	unsigned char value = MEM::getByte(address + indexRegisterX);

	unsigned char valueBit7 = ((value >> 7) & 1U);
	value = value << 1;
	if (valueBit7 == 1) {
		status |= 1U << 0;
	}

	else { accumulator &= ~(1UL << 0); }
	if (valueBit7 == 1) {
		status |= 1U << 7;
	}
	else { accumulator &= ~(1UL << 7); }
	if (value == 0) {

		status |= 1U << 1;
	}

	MEM::setByte(address, value);
	std::cout << "ASL" << std::endl;

}

void CPU::ASLAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	unsigned char value = MEM::getByte(address);

	unsigned char valueBit7 = ((value >> 7) & 1U);
	value = value << 1;

	if (valueBit7 == 1) {
		status |= 1U << 0;
	}

	else { accumulator &= ~(1UL << 0); }
	if (valueBit7 == 1) {
		status |= 1U << 7;
	}
	else { accumulator &= ~(1UL << 7); }
	if (value == 0) {

		status |= 1U << 1;
	}

	MEM::setByte(address, value);

	std::cout << "ASL" << std::endl;


}


void CPU::ASLAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	unsigned char value = MEM::getByte(address + indexRegisterX);

	unsigned char valueBit7 = ((value >> 7) & 1U);
	value = value << 1;

	if (valueBit7 == 1) {
		status |= 1U << 0;
	}

	else { accumulator &= ~(1UL << 0); }
	if (valueBit7 == 1) {
		status |= 1U << 7;
	}
	else { accumulator &= ~(1UL << 7); }

	if (value == 0) {

		status |= 1U << 1;
	}

	MEM::setByte(address, value);
	std::cout << "ASL" << std::endl;


}

void CPU::ROLAccumulator() {
	unsigned char valueBit0 = ((accumulator >> 0) & 1U);


	int value = accumulator;
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		accumulator |= 1U << 6;
	}
	else { accumulator &= ~(1UL << 6); }

	if (inputCarry ==1 ) {
		accumulator |= 1U << 0;
	}
	else { accumulator &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		accumulator = rotatedValue |= 1U << 7;
	}
	std::cout << "ROL" << std::endl;

}

void CPU::ROLZeroPage() {


	int value = MEM::getByte(++programCounter);
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	unsigned char valueBit0 = ((value >> 0) & 1U);


	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		value |= 1U << 6;
	}
	else { value &= ~(1UL << 6); }

	if (inputCarry == 1) {
		value |= 1U << 0;
	}
	else { value &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		value = rotatedValue |= 1U << 7;
	}
	std::cout << "ROL" << std::endl;

}


void CPU::ROLZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + indexRegisterX;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	unsigned char valueBit0 = ((value >> 0) & 1U);


	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		value |= 1U << 6;
	}
	else { value &= ~(1UL << 6); }

	if (inputCarry == 1) {
		value |= 1U << 0;
	}
	else { value &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		value = rotatedValue |= 1U << 7;
	}
	std::cout << "ROL" << std::endl;

}

void CPU::ROLZeroPageY() {

	unsigned short address = MEM::getByte(++programCounter) + indexRegisterY;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	unsigned char valueBit0 = ((value >> 0) & 1U);


	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		value |= 1U << 6;
	}
	else { value &= ~(1UL << 6); }

	if (inputCarry == 1) {
		value |= 1U << 0;
	}
	else { value &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		value = rotatedValue |= 1U << 7;
	}
	std::cout << "ROL" << std::endl;

}


void CPU::ROLAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	unsigned char valueBit0 = ((value >> 0) & 1U);


	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		value |= 1U << 6;
	}
	else { value &= ~(1UL << 6); }

	if (inputCarry == 1) {
		value |= 1U << 0;
	}
	else { value &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		value = rotatedValue |= 1U << 7;
	}
	std::cout << "ROL" << std::endl;

}

void CPU::ROLAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterX;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotl8(value, 1);
	unsigned char inputCarry = ((value >> 0) & 1U);
	bool setN = false;

	unsigned char valueBit0 = ((value >> 0) & 1U);


	if (((status >> 6) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		value |= 1U << 6;
	}
	else { value &= ~(1UL << 6); }

	if (inputCarry == 1) {
		value |= 1U << 0;
	}
	else { value &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		value = rotatedValue |= 1U << 7;
	}

	std::cout << "ROL" << std::endl;

}

void CPU::RORAccumulator() {
	unsigned char valueBit0 = ((accumulator >> 0) & 1U);


	int value = accumulator;
	unsigned char rotatedValue = _rotr8(value, 1);
	bool setN = false;

	if (rotatedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((status >> 0) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	accumulator = rotatedValue;
	if (setN == true) {

		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (valueBit0 == 1) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		accumulator = rotatedValue |= 1U << 7;
	}
	std::cout << "ROR" << std::endl;

}

void CPU::RORZeroPage() {

	unsigned short address = MEM::getByte(++programCounter);
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotr8(value, 1);
	unsigned char valueBit0 = ((value >> 0) & 1U);
	bool setN = false;

	if (rotatedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((status >> 0) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	MEM::setByte(address, rotatedValue);

	if (setN == true) {

		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (valueBit0 == 1) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		MEM::setByte(address, rotatedValue |= 1U << 7);
	}

	std::cout << "ROR" << std::endl;

}


void CPU::RORZeroPageX() {

	unsigned short address = MEM::getByte(++programCounter) + indexRegisterX;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotr8(value, 1);
	unsigned char valueBit0 = ((value >> 0) & 1U);
	bool setN = false;

	if (rotatedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }
		
	if (((status >> 0) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	MEM::setByte(address, rotatedValue);

	if (setN == true) {

		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (valueBit0 == 1) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		MEM::setByte(address, rotatedValue |= 1U << 7);
	}
	std::cout << "ROR" << std::endl;

}


void CPU::RORAbsolute() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotr8(value, 1); 
	unsigned char valueBit0 = ((value >> 0) & 1U);
	bool setN = false;

	if (rotatedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((status >> 0) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	MEM::setByte(address, rotatedValue);

	if (setN == true) {

		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (valueBit0 == 1) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		MEM::setByte(address, rotatedValue |= 1U << 7);
	}
	std::cout << "ROR" << std::endl;

}

void CPU::RORAbsoluteX() {

	unsigned short address = MEM::getByte(++programCounter) + MEM::getByte(++programCounter) * 256 + indexRegisterX;
	int value = MEM::getByte(address);
	unsigned char rotatedValue = _rotr8(value, 1); 
	unsigned char valueBit0 = ((value >> 0) & 1U);
	bool setN = false;

	if (rotatedValue == 0)
	{
		status |= 1U << 1;
	}
	else { status &= ~(1UL << 1); }

	if (((status >> 0) & 1U) == 1)
	{
		setN = true;
	}
	else { setN = false; }

	MEM::setByte(address, rotatedValue);

	if (setN == true) {

		status |= 1U << 7;
	}
	else { status &= ~(1UL << 7); }

	if (valueBit0 == 1) {
		status |= 1U << 0;
	}
	else { status &= ~(1UL << 0); }

	if (((status >> 0) & 1U) == 1) {
		MEM::setByte(address, rotatedValue |= 1U << 7);
	}
	std::cout << "ROR" << std::endl;

}

void CPU::NOPRealImplied() {

	std::cout << "REALNOP" << std::endl;

}

void CPU::NOPImplied() {

	std::cout << "**************************************BAD INSTRUCTION*************************************" << std::endl;

}

void CPU::interrupt() {
	unsigned short firstLowByte = programCounter & 0xFF;
	unsigned short firstHighByte = (programCounter >> 8) & 0xFF;

	//put program counter on the stack
	MEM::setByte(stackPointer, firstLowByte);
	--stackPointer;
	MEM::setByte(stackPointer, firstHighByte);
	--stackPointer;


	programCounter = (MEM::getByte(0xFFFE) + 0xF000 )+ (MEM::getByte(0xFFFF) + 0xF000)* 256;
}