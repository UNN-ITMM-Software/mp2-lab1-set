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
  {
    throw "init error";
  }
  else 
  {
    BitLen = sizeof(int) * 8 * len;
    MemLen = len;
    pMem = new TELEM(MemLen);
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
  pMem = new TELEM(MemLen);
  for (int i = 0; i < MemLen; i++) 
  {
  pMem[i] = bf.pMem[i];
  } 
}

TBitField::~TBitField()
{
  if (pMem != nullptr)
  {
     delete [] pMem;
     BitLen = 0;
     MemLen = 0;
     pMem = nullptr;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n >= 0) && (n < BitLen))
  {
    return n >> 5;
  }
  else
  {
    throw "error";
  }
  return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n >= 0) && (n < BitLen))
  {
    return 1 << (n & 31);
  }
  else
  {
    throw "error";
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
  if ((n >= 0) && (n < BitLen))
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
  if ((n >= 0) && (n < BitLen))
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
  }
  else
  {
    throw "Error index";
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n >= 0) && (n < BitLen))
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    return (pMem[i] & m) == 0 ? 0 : 1;
  }
  else 
  {
    throw "Error GetBit";
  } 
  return FAKE_INT;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (bf.pMem == pMem)
  {
  return *this;
  }
  else
  {
    delete [] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i< MemLen; i++)
    {
      pMem[i]=bf.pMem[i];
    }
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (MemLen != bf.MemLen)
  {
    return false;
  }
  else
  {
    for (int i = 0; i<MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
	return false;
      }
    }
    return true;
  }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (MemLen != bf.MemLen)
  {
    return true;
  }
  else
  {
    for (int i = 0; i<MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        return true;
      }
    }
    return false;
  }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  if (MemLen == bf.MemLen)
  {
    for (int i = 0; i<MemLen; i++)
    {
      pMem[i] = pMem[i] | bf.pMem[i];
    }
  }
  else
  {
    throw "Error lenght"
  }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if (MemLen == bf.MemLen)
  {
    for (int i = 0; i<MemLen; i++)
    {
      pMem[i] = pMem[i] & bf.pMem[i];
    }
   else
   {
     throw "Eror lenght"
   }
}

TBitField TBitField::operator~(void) // отрицание
{
  for (int i = 0; i<MemLen; i++)
  {
    pMem[i] = ~pMem[i]; 
  }
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  return ostr<<bf.Mem;
}
