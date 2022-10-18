
#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : bitField(mp)
{
  MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
  int l = bf.GetLength();
  maxPower = l;
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

TSet& TSet::operator=(const TSet &s) // присваивание
{
  maxPower = s.maxPower;
  if (*this == s)
    delete[] this;
  else
  {
    maxPower = s.maxPower;
    bitField = s.bitField;
    return *this;
  }
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (maxPower != s.maxPower)
    return 0;
  else
    return bitField == s.bitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this==s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet res(bitField | s.bitField);
  return res;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
  if (elem < 0 || Elem > maxPower)
    throw "error";
  else
  {
    InsElem(elem);
    return *this;
  }
}

TSet TSet::operator-(const int elem) // разность с элементом
{
  if (elem < 0 || elem > maxPower)
    throw "error";
  else
  {
    DelElem(elem);
    return *this;
  }
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet res(bitField & s.bitField);
  return res;
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(~bitField);
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int len;
  istr >> len;
  TSet res(len);
  int t = 0;
  for (int i = 0; i < len; i++)
  {
    istr >> t;
    if (t == 0)
      res.DelElem(i);
    else
      res.InsElem(i);
  }
  s = res;
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
