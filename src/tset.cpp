// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
  MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  TBitField res(this->BitField);
  return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  MaxPower = s.MaxPower;
  if (*this == s)
    delete[] this;
  else
  {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
  }
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet res(BitField | s.BitField);
  return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem < 0 || Elem > MaxPower)
    throw "Error";
  else
  {
    InsElem(Elem);
    return *this;
  }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (Elem < 0 || Elem > MaxPower)
    throw "Error";
  else
  {
    DelElem(Elem);
    return *this;
  }
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet res(BitField & s.BitField);
  return res;
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(~BitField);
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int l;
  istr >> l;
  TSet r(l);
  int t = 0;
  for (int i = 0; i < l; i++)
  {
    istr >> t;
    if (t == 0)
      r.DelElem(i);
    else
      r.InsElem(i);
  }
  s = r;
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  int n = s.GetMaxPower();
  ostr << "{";
  for (int i = 0; i < n; i++)
    if (s.IsMember(i))
      ostr << i << " ";
  ostr << "}";
  return ostr;
}
