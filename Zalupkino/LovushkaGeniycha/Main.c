#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "HeadSorts.h"
#include "HeadProgramm.h"

void main(int argc, char** argv)
{
 int console;
 int size;
 clock_t start, finish;
 float* massive;
 setlocale(LC_ALL, "Russian");
 if (argc < 2)
 {
  printf("Неверное количество параметров!\n");
  return;
 }
 massive = openMassiveFromFile(argv[1], &size);
 if (massive == NULL)
 {
  printf("Проблемы с открытием файла!\n");
  return;
 }
 do
 {
  printConsole();
  scanf_s("%d", &console);
  if (console == 1)
  {
   printMassive(massive, size);
   continue;
  }
  if (console == 2)
  {
   start = clock();
   bubbleSort(massive, size);
   finish = clock();
   printf("Сортировка выполнена за %.4lf секунд\n", (double)(finish - start) / CLOCKS_PER_SEC);
   continue;
  }
  if (console == 3)
  {
   start = clock();
   insertSort(massive, size);
   finish = clock();
   printf("Сортировка выполнена за %.4lf секунд\n", (double)(finish - start) / CLOCKS_PER_SEC);
   continue;
  }
  if (console == 4)
  {
   start = clock();
   quickSort(massive, 0, size - 1);
   finish = clock();
   printf("Сортировка выполнена за %.4lf секунд\n", (double)(finish - start) / CLOCKS_PER_SEC);
   continue;
  }
  if (console == 5)
  {
   constantMassive(massive, argv[1]);
   printf("Сброс выполнен!\n");
   continue;
  }
  if (console == 6)
  {
   continue;
  }
  printf("Error 404\n");
 } while (console != 6);
}