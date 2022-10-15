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
  if (len < 0) throw "Lenght of BitField can't be less 0";

  BitLen = len;

  MemLen = 8 * sizeof(TELEM) * len;

  pMem = new TELEM[len];
  for (int i = 0; i < len; i++)
  {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  if (bf.BitLen < 0) 
    throw ("Can't copy BitField");
  else
  {
    MemLen = bf.MemLen;

    BitLen = bf.BitLen;

    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
   
}

TBitField::~TBitField()
{
  pMem = nullptr;
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n >= BitLen)) 
    throw "Error";
  return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return 1 << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n >= BitLen)) 
    throw "Error";
  
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n >= BitLen))
    throw "Error";

  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= BitLen))
    throw "Error";

  return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
  {
    pMem = nullptr;
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (MemLen != bf.MemLen || BitLen != bf.BitLen)
    return 0;
  else
    for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i])
        return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int length = max(BitLen, bf.BitLen);
  TBitField res(length);
  int i = 0;
  for (i; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (i = 0; i < bf.MemLen; i++)
    res.pMem[i] = res.pMem[i] | bf.pMem[i];
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int length = max(BitLen, bf.BitLen);
  TBitField res(length);
  int i = 0;
  for (i; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (i = 0; i < bf.MemLen; i++)
    res.pMem[i] = res.pMem[i] & bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);
  for (int i = 0; i < res.BitLen; i++)
  {
    if (res.GetBit(i))
      res.ClrBit(i);
    else
      res.SetBit(i);
  }
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int length;
  istr >> length;
  TBitField res(length);
  char* mas = new char[length];
  istr >> mas;
  for (int i = 0; i < bf.BitLen; i++)
    if (mas[i] == 0)
      bf.ClrBit(i);
    else if (mas[i] == 1)
      bf.SetBit(i);
    else throw "Error";
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
