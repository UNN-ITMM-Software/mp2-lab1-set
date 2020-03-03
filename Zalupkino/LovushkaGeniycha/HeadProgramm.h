#pragma once
#ifndef _HEADPROGRAMM_H_
#define _HEADPROGRAMM_H_
#include <stdio.h>
#include <stdlib.h>

void printConsole();
float* openMassiveFromFile(const char* spisok, int* size);
void printMassive(float* massive, int size);
void constantMassive(float* massive, const char* filename);
void freeMassive(float* massive);

#endif