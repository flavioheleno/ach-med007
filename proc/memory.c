#include "memory.h"

uint8_t ReadFILE(char *file, uint16_t Address, uint8_t Default) {
	FILE *f;
	uint8_t data;
	f = fopen(file, "rb");
	if (f) {
		fseek(f, (Address * sizeof(uint16_t)), SEEK_SET);
		fscanf(f, "%c", &data);
		fclose(f);
		return data;
	} else {
		return Default;
	}	
}

void WriteFILE(char *file, uint16_t Address, uint8_t Data) {
	FILE *f;
	f = fopen(file, "r+b");
	if (!f) {
		f = fopen(file, "w+b");
	}
	if (f) {
		fseek(f, (Address * sizeof(uint16_t)), SEEK_SET);
		fprintf(f, "%c", (char)Data);
		fclose(f);
	} else {
		printf("ERROR WRITING TO ROM FILE!\r\n");
	}
}

void CreateRAM() {
	uint16_t i;
	for (i = 0; i < UINT16_MAX; i++) {
		WriteFILE("ram.bin", i, (uint8_t) 0);
	}
}
