#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Programm.h"

void main(int argc, char* argv[])
{
 int size;
 int min, max;
 float* massive;
 setlocale(LC_ALL, "Russian");
 if(argc < 5)
 {
  printf("Неверное количество введенных аргументов!\n");
  return;
 }
 size = atoi(argv[1]);
 min = atof(argv[2]);
 max = atof(argv[3]);
 massive = generateMassive(size, min, max);
 {
  writeMassive(massive, size, argv[4]);
 }
 printMassive(massive, size);
 freeFile(massive);
}