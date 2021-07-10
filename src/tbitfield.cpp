// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len > 0) {
    BitLen = len;
    MemLen = (len - 1) / 32 + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = 0;
  }
  else
    throw 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem != 0) delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n >= 0 && n < BitLen)
    return n / 32;
  else
    throw 2;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n >= 0 && n < BitLen)
    return TELEM(1) << (n % 32);
  else
    throw 3;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (&bf == this) return *this;
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (this->BitLen != bf.BitLen) return false;
  for (int i = 0; i < MemLen; i++)
    if (pMem[i] != bf.pMem[i]) return false;
  return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int n = bf.GetLength();
  if (GetLength() < n)
    n = GetLength();
  TBitField res((bf.GetLength() > GetLength()) ? bf : *this);
  for (int i = 0; i < n; i++)
    if (GetBit(i) | bf.GetBit(i))
      res.SetBit(i);
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int a = GetLength();
  int b = bf.GetLength();
  if (a > b) swap(a, b);
  TBitField res(b);
  for (int i = 0; i < a; i++)
    if (GetBit(i) & bf.GetBit(i))
      res.SetBit(i);
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  int n = GetLength();
  TBitField res(n);
  for (int i = 0; i < n; i++)
    if (!GetBit(i))
      res.SetBit(i);
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int n;
  istr >> n;
  bf = *new TBitField(n);
  char c;
  for (int i = 0; i < n; i++) {
    istr >> c;
    if (c) bf.SetBit(i);
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  int n = bf.GetLength();
  ostr << n << endl;
  for (int i = 0; i < n; i++)
    ostr << bf.GetBit(i);
  ostr << endl;
  return ostr;
}
