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

TSet::TSet(int mp) : bitField(1)
{
  if (mp < 0) throw "Error";
  maxPower = mp;
  bitField = TBitField(maxPower);
}

// конструктор копирования
TSet::TSet(const TSet& s) : bitField(1)
{
  maxPower = s.maxPower;
  bitField = s.bitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : bitField(1)
{
  maxPower = bf.GetLength();
  bitField = bf;
}

TSet::operator TBitField()
{
  return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  //if (Elem < 0) throw "Error";
  if (bitField.GetBit(Elem) == 1) return true;
  return false;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  //if (Elem < 0) throw "Error";
  bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  //if (Elem < 0) throw "Error";
  bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
  if (&s == this) return *this;
  maxPower = s.maxPower;
  bitField = s.bitField;
  return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
  if (maxPower != s.maxPower) return false;
  if (bitField != s.bitField) return false;
  return true;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
  if (maxPower != s.maxPower) return true;
  if (bitField != s.bitField) return true;
  return false;
}

TSet TSet::operator+(const TSet& s) // объединение
{
  TSet tmp(s.maxPower > maxPower ? s.maxPower : maxPower);
  tmp.bitField = bitField | s.bitField;
  return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet tmp(Elem > maxPower ? Elem : maxPower);
  tmp.InsElem(Elem);
  return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet tmp(maxPower);
  tmp.DelElem(Elem);
  return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
  TSet tmp(s.maxPower > maxPower ? s.maxPower : maxPower);
  tmp.bitField = bitField & s.bitField;
  return tmp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet tmp(maxPower);
  tmp = ~bitField;
  return tmp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{

  int tmp = 0;
  for (int i = 0; i < s.maxPower; i++)
  {
    istr >> tmp;
    s.InsElem(tmp);
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
  for (int i = 0; i < s.maxPower; i++)
  {
    ostr << s.bitField.GetBit(i);
  }
  return ostr;
}
