// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static const int SIZE = sizeof(TELEM)*8;

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "bad length!";
  bitLen = len;
  memLen = bitLen / SIZE;
  pMem = new TELEM(memLen);
  for (int i = 0; i < memLen; ++i)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.GetLength();
  memLen = bitLen / SIZE;
  pMem = new TELEM(memLen);
  for (int i = 0; i < memLen; ++i)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс элемента в массиве в котором хранится бит
{
    return n / SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return std::pow(2, n % SIZE);
  //return std::pow(2, n-GetMemIndex(n)*SIZE);
  //TELEM mask = 0;
  //mask >> (n & ((1 << 32) - 1));
  //return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n > bitLen) || (n < 0))
    throw "bad index";
  int pos = GetMemIndex(n);
  TELEM aboba = GetMemMask(n);
  //std::cout << "Mask: " << aboba << std::endl;
  pMem[pos] = pMem[pos] | aboba;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n > bitLen) || (n < 0))
    throw "bad index";
  int pos = GetMemIndex(n);
  TELEM aboba = GetMemMask(n);
  pMem[pos] = pMem[pos] & ~aboba;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n > bitLen) || (n < 0))
    throw "bad index";
  int pos = GetMemIndex(n);
  TELEM aboba = GetMemMask(n);
  if ((pMem[pos] & aboba) != 0)
    return 1;
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (pMem != nullptr)
    delete[] pMem;
  bitLen = bf.GetLength();
  memLen = bitLen / SIZE + 1;
  pMem = new TELEM(memLen);
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.GetLength())
    return 0;

  for(int i = 0; i < memLen; i++)
    if (pMem[i] != bf.pMem[i])
      return 0;
  
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  //return !(*this == bf);
  if (bitLen != bf.GetLength())
    return 1;

  for(int i = 0; i < bitLen; i++)
    if (GetBit(i) != bf.GetBit(i))
      return 1;
  
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TBitField aboba(std::max(bitLen, bf.GetLength()));
  for (int i = 0; i < aboba.GetLength()/SIZE; i++)
    aboba.pMem[i] = pMem[i] | bf.pMem[i];
  return aboba;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField aboba(std::max(bitLen, bf.GetLength()));
  for (int i = 0; i < aboba.GetLength()/SIZE; i++)
    aboba.pMem[i] = pMem[i] & bf.pMem[i];
  return aboba;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField aboba(bitLen);
  for (int i = 0; i < aboba.GetLength()/SIZE; i++)
    aboba.pMem[i] = ~pMem[i];
  return aboba;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int num = -1;
  for (int i = 0; i < bf.GetLength(); ++i)
  {
    std::cout << "Enter value of bit #" << i << std::endl;
    istr >> num;
    if (num != 0 && num != 1)
      throw "invalid value of a bit!";
    if (num == 1)
      bf.SetBit(i);
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
    ostr << bf.GetBit(i);
  ostr << std::endl;
  return ostr;
}
