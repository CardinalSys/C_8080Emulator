#include <stdio.h>
#include "cpu.h"

#define RAM_SIZE 0x10000

unsigned char ram[RAM_SIZE];

unsigned short pc = 0;
unsigned short sp = 0;

unsigned char A;

struct Register {
	union {
		unsigned short word;
		struct {
			unsigned char low;
			unsigned char high;		
		};
	};
};
struct Register BC;
struct Register DE;
struct Register HL;

struct Register WZ;

struct Flags {
	unsigned char carry : 1;
	unsigned char sign : 1;
	unsigned char zero : 1;
	unsigned char parity : 1; 
	unsigned char auxCarry : 1;
	unsigned char reserved : 3; 
};

struct Flags flags;


void SignCheck(unsigned char number) {
	if (number & 0x80) {
		flags.sign = 1;
	}
	else {
		flags.sign = 0;
	}
}

void ZeroCheck(unsigned char number) {
	if (number == 0) {
		flags.zero = 1;
	}
	else {
		flags.zero = 0;
	}
}

void ParityCheck(unsigned char number) {
	unsigned char bitCount = 0;

	for (int i = 0; i < 8; i++) {
		if (number & (1 << i)) {
			bitCount++;
		}
	}

	if (bitCount % 2 == 0) {
		flags.parity = 1;
	}
	else {
		flags.parity = 0;
	}
}

void AuxiliaryCarryCheck(unsigned char operand1, unsigned char operand2, unsigned char carry_in, unsigned char result) {
	if (((operand1 & 0x0F) + (operand2 & 0x0F) + carry_in) > 0x0F) {
		flags.auxCarry = 1;
	}
	else {
		flags.auxCarry = 0;
	}
}

void AuxiliaryBorrowCheck(unsigned char operand1, unsigned char operand2) {
	if ((operand1 & 0x0F) < (operand2 & 0x0F)) {
		flags.auxCarry = 1;
	}
	else {
		flags.auxCarry = 0;
	}
}

//0x
void NOP() {
	pc += 1;
}

void LXIB() {
	BC.low = ram[pc + 1];
	BC.high = ram[pc + 2];
	pc += 3;
}

void STAXB() {
	ram[BC.word] = A;
	pc += 1;
}

void INXB() {
	BC.word++;
	pc += 1;
}

void INRB() {
	unsigned char original = BC.high;
	unsigned char result = BC.high + 1;

	BC.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, 1, 0, result);
	pc += 1;
}

void DCRB() {
	unsigned char original = BC.high;
	unsigned char result = BC.high - 1;

	BC.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryBorrowCheck(original, 1);
	pc += 1;
}

//1x
void NOPo() {
	pc += 1;
}

void LXID() {
	DE.low = ram[pc + 1];
	DE.high = ram[pc + 2];
	
	pc += 3;
}

void STAXD() {
	ram[DE.word] = A;
	pc += 1;
}

void INXD() {
	DE.word;
	pc += 1;
}

void INRD() {
	unsigned char original = DE.high;
	unsigned char result = DE.high + 1;

	DE.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, 1, 0, result);

}

void DCRD() {
	unsigned char original = DE.high;
	unsigned char result = DE.high - 1;

	DE.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, -1, 0, result);
}

//2x
void NOPoo() {
	pc += 1;
}

void LXIH() {
	HL.low = ram[pc + 1];
	HL.high = ram[pc + 2];
	
	pc += 3;
}

void SHLD() {
	unsigned short address = (ram[pc + 2] << 8) | ram[pc + 1];

	ram[address] = HL.low;

	ram[address + 1] = HL.high;

	pc += 3;
}

void INXH() {
	HL.word;
	pc += 1;
}

void INRH() {
	unsigned char original = HL.high;
	unsigned char result = HL.high + 1;

	HL.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, 1, 0, result);

}

void DCRH() {
	unsigned char original = HL.high;
	unsigned char result = HL.high - 1;

	HL.high = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, -1, 0, result);
}

//3x
void NOPooo() {
	pc += 1;
}

void LXISP() {
	sp = (ram[pc + 1] << 8) | ram[pc + 2];
	pc += 3;
}

void STA() {
	unsigned short addr = (ram[pc + 2] << 8) | ram[pc + 1];
	ram[addr] = A;
	pc += 3;
}

void INXSP() {
	sp++;
	pc += 1;
}

void INRM() {
	unsigned char original = ram[HL.word];
	unsigned char result = ram[HL.word] + 1;

	ram[HL.word] = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, 1, 0, result);

}

void DCRM() {
	unsigned char original = ram[HL.word];
	unsigned char result = ram[HL.word] - 1;

	ram[HL.word] = result;

	ZeroCheck(result);
	SignCheck(result);
	ParityCheck(result);
	AuxiliaryCarryCheck(original, -1, 0, result);
}

//4x
void MOVBB() {
	BC.high = BC.high;
	pc += 1;
}
void MOVBC() {
	BC.high = BC.low;
	pc += 1;
}
void MOVBE() {
	BC.high = DE.low;
	pc += 1;
}
void MOVBH() {
	BC.high = HL.high;
	pc += 1;
}
void MOVBL() {
	BC.high = HL.low;
	pc += 1;
}
void MOVBM() {
	unsigned short addr = HL.word;
	BC.high = ram[addr];
	pc += 1;
}
void MOVBA() {
	BC.high = A;
	pc += 1;
}
void MOVCB() {
	BC.low = BC.high;
	pc += 1;
}
void MOVCC() {
	BC.low = BC.low;
	pc += 1;
}
void MOVCD() {
	BC.low = DE.high;
	pc += 1;
}
void MOVCE() {
	BC.low = DE.low;
	pc += 1;
}
void MOVCH() {
	BC.low = HL.high;
	pc += 1;
}
void MOVCL() {
	BC.low = BC.low;
	pc += 1;
}
void MOVCM() {
	unsigned short addr = HL.word;
	BC.low = ram[addr];
	pc += 1;
}
void MOVCA() {
	BC.low = A;
	pc += 1;
}
//5x
void MOVDB() {
	DE.high = BC.high;
	pc += 1;
}
void MOVDC() {
	DE.high = BC.low;
	pc += 1;
}
void MOVDE() {
	DE.high = DE.low;
	pc += 1;
}
void MOVDH() {
	DE.high = HL.high;
	pc += 1;
}
void MOVDL() {
	DE.high = HL.low;
	pc += 1;
}
void MOVDM() {
	unsigned short addr = HL.word;
	DE.high = ram[addr];
	pc += 1;
}
void MOVDA() {
	DE.high = A;
	pc += 1;
}
void MOVEB() {
	DE.low = BC.high;
	pc += 1;
}
void MOVEC() {
	DE.low = BC.low;
	pc += 1;
}
void MOVED() {
	DE.low = DE.high;
	pc += 1;
}
void MOVEE() {
	DE.low = DE.low;
	pc += 1;
}
void MOVEH() {
	DE.low = HL.high;
	pc += 1;
}
void MOVEL() {
	DE.low = HL.low;
	pc += 1;
}
void MOVEM() {
	unsigned short addr = HL.word;
	DE.low = ram[addr];
	pc += 1;
}
void MOVEA() {
	DE.low = A;
	pc += 1;
}
//6x
void MOVHB() {
	HL.high = BC.high;
	pc += 1;
}
void MOVHC() {
	HL.high = BC.low;
	pc += 1;
}
void MOVHE() {
	HL.high = DE.low;
	pc += 1;
}
void MOVHH() {
	HL.high = HL.high;
	pc += 1;
}
void MOVHL() {
	HL.high = HL.low;
	pc += 1;
}
void MOVHM() {
	unsigned short addr = HL.word;
	HL.high = ram[addr];
	pc += 1;
}
void MOVHA() {
	HL.high = A;
	pc += 1;
}
void MOVLB() {
	HL.low = BC.high;
	pc += 1;
}
void MOVLC() {
	HL.low = BC.low;
	pc += 1;
}
void MOVLD() {
	HL.low = DE.high;
	pc += 1;
}
void MOVLE() {
	HL.low = DE.low;
	pc += 1;
}
void MOVLH() {
	HL.low = HL.high;
	pc += 1;
}
void MOVLL() {
	HL.low = HL.low;
	pc += 1;
}
void MOVLM() {
	unsigned short addr = HL.word;
	HL.low = ram[addr];
	pc += 1;
}
void MOVLA() {
	HL.low = A;
	pc += 1;
}
//7x
void MOVMB() {
	ram[HL.word] = BC.high;
	pc += 1;
}
void MOVMC() {
	ram[HL.word] = BC.low;
	pc += 1;
}
void MOVME() {
	ram[HL.word] = DE.low;
	pc += 1;
}
void MOVMH() {
	ram[HL.word] = HL.high;
	pc += 1;
}
void MOVML() {
	ram[HL.word] = HL.low;
	pc += 1;
}
void HLT() {
	pc += 1;
}
void MOVMA() {
	ram[HL.word] = A;
	pc += 1;
}
void MOVAB() {
	A = BC.high;
	pc += 1;
}
void MOVAC() {
	A = BC.low;
	pc += 1;
}
void MOVAD() {
	A = DE.high;
	pc += 1;
}
void MOVAE() {
	A = DE.low;
	pc += 1;
}
void MOVAH() {
	A = HL.high;
	pc += 1;
}
void MOVAL() {
	A = HL.low;
	pc += 1;
}
void MOVAM() {
	A = ram[HL.word];
	pc += 1;
}
void MOVAA() {
	A = A;
	pc += 1;
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
