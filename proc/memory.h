#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdint.h>

uint8_t ReadFILE(char *file, uint16_t Address, uint8_t Default);
void WriteFILE(char *file, uint16_t Address, uint8_t Data);
void CreateRAM();

#define ReadROM(Address, Default) ReadFILE("rom.bin", Address, Default)
#define WriteROM(Address, Data) WriteFILE("rom.bin", Address, Data)
#define ReadRAM(Address, Default) ReadFILE("ram.bin", Address, Default)
#define WriteRAM(Adress, Data) WriteFILE("ram.bin", Address, Data)

#endif
