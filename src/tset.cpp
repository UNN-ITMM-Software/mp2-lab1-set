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
static const unsigned int TELEM_BIT_SIZE = (8*sizeof(TELEM));

TSet::TSet(int mp) : BitField(mp/TELEM_BIT_SIZE + 1)
{
  MaxPower =  mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField.GetLength()/TELEM_BIT_SIZE)
{
  MaxPower = s.GetMaxPower();
  for(int i = 0; i < s.BitField.GetLength()/TELEM_BIT_SIZE; i++)
  {
    BitField[i] = s.BitField.GetMemElem(i);
  }
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength()/TELEM_BIT_SIZE)
{
  MaxPower = bf.GetLength();
  for(int i = 0; i < bf.GetLength()/TELEM_BIT_SIZE; i++) {
    BitField[i] = bf.GetMemElem(i);
  }
}

TSet::operator TBitField()
{
  TBitField temp(this->BitField.GetMemLen());
  for(int i = 0; i < temp.GetMemLen(); i++)
  {
    temp[i] = this->BitField.GetMemElem(i);
  }

  return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  return (BitField.GetBit(Elem));
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
  if(this == &s)
    throw "Op ERROR: selfcopying";

  MaxPower = s.GetMaxPower();
  BitField = s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if(MaxPower != s.GetMaxPower())
    return 0;

  if(this->BitField == s.BitField)
    return 1;
  else
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if(*this == s)
    return 0;
  else
    return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  if(this->GetMaxPower() != s.GetMaxPower())
    throw "Op ERROR: different maxpower";

  TSet temp(*this);
  temp.BitField = temp.BitField | s.BitField;
  return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if(Elem >= MaxPower)
    throw "Op ERROR: different maxpower";

  TSet temp(*this);
  temp.BitField.SetBit(Elem);
  return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if(Elem >= MaxPower)
    throw "Op ERROR: different maxpower";

  TSet temp(*this);
  temp.BitField.ClrBit(Elem);
  return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  if(this->GetMaxPower() != s.GetMaxPower())
    throw "Op ERROR: different maxpower";

  TSet temp(*this);
  temp.BitField = temp.BitField & s.BitField;
  return temp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet temp(*this);
  temp.BitField = ~temp.BitField;
  return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int i;
  istr >> i;
  if(i >= 0 && i < s.GetMaxPower()) 
  {
    s.InsElem(i);
  }
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << '{';
  for(int i = 0; i < s.GetMaxPower(); i++)
  {
    if(s.IsMember(i))
      ostr << i << ',' << ' ';
  }

  ostr << '}';
  return ostr;
}
