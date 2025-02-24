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

TSet::TSet(int mp) : BitField(1)
{
  if (mp < 0) throw "Error";
  MaxPower = mp;
  BitField = TBitField(MaxPower);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(1)
{
  MaxPower = s.MaxPower;
  BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(1)
{
  MaxPower = bf.GetLength();
  BitField = bf;
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
  //if (Elem < 0) throw "Error";
  if (BitField.GetBit(Elem) == 1) return true;
  return false;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  //if (Elem < 0) throw "Error";
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  //if (Elem < 0) throw "Error";
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  if (&s == this) return *this;
  MaxPower = s.MaxPower;
  BitField = s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (MaxPower != s.MaxPower) return false;
  if (BitField != s.BitField) return false;
  return true;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if (MaxPower != s.MaxPower) return true;
  if (BitField != s.BitField) return true;
  return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet tmp(s.MaxPower > MaxPower ? s.MaxPower : MaxPower);
  tmp.BitField = BitField | s.BitField;
  return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet tmp(Elem > MaxPower ? Elem : MaxPower);
  tmp.InsElem(Elem);
  return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet tmp(MaxPower);
  tmp.DelElem(Elem);
  return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet tmp(s.MaxPower > MaxPower ? s.MaxPower : MaxPower);
  tmp.BitField = BitField & s.BitField;
  return tmp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet tmp(MaxPower);
  tmp = ~BitField;
  return tmp; 
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{

  int tmp = 0;
  for (int i = 0; i < s.MaxPower; i++)
  {
    istr >> tmp;
    s.InsElem(tmp);
  }
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  for (int i = 0; i < s.MaxPower; i++)
  {
    ostr << s.BitField.GetBit(i);
  }
  return ostr;
}
