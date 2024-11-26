#include <stdio.h>
#include "cpu.h"

#define RAM_SIZE 0x10000

unsigned char ram[RAM_SIZE];

unsigned short pc = 0;
unsigned short sp = 0;

unsigned short A;

struct Register {
	unsigned char high;
	unsigned char low;
};

struct Register BC;
struct Register DE;
struct Register HL;

struct Register WZ;


void NOP() {
	return;
}

void JMP() {

	int addr = ram[pc + 1] << 8 | ram[pc + 2];

	pc == addr;
}

//4x
void MOVBB() {
	BC.high = BC.high;
}
void MOVBC() {	
	BC.high = BC.low;
}
void MOVBE() {
	BC.high = DE.low;
}
void MOVBH() {
	BC.high = HL.high;
}
void MOVBL() {
	BC.high = HL.low;
}
void MOVBM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	BC.high = ram[addr];
}
void MOVBA() {
	BC.high = A;
}
void MOVCB() {
	BC.low = BC.high;
}
void MOVCC() {
	BC.low = BC.low;
}
void MOVCD() {
	BC.low = DE.high;
}
void MOVCE() {
	BC.low = DE.low;
}
void MOVCH() {
	BC.low = HL.high;
}
void MOVCL() {
	BC.low = BC.low;
}
void MOVCM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	BC.low = ram[addr];
}
void MOVCA() {
	BC.low = A;
}
//5x
void MOVDB() {
	DE.high = BC.high;
}
void MOVDC() {
	DE.high = BC.low;
}
void MOVDE() {
	DE.high = DE.low;
}
void MOVDH() {
	DE.high = HL.high;
}
void MOVDL() {
	DE.high = HL.low;
}
void MOVDM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	DE.high = ram[addr];
}
void MOVDA() {
	DE.high = A;
}
void MOVEB() {
	DE.low = BC.high;
}
void MOVEC() {
	DE.low = BC.low;
}
void MOVED() {
	DE.low = DE.high;
}
void MOVEE() {
	DE.low = DE.low;
}
void MOVEH() {
	DE.low = HL.high;
}
void MOVEL() {
	DE.low = HL.low;
}
void MOVEM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	DE.low = ram[addr];
}
void MOVEA() {
	DE.low = A;
}
//6x
void MOVHB() {
	HL.high = BC.high;
}
void MOVHC() {
	HL.high = BC.low;
}
void MOVHE() {
	HL.high = DE.low;
}
void MOVHH() {
	HL.high = HL.high;
}
void MOVHL() {
	HL.high = HL.low;
}
void MOVHM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	HL.high = ram[addr];
}
void MOVHA() {
	HL.high = A;
}
void MOVLB() {
	HL.low = BC.high;
}
void MOVLC() {
	HL.low = BC.low;
}
void MOVLD() {
	HL.low = DE.high;
}
void MOVLE() {
	HL.low = DE.low;
}
void MOVLH() {
	HL.low = HL.high;
}
void MOVLL() {
	HL.low = HL.low;
}
void MOVLM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	HL.low = ram[addr];
}
void MOVLA() {
	BC.low = A;
}
//7x
void MOVMB() {
	ram[(HL.high << 8) | HL.low] = BC.high;
}
void MOVMC() {
	ram[(HL.high << 8) | HL.low] = BC.low;
}
void MOVME() {
	ram[(HL.high << 8) | HL.low] = DE.low;
}
void MOVMH() {
	ram[(HL.high << 8) | HL.low] = HL.high;
}
void MOVML() {
	ram[(HL.high << 8) | HL.low] = HL.low;
}
void HLT() {
	
}
void MOVMA() {
	ram[(HL.high << 8) | HL.low] = A;
}
void MOVAB() {
	A = BC.high;
}
void MOVAC() {
	A = BC.low;
}
void MOVAD() {
	A = DE.high;
}
void MOVAE() {
	A = DE.low;
}
void MOVAH() {
	A = HL.high;
}
void MOVAL() {
	A = HL.low;
}
void MOVAM() {
	unsigned short addr = (HL.high << 8) | HL.low;
	A = ram[addr];
}
void MOVAA() {
	A = A;
}


void ExecuteOpcode(unsigned char* op) {
	switch (*op)
	{
	case 0x00:
		NOP();
		break;
	case 0xC3:
		JMP();

	default:
		printf("Unknown opcode: 0x%02X at address 0x%04X\n", *op, pc);
		break;
	}
}
