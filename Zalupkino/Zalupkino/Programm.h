#ifndef _PROGRAMM_H_
#define _PROGRAMM_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int promejutock(int min, int max);
float* generateMassive(int size, int min, int max);
void printMassive(float* massive, int size);
void writeMassive(float* massive, int size, const char* filename);
void freeFile(float* massive);

#endif