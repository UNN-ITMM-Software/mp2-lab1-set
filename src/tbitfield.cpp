// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  if (len < 1)
    throw "Error: Len < 1";
  BitLen = len;
  MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
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
  if (pMem != 0)
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= BitLen)
    throw "Error: out of range";
  return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen)
    throw "Error: out of range";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] | m;    
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen)
    throw "Error: out of range";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] & ~m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= BitLen)
    throw "Error: out of range";
  int i = GetMemIndex(n);
  return (pMem[i] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
    return*this;
  delete[]pMem;
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int tmp = 1;
  if (BitLen != bf.BitLen)
    return tmp = 0;
  else
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        return tmp = 0;
      }
    }
  return tmp = 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int tmp = 0;
  if (BitLen != bf.BitLen)
    tmp = 1;
  else
    for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i]) {
        tmp = 1;
        break;
      }
  return tmp;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  TBitField tmp(len);
  for (int i = 0; i < MemLen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    tmp.pMem[i] |= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  TBitField tmp(len);
  for (int i = 0; i < MemLen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    tmp.pMem[i] &= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  int len = BitLen;
  TBitField tmp(len);
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) == 0)
      tmp.SetBit(i);
    else
      tmp.ClrBit(i);
  return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  for (int i = 0; i < bf.MemLen; i++)
  {
    istr >> bf.MemLen;
    for (int i = 0; i < bf.MemLen; i++)
    {
      istr >> bf.pMem[i];
    }
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.MemLen; i++)
  {
    ostr << bf.pMem[i] << "\t";
  }
  return ostr;
}
