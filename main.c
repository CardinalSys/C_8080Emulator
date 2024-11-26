#include <stdio.h>
#include <stdlib.h>
#include "Disassembler.h"
#include "cpu.h"
#define ROM_SIZE 0x1fff

char rom[ROM_SIZE];
int romIndex = 0;

void AllocateRom();
int ReadRom(char* path);
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

int ReadRom(char* path) {
	long romSize = 0;
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, path, "rb");
	if (err != 0) {
		printf("File not found\n");
		return 0;
	}

	fseek(fp, 0L, SEEK_END);
	romSize = ftell(fp);
	if (romSize <= 0) {
		printf("Incorrect file size\n");
		fclose(fp);
		return 0;
	}
	fseek(fp, 0L, SEEK_SET);
	printf("Rom size: %ld kb\n", romSize);
	


	unsigned char* bufferPtr = (unsigned char*)malloc(sizeof(unsigned char) * romSize);
	if (bufferPtr == NULL) {
		printf("Memory allocation failed for: %s\n", path);
		fclose(fp);
		return 0;
	}

	printf("Memory allocated\n");

	size_t  bytesRead = fread(bufferPtr, sizeof(unsigned char), romSize, fp);

	if (bytesRead != romSize) {
		printf("failed to read complete file");
		free(bufferPtr);
		fclose(fp);
		return;
	}

	fclose(fp);

	for (int i = 0; i < romSize; i++) {

		rom[romIndex++] = bufferPtr[i];
		
	}

	int a;

	free(bufferPtr);
	return 1;
}