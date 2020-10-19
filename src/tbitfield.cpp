// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len > 0)
  {
    BitLen = len;
    pMem = nullptr;
    MemLen = ceil((double)BitLen / 8 * sizeof(TELEM));
    pMem = new TELEM[MemLen];
    if (pMem != nullptr)
    {
      for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
    }
    else
      throw - 1;
  }
  else throw - 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.BitLen;
  pMem = nullptr;
  pMem = new TELEM[MemLen];
  if (pMem != nullptr)
  {
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  else
    throw - 1;
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n >= 0 && n < BitLen)
    return (floor((double)n / (8 * sizeof(TELEM))));
  else
    throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n >= 0 && n < BitLen)
  {
    int tempBN = n % (8 * sizeof(TELEM));
    TELEM mask = 1 << tempBN;
    return mask;
  }
  else
    throw - 1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n > BitLen)
    throw - 1;
  int i = GetMemIndex(n);
  pMem[i] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > BitLen)
    throw - 1;
  int i = GetMemIndex(n);
  pMem[i] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > BitLen)
    throw -1;
  int i = GetMemIndex(n);
  if ((pMem[i] & GetMemMask(n)) != 0)
  {
    return 1;
  }
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
  {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  bool res = 1;
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

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  bool res = 0;
  if (BitLen != bf.BitLen)
    res = 1;
  else
    for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i])
      {
        res = 1;
        break;
      }
  return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int templen = BitLen;
  if (bf.BitLen > templen)
    templen = bf.BitLen;
  TBitField temp(templen);
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] |= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int templen = BitLen;
  if (bf.BitLen > templen)
    templen = bf.BitLen;
  TBitField temp(templen);
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] &= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  int templen = BitLen;
  TBitField temp(templen);
  for (int i = 0; i < templen; i++)
    if (this->GetBit(i) == 0)
      temp.SetBit(i);
    else
      temp.ClrBit(i);
  return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char c;
  int k = 0;
  do
  {
    istr >> c;
    if (c == '1')
    {
      bf.SetBit(k);
    }
    if (c == '0')
    {
      bf.ClrBit(k);
    }
    k++;
  } while ((c == '1') || (c == '0'));
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
  {
    ostr << bf.GetBit(i);
  }
  return ostr;
}
