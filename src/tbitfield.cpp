// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <math.h>
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  if (len <= 0)
    throw "Ошибка";
  BitLen = len;
  MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  if (bf.pMem == 0)
  {
    pMem = 0;
    MemLen = 0;
  }

  else
  {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
}

TBitField::~TBitField()
{
  if (pMem != 0)
  {
    delete[] pMem;
    pMem = 0;
    MemLen = 0;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n >= BitLen))
    throw "Ошибка";
  return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  int m = 1;
  return m << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n >= BitLen))
    throw "Ошибка";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n >= BitLen))
    throw "Ошибка";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] & ~m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= BitLen))
    throw "Ошибка";
  int i = GetMemIndex(n);
  return (pMem[i] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (this != &bf)
  {
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  int res = 1;
  if (BitLen != bf.BitLen)
    res = 0;
  else
    for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i])
      {
        res = 0;
        break;
      }
  return res;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  int res = 0;
  if (BitLen != bf.BitLen)
    res = 1;
  else
    for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i]) {
        res = 1;
        break;
      }
  return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  TBitField temp(len);
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] |= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  TBitField temp(len);
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] &= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  int len = BitLen;
  TBitField temp(len);
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) == 0)
      temp.SetBit(i);
    else
      temp.ClrBit(i);
  return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
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

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  for (int i = 0; i < bf.MemLen; i++)
  {
    ostr << bf.pMem[i] << "\t";
  }
  return ostr;
}