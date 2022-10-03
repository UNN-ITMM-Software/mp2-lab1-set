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
  if (len <= 0)
    throw "len error";
  else
  {
    BitLen = sizeof(TELEM) * 8 * len;

    MemLen = len;

    pMem = new TELEM[MemLen];

    for (int i = 0; i < len; i++)
    {
      pMem[i] = 0;
    }
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;

  MemLen = bf.MemLen;

  pMem = new TELEM[MemLen];

  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
  {
    BitLen = 0;

    MemLen = 0;

    delete[] pMem;

    pMem = nullptr;
  }
  else
  {
    throw "delete error";
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n >= 0) && (n <= BitLen))
  {
    return n >> 5;
  }
  else
  {
    throw "error index";
  }
  return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n >= 0) && (n <= BitLen))
  {
    return 1 << (n % 32);
  }
  else
  {
    throw "error index";
  }
  return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return MemLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n >= 0) && (n <= BitLen))
  {
    int i = GetMemIndex(n);

    int m = GetMemMask(n);

    pMem[i] = pMem[i] | m;
  }
  else
  {
    throw "error index";
  }
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n >= 0) && (n <= BitLen))
  {
    int i = GetMemIndex(n);

    int m = GetMemMask(n);

    pMem[i] = pMem[i] & (~m);
  }
  else
  {
    throw "error index";
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n >= 0) && (n <= BitLen))
  {
    int i = GetMemIndex(n);

    int m = GetMemMask(n);
    
    return pMem[i] & m;
  }
  else
  {
    throw "error index";
  }
  return FAKE_INT;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  TBitField a(bf);

  swap(*this, a);
  
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bf.MemLen != MemLen)
    return false;
  else
  {
    int f = 0;
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[1])
        f = 1;
    }
    if (f == 1)
      return false;
    else
      return true;
  }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{ 
  return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int m = BitLen;

  if (bf.BitLen > m)
  {
    m = bf.BitLen;
  }

  TBitField res(*this);

  for (int i = 0; i < m; i++)
  {
    res.pMem[i] = res.pMem[i] | bf.pMem[i];
  }

  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int m = BitLen;

  if (bf.BitLen > m)
  {
    m = bf.BitLen;
  }

  TBitField res(*this);

  for (int i = 0; i < m; i++)
  {
    res.pMem[i] = res.pMem[i] & bf.pMem[i];
  }

  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);

  for (int i = 0; i < res.BitLen; i++)
  {
    if (res.GetBit(i))
    {
      res.ClrBit(i);
    }
    else
    {
      res.SetBit(i);
    }
  }

  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int f = 0;

  for (int i = 0; i < bf.GetLength(); i++)
  {
    cin >> f;

    if (f == 1)
    {
      bf.SetBit(i);
    }
    if (f == 0)
    {
      bf.ClrBit(i);
    }
    else
    {
      throw "bad data";
    }
  }

  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
  {
    ostr << bf.GetBit(i);
  }

  return ostr;
}
