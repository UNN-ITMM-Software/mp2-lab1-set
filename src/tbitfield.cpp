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

size_t TBitField::GET_INDEX_CONST = mylog2(8 * sizeof(TELEM));

TBitField::TBitField(int len)
{
  if (len <= 0)
    throw out_of_range("Len must be > 0.");
  BitLen = len;
  MemLen = GetMemIndex(BitLen) + 1;
  pMem = new TELEM[MemLen];
  for (size_t i = 0; i < MemLen; i++)
  {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  MemLen = bf.MemLen;
  BitLen = bf.BitLen;
  pMem = new TELEM[MemLen];
  for (size_t i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n >> TBitField::GET_INDEX_CONST;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM m = 1;
  return m << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0)
    throw out_of_range("n must be > 0");
  if (n >= BitLen)
    throw out_of_range("n must be less than BitLien");
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0)
    throw out_of_range("n must be > 0");
  if (n >= BitLen)
    throw out_of_range("n must be less than BitLien");
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0)
    throw out_of_range("n must be > 0");
  if (n >= BitLen)
    throw out_of_range("n must be less than BitLien");
  return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (pMem == bf.pMem)
    return *this;
  BitLen = bf.BitLen;
  if (MemLen != bf.MemLen || pMem == nullptr)
  {
    delete[] pMem;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
  }
  for (size_t i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (BitLen != bf.BitLen)
    return false;
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) != bf.GetBit(i))
      return false;
  return true;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  if (BitLen != bf.BitLen)
    return true;
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) != bf.GetBit(i))
      return true;
  return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int highBitLen;
  int lowBitLen;
  const TBitField* highBitField;
  if (BitLen > bf.BitLen)
  {
    highBitLen = BitLen;
    lowBitLen = bf.BitLen;
    highBitField = this;
  }
  else
  {
    highBitLen = bf.BitLen;
    lowBitLen = BitLen;
    highBitField = &bf;
  }
  TBitField tmp(highBitLen);
  int i;
  for (i = 0; i < lowBitLen; i++)
    if (GetBit(i) | bf.GetBit(i))
      tmp.SetBit(i);
  for (; i < highBitLen; i++)
    if (highBitField->GetBit(i))
      tmp.SetBit(i);
  return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int highBitLen;
  int lowBitLen;
  if (BitLen > bf.BitLen)
  {
    highBitLen = BitLen;
    lowBitLen = bf.BitLen;
  }
  else
  {
    highBitLen = bf.BitLen;
    lowBitLen = BitLen;
  }
  TBitField tmp(highBitLen);
  for (int i = 0; i < lowBitLen; i++)
    if (GetBit(i) & bf.GetBit(i))
      tmp.SetBit(i);
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField tmp(BitLen);
  int i;
  for (i = 0; i < MemLen - 1; i++)
    tmp.pMem[i] = ~pMem[i];
  for (i = (MemLen - 1) * 8 * sizeof(TELEM); i < BitLen; i++)
    if (!GetBit(i))
      tmp.SetBit(i);
  return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  const int IN_BUFFER = 5;
  char c;
  int i = 0;
  bf = TBitField(1);

  while (istr.get(c) && c != 10)
  {
    if (i % IN_BUFFER == 0)
      bf = bf | TBitField(i + IN_BUFFER);
    if (c != '0')
      bf.SetBit(i);
    i++;
  }
  if (bf.BitLen > i)
  {
    TBitField tmp = bf;
    bf = TBitField(i);
    for (i = 0; i < bf.MemLen; i++)
      bf.pMem[i] = tmp.pMem[i];
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
