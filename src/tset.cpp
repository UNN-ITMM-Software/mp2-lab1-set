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
  TBitField temp(this->BitField);
  return temp;
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
  if (this != &s)
  {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
  }
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet temp(BitField | s.BitField);
  return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet temp(BitField);
  temp.BitField.SetBit(Elem);
  return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet temp(BitField);
  temp.BitField.ClrBit(Elem);
  return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet temp(BitField & s.BitField);
  return temp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet temp(~BitField);
  return temp;
}

// перегрузка ввода/вывода
// Формат данных - { i1, i2,...,  in}

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int temp;
  char ch;
  do
  {
    istr >> ch;
  } while (ch != '{');
  do
  {
    istr >> temp;
    s.InsElem(temp);
    do
    {
      istr >> ch;
    } while ((ch != ',') && (ch != '}'));
  } while (ch != '}');
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  int num;
  char ch = ' ';
  ostr << "{";
  num = s.GetMaxPower();
  for (int i = 0; i < num; i++)
    if (s.IsMember(i))
    {
      ostr << ch << ' ' << i;
      ch = ',';
    }
  ostr << "}";
  return ostr;
}