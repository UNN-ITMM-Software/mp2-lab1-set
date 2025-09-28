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

TSet::TSet(int mp) : bitField(mp)
{
  maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.GetMaxPower())
{
  maxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf.GetLength())
{
  maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return TBitField(maxPower);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
  if (elem > maxPower)
    throw "tak nel'zya";
  return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
  if (elem > maxPower)
    throw "tak nel'zya";
  bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
  if (elem > maxPower)
    throw "tak nel'zya";
  bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet &TSet::operator=(const TSet &s) // присваивание
{
  maxPower = s.GetMaxPower();
  bitField = s.bitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (maxPower != s.GetMaxPower())
    return 0;
  return bitField == s.bitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  //return !(*this == s);
  if (maxPower != s.GetMaxPower())
    return 1;
  return bitField != s.bitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet temp(std::max(maxPower, s.GetMaxPower()));
  temp.bitField = bitField | s.bitField;
  return temp;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
  if (elem > maxPower)
    throw "tak nel'zya";
  TSet temp(maxPower);
  temp.bitField = bitField;
  temp.bitField.SetBit(elem);
  return temp;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
  if (elem > maxPower)
    throw "tak nel'zya";
  bitField.ClrBit(elem);
  return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet temp(std::max(maxPower, s.GetMaxPower()));
  temp.bitField = bitField & s.bitField;
  return temp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet temp(maxPower);
  temp.bitField = ~bitField;
  return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  std::cout << "Enter MaxPower: ";
  istr >> s.maxPower;
  istr >> s.bitField;
  return istr;
}

ostream &operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << "MaxPower: " << s.GetMaxPower() << std::endl;
  ostr << s.bitField;
  return ostr;
}
