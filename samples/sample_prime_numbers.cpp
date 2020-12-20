// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>


#include "tset.h"
#include "tbitfield.h"

int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
 
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TSet s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.InsElem(m);
  cout << s << endl;
  int* mas = s.Ostatok(2);
  n = s.GetNumOst(2);
  cout << "Элементы, кратные 2:" << endl;
  for(int i=0;i<n;i++)
  cout << mas[i] << endl;
  s.FindClr(14);
  cout << s << endl;
  s.WriteF();
  TSet s1(1);
  s1.ReadF();
  cout << s1 << endl;
}

