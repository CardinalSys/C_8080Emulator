#include <stdio.h>
#include <stdlib.h>

void ReadRom();

int main() {
	ReadRom();
	return 0;
}

void ReadRom() {
	long romSize = 0;
	FILE* fp = fopen("D:/rom/bully.gb", "rb");
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
	for (long i = 0; i < romSize; i++) {
		printf("%02X ", bufferPtr[i]);
		if ((i + 1) % 16 == 0) printf("\n");
	}
	free(bufferPtr);
	return 0;
}