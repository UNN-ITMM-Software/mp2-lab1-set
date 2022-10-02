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
  if (len > -1)
  {
	BitLen = len;
	MemLen = (len + 31) >> sizeof(TELEM);
	pMem = new TELEM[MemLen];
	if (pMem != NULL) {
	  for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
	}
  }
  else
  {
	throw("Error");
  }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  if (bf.BitLen <= 0)
	throw "Error";
  else
  {
	BitLen = bf.BitLen;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
	{
	  pMem[i] = bf.pMem[i];
	}
	MemLen = bf.MemLen;
  }
}

TBitField::~TBitField()
{
  if (pMem != 0) delete[] pMem;
  pMem = 0;
  MemLen = 0;
  BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > BitLen)) throw "Error";
  else
	return n >> 5; // return pMem[n/32];
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 && n < BitLen) throw "Error";
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n > BitLen))
  {
	throw "Error";
  }
  else
  {
	int i = GetMemIndex(n);
	int m = GetMemMask(n);
	pMem[i] = pMem[i] | m;
  }
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n > BitLen))
  {
	throw "Error";
  }
  else
  {
	int i = GetMemIndex(n);
	int m = GetMemMask(n);
	pMem[i] = pMem[i] & ~m;
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n > BitLen))
  {
	throw "Error";
  }
  else
  {
	int i = GetMemIndex(n);
	int m = GetMemMask(n);
	return (pMem[i] & m);
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  {
	if (this == &bf)
	  return *this;
	else
	{
	  delete[] pMem;
	  MemLen = bf.MemLen;
	  pMem = new TELEM[MemLen];
	  BitLen = bf.BitLen;
	  for (int i = 0; i < MemLen; i++)
	  {
		pMem[i] = bf.pMem[i];
	  }
	  return *this;
	}
  }
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (MemLen != bf.MemLen || BitLen != bf.BitLen) return 0;
  else
  {
	for (int i = 0; i < MemLen; i++)
	{
	  if (pMem[i] != bf.pMem[i])
		return 0;
	}
	return 1;
  }
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int len = BitLen;
  if (bf.BitLen > len)
	len = bf.BitLen;
  TBitField tmp(len);
  for (int i = 0; i < MemLen; i++)
	tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
	tmp.pMem[i] |= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int len = BitLen;
  if (bf.BitLen > len)
	len = bf.BitLen;
  TBitField tmp = (len);
  for (int i = 0; i < MemLen; i++)
	tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
	tmp.pMem[i] &= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
   {
    TBitField tmp(*this);
    for (int i = 0; i < tmp.BitLen; i++)
    {
      if (tmp.GetBit(i))
        tmp.ClrBit(i);
      else
        tmp.SetBit(i);
    }
    return tmp;
  }
}

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char* s;
    istr >> s;
    int len = sizeof(s) / sizeof(char) - 1;
    TBitField tmp(len);
    for (int i = 0; i < len; ++i)
    {
        if (s[i] == '1')
            tmp.SetBit(i);
        else
            tmp.ClrBit(i);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++)
        ostr << bf.GetBit(i);
    return ostr;
}
