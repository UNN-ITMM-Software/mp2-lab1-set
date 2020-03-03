#define _CRT_SECURE_NO_WARNINGS
#include "HeadSorts.h"

void swype(int* x, int* y)
{
 int tp = *x;
 *x = *y;
 *y = tp;
}

void bubbleSort(float* massive, int size)
{
 int i = 0, j = 0;
 for(i = 0; i < size; i++)
 {
  for(j = 1; j < size - i; j++)
  {
   if(massive[j - i] > massive[j])
   {
    swype(&massive[j], &massive[j - i]);
   }
  }
 }
}

void insertSort(float* massive, int size)
{
 int i = 0, j = 0, tp;
 for(i = 1; i < size; i++)
 {
  tp = massive[i];
  j = i - 1;
  while((j >= 0) && (massive[j] > tp))
  {
   swype(&massive[j], &massive[j + 1]);
   j--;
  }
 }
}

void quickSort(float* massive, int begin, int end)
{
 int comp = massive[(begin + end) / 2];
 int i = begin, j = end;
 do
 {
  while(massive[i] < comp)
  {
   i++;
  }
  while(massive[j] > comp)
  {
   j--;
  }
  if(i <= j)
  {
   if(massive[i] > massive[j])
   {
    swype(&massive[i], &massive[j]);
   }
   i++;
   j--;
  }
 } while (i <= j);
 if(i < end)
 {
  quickSort(massive, i, end);
 }
 if(j > begin)
 {
  quickSort(massive, begin, j);
 }
}