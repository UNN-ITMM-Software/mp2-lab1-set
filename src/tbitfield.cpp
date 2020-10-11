// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 1) 
  throw "Wrong size";
  BitLen = len;
  MemLen = ceil((double)(len) / (sizeof(TELEM) * 8));
  pMem = nullptr;
  pMem = new TELEM[MemLen];
  if (pMem == nullptr) 
    throw "Memmory Error";
  for (int i = 0; i < MemLen; i++)
  pMem[i] = 0u;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = nullptr;
  pMem = new TELEM[MemLen];
  if (pMem == nullptr)
    throw "Memmory Error";
  for (int i = 0; i < MemLen; i++)
  pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
    delete[] pMem;
  pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return (floor((double)(n) / (sizeof(TELEM) * 8)));
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
  if ((n < 0) || (n >= BitLen)) 
  throw "Wrong index";
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || BitLen <= n) 
  throw "Wrong index";
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= BitLen)) 
  throw "Error";
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % (sizeof(TELEM) * 8));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = nullptr;
  pMem = new TELEM[MemLen];
  if (pMem == nullptr) 
    throw "Memmory Error";
  for (int i = 0; i < MemLen; i++)
  pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (this == &bf) 
    return 1;
  if (BitLen != bf.BitLen)
    return 0;
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) != bf.GetBit(i)) return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TBitField res(BitLen > bf.BitLen ? BitLen : bf.BitLen);
  if (BitLen > bf.BitLen)
  {
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] = bf.pMem[i];
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] |= pMem[i];
  }
  else
  {
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] |= bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField res(BitLen > bf.BitLen ? BitLen : bf.BitLen);
  if (BitLen > bf.BitLen)
  {
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] = bf.pMem[i];
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] &= pMem[i];
  }
  else
  {
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] &= bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(BitLen);
  for (int i = 0; i < BitLen; i++)
  if (GetBit(i) == 0)
    res.SetBit(i);
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  string string;
  istr >> string;
  TBitField res(string.length());
  for (int i = 0; i < string.length(); i++)
  if (string[i] == '1') res.SetBit(string.length() - 1 - i);
  bf = res;
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
  ostr << bf.GetBit(i);
  return ostr;
}
