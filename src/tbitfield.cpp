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
  if (len > 0)
  {
    bitLen = len;
    memLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = 0;
    }
  }
  else throw "Error";
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  memLen = bf.memLen;
  bitLen = bf.bitLen;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  if (pMem != 0) delete[] pMem;
  memLen = 0;
  bitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= bitLen) throw "Error";
  return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= bitLen) throw "Error";
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= bitLen) throw "Error";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= bitLen) throw "Error";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  pMem[i] = pMem[i] & ~m;
}

bool TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= bitLen) throw "Error";
  int i = GetMemIndex(n);
  int m = GetMemMask(n);
  return (pMem[i] & m) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (&bf == this) return *this;
  delete[] pMem;
  memLen = bf.memLen;
  bitLen = bf.bitLen;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
  return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (memLen != bf.memLen) return false;
  for (int i = 0; i < memLen; i++)
  {
    if (pMem[i] != bf.pMem[i]) return false;
  }
  return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
  if (memLen != bf.memLen) return true;
  for (int i = 0; i < memLen; i++)
  {
    if (pMem[i] != bf.pMem[i]) return true;
  }
  return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  if (memLen != bf.memLen) throw "Error";
  TBitField res(*this);
  for (int i = 0; i < memLen; i++)
  {
    res.pMem[i] = pMem[i] | bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  if (memLen != bf.memLen) throw "Error";
  TBitField res(*this);
  for (int i = 0; i < memLen; i++)
  {
    res.pMem[i] = pMem[i] & bf.pMem[i];
  }
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);
  for (int i = 0; i < bitLen; i++)
  {
    if (GetBit(i) == 1) res.ClrBit(i);
    else res.SetBit(i);
  }
  return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  int tmp = 0;
  for (int i = 0; i < bf.bitLen; i++)
  {
    istr >> tmp;
    bf.SetBit(tmp);
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
  {
    ostr << bf.GetBit(i);
  }
  return ostr;
}
