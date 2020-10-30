// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

// #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

#ifdef USE_SET // Использовать класс TBitField

#include "tbitfield.h"


int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки битового поля" << endl;
  cout << "             Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TBitField s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.SetBit(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если m в s, удаление кратных
    if (s.GetBit(m))
      for (k = 2 * m; k <= n; k += m)
        if (s.GetBit(k))
          s.ClrBit(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.GetBit(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}
#else

#include "tset.h"

int main()
{
    int n, m, k, count;

    setlocale(LC_ALL, "Russian");
    cout << "Тестирование программ поддержки множества" << endl;
    cout << "              Решето Эратосфена" << endl;
    cout << "Введите верхнюю границу целых значений - ";
    cin >> n;
    TSet s(n + 1);
    // заполнение множества
    for (m = 2; m <= n; m++)
        s.InsElem(m);
    // проверка до sqrt(n) и удаление кратных
    for (m = 2; m * m <= n; m++)
        // если м в s, удаление кратных
        if (s.IsMember(m))
            for (k = 2 * m; k <= n; k += m)
                if (s.IsMember(k))
                    s.DelElem(k);
    // оставшиеся в s элементы - простые числа
    cout << endl << "Печать множества некратных чисел" << endl << s << endl;
    cout << endl << "Печать простых чисел" << endl;
    count = 0;
    k = 1;
    for (m = 2; m <= n; m++)
        if (s.IsMember(m))
        {
            count++;
            cout << setw(3) << m << " ";
            if (k++ % 10 == 0)
                cout << endl;
        }
    cout << endl;
    cout << "В первых " << n << " числах " << count << " простых" << endl;
    cout << "Создание нового массива из чисел некратных 3" << endl;
    int length;
    cout << "Введите верхнюю границу целых значений - ";
    cin >> length;
    TSet q(length + 1);
    for (int i = 1; i <= length; i++) {
        q.InsElem(i);
        for (int i = 1; i <= length; i++) {
            if (q.IsMember(i)) {
                for (int k = i * 3; k <= length; k *= 3) {
                    if (q.IsMember(k))
                        q.DelElem(k);

                }
            }
        }
    }
    cout << endl << "Печать множества чисел, которые не делятся на 3" << endl << q << endl;
    cout << endl << "Печать множества квадратов чисел, которые не делятся на 3, делятся на 4" << endl;
    q.Foo(length);
    q.Infile();
    q.Outfile();
    q.Add();
    



}
#endif