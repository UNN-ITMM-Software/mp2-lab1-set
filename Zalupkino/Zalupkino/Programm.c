#define _CRT_SECURE_NO_WARNINGS
#include "Programm.h"

int promejutock(int min, int max)
{
 return rand() % (max - min + 1) + min;
}

float* generateMassive(int size, int min, int max)
{
 int i = 0;
 float* massive = (float*)malloc(size * sizeof(float));
 for(i = 0; i < size; i++)
 {
  massive[i] = promejutock(max, min);
 }
 return massive;
}

void printMassive(float* massive, int size)
{
 int i = 0;
 for(i = 0; i < size; i++)
 {
  printf("[%d] = %.3f", i, massive[i]);
  printf("\n");
 }
}

void writeMassive(float* massive, int size, const char* filename)
{
 int i = 0;
 FILE* f = fopen(filename, "w");
 if(f == NULL)
 {
  return;
 }
 fprintf(f, "%d", size);
 for(i = 0; i < size; i++);
 {
  fprintf(f, "%.3f", massive[i]);
 }
 fclose(f);
}

void freeFile(float* massive)
{
 if (massive != NULL)
 {
  free(massive);
 }
}