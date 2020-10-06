// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0)
  {
    throw "ERROR";
  }

  BitLen = len;
  MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
  //MemLen = len / (sizeof(TELEM) * 8) + 1;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  if (pMem != NULL)
  {
    for (int i = 0; i < MemLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
}

TBitField::~TBitField()
{
  if (pMem != NULL)
  {
    delete[]pMem;
    pMem = NULL;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  int index = (n % (sizeof(int) * 8));
  TELEM mask = 1 << index;
  return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n > BitLen)
  {
    throw "ERROR";
  }
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > BitLen)
  {
    throw "ERROR";
  }
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > BitLen)
  {
    throw "ERROR";
  }
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (this == &bf) //Проверка самоприсваивания
  {
    return *this;
  }

  BitLen = bf.BitLen;

  if (MemLen != bf.MemLen)
  {
    MemLen = bf.MemLen;
    delete pMem;
    pMem = new TELEM[MemLen];
  }

  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }

  return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  int res = 1;
  if (BitLen != bf.BitLen)
  {
    res = 0;
  }
  else
  {
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        res = 0;
        break;
      }
    }
  }
  return res;
}


int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  int res = 0;
  if (BitLen == bf.BitLen)
  {
    res = 1;
  }
  else
  {
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] == bf.pMem[i])
      {
        res = 1;
        break;
      }
    }
  }
  return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int len = BitLen;
  if (bf.BitLen > len)
  {
    len = bf.BitLen;
  }

  TBitField temp(len);

  for (int i = 0; i < MemLen; i++)
  {
    temp.pMem[i] = pMem[i];
  }

  for (int i = 0; i < bf.MemLen; i++)
  {
    temp.pMem[i] |= bf.pMem[i];
  }
  return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int i, len = BitLen;
  if (bf.BitLen > len)
  {
    len = bf.BitLen;
  }

  TBitField temp(len);
  for (i = 0; i < MemLen; i++)
  {
    temp.pMem[i] = pMem[i];
  }

  for (i = 0; i < bf.MemLen; i++)
  {
    temp.pMem[i] &= bf.pMem[i];
  }

  if (bf.BitLen < len)
  {
    for (int i = bf.BitLen; i < MemLen; i++)
    {
      temp.pMem[i] = 0;
    }
  }
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField tmp(*this);

  for (int i = 0; i < tmp.BitLen; i++)
  {
    if (tmp.GetBit(i))
    {
      tmp.ClrBit(i);
    }
    else
    {
      tmp.SetBit(i);
    }
  }
  return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  int i = 0; char ch;
  do
  {
    istr >> ch;
  } while (ch != ' ');
  while (1)
  {
    istr >> ch;
    if (ch == '0')
    {
      bf.ClrBit(i++);
    }
    else if (ch == '1')
    {
      bf.SetBit(i++);
    }
    else break;
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  int len = bf.GetLength();
  for (int i = 0; i < len; i++)
  {
    if (bf.GetBit(i))
    {
      ostr << '1';
    }
    else
    {
      ostr << '0';
    }
  }
  return ostr;
}
