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
  if (mp > 0)
  {
    this->MaxPower = mp;
  }
  else
  {
    throw "bad data";
  }
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  TBitField res(this->BitField);

  return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
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
  TSet res(s);
  
  swap(*this, res);

  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return s.BitField == this->BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return s.BitField != this->BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet res(this->BitField | s.BitField);

  return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet res(this->BitField | Elem);

  return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet res(this->BitField & Elem);

  return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet res(this->BitField & s.BitField);

  return res;
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(~(this->BitField));

  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int f = 0;

  cin >> f;

  if ((f >= 0) && (f <= s.MaxPower))
  {
    s.InsElem(f);

    return istr;
  }
  else
  {
    throw "bad data";
  }
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  for (int i = 0; i < s.GetMaxPower(); i++)
  {
    if (s.IsMember(i))
    {
      ostr << i << " ";
    }
  }

  return ostr;
}
