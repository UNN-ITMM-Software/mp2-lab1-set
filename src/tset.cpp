// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
 MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
 MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
 MaxPower = bf.GetLength();
}

TSet::operator TBitField()// преобразование типа к битовому полю
{
 return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
 return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
 if (Elem >= MaxPower || Elem < 0)
  throw "Error";

 return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
 if (Elem >= MaxPower || Elem < 0)
  throw "Error";
 BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
 if (Elem >= MaxPower || Elem < 0)
  throw "Error";
 BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
 MaxPower = s.MaxPower;
 BitField = s.BitField;
 return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
 if (BitField != s.BitField) return 0;
 else return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
 if (BitField != s.BitField) return 1;
 else return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
 TSet temp(BitField | s.BitField);
 return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
 TSet temp = *this;
 temp.InsElem(Elem);
 return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
 TSet temp = *this;
 temp.DelElem(Elem);
 return temp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{

 TSet temp(BitField & s.BitField);
 return temp;
}


TSet TSet::operator~(void) // дополнение
{
 TSet temp(*this);
 temp.BitField = ~(this->BitField);
 return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
 int i;
 cin >> i;
 for (; i > -1; cin >> i)
  s.BitField.SetBit(i);
 return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
 for (int i = 0; i < s.MaxPower; i++)
  cout << s.BitField.GetBit(i);
 cout << "}" << endl;
 return ostr;
}