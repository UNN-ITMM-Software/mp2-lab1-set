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
    MemLen = (len-1) / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
      pMem[i] = 0;
    }
  }
  else
    throw "Ошибка";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
  BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return (n/ (8 * sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  int mask;
  if (n < 0 || n >= BitLen)
    throw("Ошибка");
  mask = n - GetMemIndex(n) * (8 * sizeof(TELEM));
  return (1 << mask); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n >= 0 && n < BitLen)
    pMem[GetMemIndex(n)] |= GetMemMask(n);
  else
    throw("Ошибка");
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n >= 0 && n < BitLen)
    pMem[GetMemIndex(n)] &= (~GetMemMask(n));
  else
    throw("Ошибка");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == GetMemMask(n))
    return 1;
  else
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
    return *this;
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];  
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (MemLen != bf.MemLen)
  {
    return 0;
  }
  for (int i = 0; i < bf.MemLen; i++)
  {
    if (pMem[i] != bf.pMem[i])
      return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this == bf)
    return 0;
  return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int size;
  if (BitLen > bf.BitLen)
    size = BitLen;
  else
    size = bf.BitLen;
  TBitField result(size);
  for (int i = 0; i < MemLen && i < bf.MemLen; i++)
    result.pMem[i] = pMem[i] | bf.pMem[i];
  return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int size;
  if (BitLen > bf.BitLen)
    size = BitLen;
  else
    size = bf.BitLen;
  TBitField result(size);
  for (int i = 0; i < MemLen && i < bf.MemLen; i++)
    result.pMem[i] = pMem[i] & bf.pMem[i];
  return result;
}

TBitField TBitField::operator~(void) // отрицание
{
  for (int i = 0; i < BitLen; i++)
  {
    pMem[GetMemIndex(i)] ^= GetMemMask(i);
  }
  return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char element;
  for (int i = 0; i < bf.BitLen; i++)
  {
    istr >> element;
    if ((int)element == 1)
      bf.SetBit(i);
    if ((int)element == 0)
      bf.ClrBit(i);
    return istr;
  }
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
  {
    if ((bf.pMem[(int)(i / (sizeof(TELEM) * 8))] & bf.GetMemMask(i)) == bf.GetMemMask(i))
      ostr << "1";
    else
      ostr << "0";
  }
  return ostr;
}
