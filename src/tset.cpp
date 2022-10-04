
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
  int l = bf.GetLength();
  MaxPower = l;
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
  if (MaxPower != s.MaxPower)
    return 0;
  else
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this==s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet res(BitField | s.BitField);
  return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem < 0 || Elem > MaxPower)
    throw "error";
  else
  {
    InsElem(Elem);
    return *this;
  }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (Elem < 0 || Elem > MaxPower)
    throw "error";
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
