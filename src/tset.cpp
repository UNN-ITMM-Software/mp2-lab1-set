// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
  if (mp < 0)
    throw "error";
  MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
  MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  if (0 > Elem || Elem > MaxPower)
    throw "error";
  return BitField.GetBit(Elem);
}
void TSet::InsElem(const int Elem) // включение элемента множества
{
  if (0 > Elem || Elem > MaxPower)
    throw "error";
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  if (0 > Elem || Elem > MaxPower)
    throw "error";
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
  BitField = s.BitField;
  MaxPower = s.MaxPower;
  return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
  if (s.BitField != BitField)
    return 0;
  return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
  return !operator==(s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
  int m = MaxPower;
  if (s.MaxPower > m) m = s.MaxPower;
  TSet tmp(m);
  tmp.BitField = BitField | s.BitField;
  return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (0 > Elem || Elem > MaxPower)
    throw "error";
  BitField.SetBit(Elem);
  return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (0 > Elem || Elem > MaxPower)
    throw "error";
  BitField.ClrBit(Elem);
  return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
  int m = MaxPower;
  if (s.MaxPower > m) m = s.MaxPower;
  TSet tmp(m);
  tmp.BitField = BitField & s.BitField;
  return tmp;
}

TSet TSet::operator~(void) // дополнение
{
  for (int i = 0; i < MaxPower; i++)
    if (BitField.GetBit(i) != 0)
      BitField.ClrBit(i);
    else
      BitField.SetBit(i);
  return *this;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
  for (int i = 0; i < s.BitField.GetLength(); i++)
  {
    if (s.BitField.GetBit(i))
      istr >> i;
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{

  for (int i = 0; i < s.BitField.GetLength(); i++)
  {
    if (s.BitField.GetBit(i))
      ostr << i << " ";
  }
  return ostr;
}