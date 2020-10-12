// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

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

TSet& TSet::operator=(const TSet& s) // присваивание
{
  BitField = s.BitField;
  MaxPower = s.MaxPower;
  return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
  return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
  return !(BitField == s.BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
  TSet temp(BitField | s.BitField);
  return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet temp(*this);
  temp.InsElem(Elem);
  return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet temp(*this);
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
  TSet temp(~BitField);
  return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
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
    } while (ch == ',' && ch != '}');
  } while (ch != '}');
  return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
  int i;
  ostr << '{';
  for (i = 0; i < s.MaxPower; i++)
    if (s.IsMember(i))
    {
      ostr << i;
      break;
    }
  i++;
  for (i; i < s.MaxPower; i++)
    if (s.IsMember(i))
      ostr << ", " << i;
  ostr << '}';
  return ostr;
}

// дополнительные задания

string TSet::GetElemsModK(int k)
{
  string s = "";
  int len = BitField.GetLength();
  for (int i = 0; i < len; i++)
    if (BitField.GetBit(i) && i % k == 0)
      s += i + 48;
  return s;
}

void TSet::ChangeElem(int n)
{
  if (BitField.GetBit(n))
    BitField.ClrBit(n);
  else
    BitField.SetBit(n);
}

ofstream& operator<<(ofstream& out, const TSet s)
{
  out << s;
  return out;
}
