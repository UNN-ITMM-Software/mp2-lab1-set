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
  if (len > -1)
  {
    bitLen = len;
    memLen = len * sizeof(TELEM) * 8;
    pMem = new TELEM[memLen];
    if (pMem != NULL)
    {
      for (int i = 0; i < memLen; i++)
        pMem[i] = 0;
    }
  }
  else
  {
    throw "error";
  }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  if (bf.bitLen <= 0)
    throw "error";
  else
  {
    memLen = bf.memLen;
    bitLen = bf.bitLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
}

TBitField::~TBitField()
{
  if (pMem != 0)
    delete[] pMem;
  pMem = 0;
  memLen = 0;
  bitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > bitLen))
  {
    throw "error";
  }
  else
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 && n < bitLen) throw "error";
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n > bitLen))
  {
    throw "error";
  }
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] | m;
  }
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n > bitLen))
  {
    throw "error";
  }
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n > bitLen))
  {
    throw "error";
  }
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    return (pMem[i] & m);
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (this == &bf)
    return *this;
  else
  {
    delete[] pMem;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    bitLen = bf.bitLen;
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
    return *this;
  }
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (memLen != bf.memLen || bitLen != bf.bitLen)
    return 0;
  else
  {
    for (int i = 0; i < memLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
        return 0;
    }
    return 1;
  }
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  if (memLen != bf.memLen || bitLen != bf.bitLen)
    return 1;
  else
  {
    for (int i = 0; i < memLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
        return 1;
    }
    return 0;
  }
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  if (bf.bitLen > bitLen)
    bitLen = bf.bitLen;
  TBitField res = (bitLen);
  for (int i = 0; i < memLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
  {
    res.pMem[i] = res.pMem[i] | bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  if (bf.bitLen > bitLen)
    bitLen = bf.bitLen;
  TBitField res = (bitLen);
  for (int i = 0; i < memLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    res.pMem[i] &= bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);
  for (int i = 0; i < res.bitLen; i++)
  {
    if (res.GetBit(i))
      res.ClrBit(i);
    else
      res.SetBit(i);
  }
  return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  int tmp;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    cin >> tmp;
    if (tmp == 1)
      bf.SetBit(i);
    else
      if (tmp == 0)
        bf.ClrBit(i);
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
    ostr << bf.GetBit(i);
  return ostr;
}
