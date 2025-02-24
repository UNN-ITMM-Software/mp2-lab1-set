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
TSet::TSet(const TSet& s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : bitField(bf)
{
  maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  TBitField res(this->bitField);
  return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
  return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
  bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
  bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
  bitField = s.bitField;
  maxPower = s.GetMaxPower();
  return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
  return bitField == s.bitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
  return bitField != s.bitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
  TSet res(bitField | s.bitField);
  return res;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
  bitField.SetBit(elem);
  return *this;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
  TSet res(bitField & elem);
  return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
  TSet res(bitField & s.bitField);
  return res;
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(*this);
  res.bitField = ~res.bitField;
  return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
  int in;
  cin >> in;
  if (in >= 0 && in < s.GetMaxPower())
  {
    s.InsElem(in);
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
  for (int i = 0; i < s.GetMaxPower(); i++)
    if (s.IsMember(i))
    {
      ostr << ' ' << i;
    }
  return ostr;
}
