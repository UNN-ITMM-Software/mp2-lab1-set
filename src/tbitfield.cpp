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
  if (len < 0)
    throw "error";
  MemLen = len;
  pMem = new TELEM[len];
  for (int i = 0; i < len; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  this->MemLen = bf.GetLength();
  this->BitLen = bf.GetBit(this->MemLen);
  for (int i = 0; i < this->MemLen; i++)
    this->pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem != 0)
  {
    delete[](this->pMem);
    pMem = 0;
    this->BitLen = 0;
    this->MemLen = 0;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0)
    throw "n < 0";
  if (n > sizeof(int) * 8 * n)
    throw "error";
  int i = n >> (int)(log2(8 * sizeof(int)));
  return i;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0)
    throw "error";
  if (n > sizeof(int) * 8 * n)
    throw "error";
  int m = 1<<(n&(sizeof(int)));
  return m;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return FAKE_INT;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0)
    throw "error";
  if (n > sizeof(int) * 8 * n)
    throw "error";
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0)
    throw "error";
  if (n > sizeof(int) * 8 * n)
    throw "error";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] & ~m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0)
    throw "error";
  if (n > sizeof(int) * 8 * n)
    throw "error";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  return pMem[i] & m;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
