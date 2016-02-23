#ifndef BitPacker_H
#define BitPacker_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyLib.h"

#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF

typedef struct {
   UInt curData;
   UInt nextData;
   int bitsLeft;
   int validNext;
} BitUnpacker;

void buInit(BitUnpacker *bu);

void buTakeData(BitUnpacker *bu, UInt nextData);

int unpack(BitUnpacker *bu, int size, UInt *code);

#endif
