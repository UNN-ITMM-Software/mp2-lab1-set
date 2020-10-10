// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>
#include <string>

 #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

#ifndef USE_SET // Использовать класс TBitField

/#include "tbitfield.h"

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
	

		const int size = 5;
		TSet set1(size), set2(size), set3(size), expSet(size);
		// set1 = {1, 2, 4}
		set1.InsElem(1);
		set1.InsElem(2);
		set1.InsElem(4);
		// set2 = {0, 1, 2}
		set2.InsElem(0);
		set2.InsElem(1);
		set2.InsElem(2);
		set3 = set1 * set2;
		// expSet = {1, 2}
		expSet.InsElem(1);
		expSet.InsElem(2);

		cout << (expSet == set3);
	}/*/*int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
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
  cout << "В первых " << n << " числах " << count << " простых" << endl;*/

  /*try {
	  TSet m(20);
	  cout << "Input elements:" << endl;
	  int t;
	  for (int i = 0; i < 11; i++)
	  {
		  cin >> t;
		  m.InsElem(t);
	  }
	  cin >> m;
	  cout << m;
  }
  catch (logic_error& e)
  {
	  cout << e.what();
  }*/


 

/*//Доп.задание 1: запись в файл и чтение из файла
TSet m(20);
cin >> m;

ofstream myfile_w;
myfile_w.open("myset.txt");
myfile_w << m;
myfile_w.close();

string line;
ifstream myfile_r("myset.txt");
if (myfile_r.is_open())
{
	getline(myfile_r, line);
	int n = stoi(line);
	TSet m2(n);

	getline(myfile_r, line);
	string number;

	for (char& c : line)
	{
		if (c >= '0' && c <= '9')
			number += c;
		if (c == ' ')
		{
			m2.InsElem(stoi(number));
			number = "";
		}
	}


	myfile_r.close();

	cout << m2 << endl;
}

//Доп.задание 2: найти элементы, которые являются степенью тройки
int n;
cout << "Input MaxPower: ";
cin >> n;
TSet m3(n);
cin >> m3;
cout << m3 << endl;

int pow = 1;
while (pow <= n)
{
	if (m3.IsMember(pow))
		cout << pow << " ";
	pow *= 3;
}


 // system("pause");
 
*/
//}	

#endif