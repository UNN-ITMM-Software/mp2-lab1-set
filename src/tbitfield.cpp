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
  if (len <= 0) { throw "TBitField init Error"; }
  MemLen = len;
  BitLen = MemLen * 8 * 4;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  if (bf == *this) { throw "TBitField init Error"; }
  MemLen = bf.MemLen;
  BitLen = bf.BitLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
}

TBitField::~TBitField()
{
  MemLen = 0;
  BitLen = 0;
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n > BitLen) { throw "Wrong TBitField function input"; }
  return (n >> 5);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n > BitLen) { throw "Wrong TBitField function input"; }
  return (1 << (n & (8 * 4) - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n > BitLen) { throw "Wrong TBitField function input"; }
  int ind = GetMemIndex(n);
  pMem[ind] = pMem[ind] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > BitLen) { throw "Wrong TBitField function input"; }
  int ind = GetMemIndex(n);
  pMem[ind] = pMem[ind] & (~(GetMemMask(n)));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > BitLen) { throw "Wrong TBitField function input"; }
  return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (bf == *this) { throw "TBitField operator Error"; }
  MemLen = bf.MemLen;
  BitLen = bf.BitLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (MemLen != bf.MemLen) { return 0; }
  else {
    for (int i = 0; i < MemLen; i++) { if (pMem[i] != bf.pMem[i]) { return 0; } }
    return 1;
  }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ((~(*this == bf)) & 1);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int maxLen = max(MemLen, bf.MemLen);
  int minLen = min(MemLen, bf.MemLen);
  TBitField Result(maxLen);
  for (int i = 0; i < maxLen; i++) {
    if (i < minLen) { Result.pMem[i] = pMem[i] | bf.pMem[i]; }
    else if (i >= MemLen) { Result.pMem[i] = bf.pMem[i]; }
    else { Result.pMem[i] = pMem[i]; }
  }
  return Result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int maxLen = max(MemLen, bf.MemLen);
  int minLen = min(MemLen, bf.MemLen);
  TBitField Result(maxLen);
  for (int i = 0; i < minLen; i++) { Result.pMem[i] = pMem[i] & bf.pMem[i]; }
  for (int i = minLen; i < maxLen; i++) { Result.pMem[i] = 0; }
  return Result;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField Result(MemLen);
  for (int i = 0; i < MemLen; i++) { Result.pMem[i] = ~(pMem[i]); }
  return Result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int t;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    cin >> t;
    if (t == 1) { bf.SetBit(i); }
    else if (t == 0) { bf.ClrBit(i); }
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength() / (8 * 4); i++)
  {
    TELEM t = bf.pMem[i];
    for (int j = 0; j < (8 * 4); j++)
    {
      cout << (t & 1);
      t >>= 1;
    }
    cout << ' ';
  }
  return ostr;
}
