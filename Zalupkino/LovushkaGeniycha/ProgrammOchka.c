#define _CRT_SECURE_NO_WARNINGS
#include "HeadProgramm.h"

void printConsole()
{
 printf("1. ������ �������\n");
 printf("2. ���������� ���������\n");
 printf("3. ���������� �������\n");
 printf("4. ������� ����������\n");
 printf("5. ����� ������ �������\n");
 printf("6. ����� �� �������\n");
}

float* openMassiveFromFile(const char* filename, int* size)
{
 FILE* f = fopen(filename, "r+");
 int i = 0;
 float* massive = 0;
 if(f == NULL)
 {
  return NULL;
 }
 fscanf(f, "%f", size);
 massive = (float*)malloc(*size * sizeof(float));
 for(i = 0; i < *size; i++)
 {
  fscanf(f, "%f", &massive[i]);
 }
 fclose(f);
 return massive;
}

void printMassive(float* massive, int size)
{
 int i = 0;
 for(i = 0; i < size; i++)
 {
  printf("%f", massive[i]);
 }
 printf("\n");
}

void constantMassive(float* massive, const char* filename)
{
 FILE* f = fopen(filename, "r");
 int size, i;
 if(f == NULL)
 {
  return;
 }
 fscanf(f, "%d", &size);
 for(i = 0; i < size; i++)
 {
  fscanf(f, "%f", &massive[i]);
 }
 fclose(f);
}

void freeMassive(float* massive)
{
 if(massive != NULL)
 {
  free(massive);
 }
}