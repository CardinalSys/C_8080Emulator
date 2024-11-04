#include <stdio.h>
#include <stdlib.h>
#include "Disassembler.h"

char rom[0x1fff];
long romIndex;

void AllocateRom();
void ReadRom(char* path);
void main() {
	AllocateRom();
	DebugRom();
}

void AllocateRom() {
	ReadRom("D:/rom/Space invaders/invaders.h");
	ReadRom("D:/rom/Space invaders/invaders.g");
	ReadRom("D:/rom/Space invaders/invaders.f");
	ReadRom("D:/rom/Space invaders/invaders.e");
}

void ReadRom(char* path) {
	long romSize = 0;
	FILE* fp = fopen(path, "rb");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	fseek(fp, 0L, SEEK_END);
	romSize = ftell(fp);
	if (romSize == 0) {
		printf("Incorrect file size\n");
	}
	printf("Rom size: %ld kb\n", romSize);
	fseek(fp, 0L, SEEK_SET);

	unsigned char* bufferPtr = (unsigned char*)malloc(sizeof(unsigned char) * romSize);

	if (bufferPtr == NULL) {
		printf("Memory not allocated\n");
		return 0;
	}

	printf("Memory allocated\n");

	fread(bufferPtr, sizeof(char), romSize, fp);
	fclose(fp);

	for (int i = 0; i < romSize; i++, romIndex++) {
		printf("%ld\n",romIndex);
		rom[romIndex] = bufferPtr[i];
	}



	free(bufferPtr);
	return 0;
}