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
static const unsigned int TELEM_BIT_SIZE = (8*sizeof(TELEM));

TBitField::TBitField(int len)
{
  if(len < 0) 
    throw "Can not create bitfield";

  this->MemLen = len;
  this->BitLen = TELEM_BIT_SIZE*len;

  this->pMem = new TELEM[len];
  for(int i = 0; i < len; i++) 
  {
    this->pMem[i] = 0;
  }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{ 
  this->BitLen = bf.GetLength();
  this->MemLen = this->BitLen/(TELEM_BIT_SIZE);

  this->pMem = new TELEM[this->MemLen];
  for(int i = 0; i < this->MemLen; i++)
  {
    this->pMem[i] = bf.pMem[i]; 
  }
  
}

TBitField::~TBitField()
{
  delete [] this->pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if(n > this->GetLength())
    throw "Can not get mem indx";
  int indx = n >> 5;
  return indx;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if(n < 0 || n >= this->GetLength())
    throw "Can not get bitmask";
  TELEM bitMask = 0;
  bitMask = 1 << (n & (TELEM_BIT_SIZE) - 1);
  return bitMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if(n < 0 || n >= this->GetLength())
    throw "Can not set this bit";

  int indx = this->GetMemIndex(n);
  TELEM mask = this->GetMemMask(n);
  this->pMem[indx] = this->pMem[indx] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if(n < 0 || n >= this->GetLength())
    throw "Can not clear this bit";

  int indx = this->GetMemIndex(n);
  TELEM mask = ~(this->GetMemMask(n));
  this->pMem[indx] = this->pMem[indx] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if(n < 0 || n >= this->GetLength())
    throw "Can not get this bit";
  
  int indx = this->GetMemIndex(n);
  TELEM mask = this->GetMemMask(n);

  TELEM bit = this->pMem[indx] & mask;
  if(bit == 0) 
  {
    return 0;
  } 
  else 
  {
    return 1;
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if(this == &bf) 
    throw "Selfcopying";
  
  this->BitLen = bf.GetLength();
  this->MemLen = this->BitLen / TELEM_BIT_SIZE;

  delete [] this->pMem;
  this->pMem = new TELEM[this->MemLen];
  for(int i = 0; i < this->MemLen; i++)
  {
    this->pMem[i] = bf.pMem[i];
  }

  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if(this->GetLength() != bf.GetLength())
    return 0;

  for(int i = 0; i < this->MemLen; i++)
  {
    if(this->pMem[i] != bf.pMem[i])
      return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if(*this == bf) 
    return 0;
  else  
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  if(this->GetLength() != bf.GetLength())
    throw "Op ERROR: not equal lenght";

  TBitField temp = *this;
  for(int i = 0; i < this->GetLength(); i++) 
  {
    temp.pMem[i] = temp.pMem[i] | bf.pMem[i];
  }
  return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if(this->GetLength() != bf.GetLength())
    throw "Op ERROR: not equal lenght";

  TBitField temp = *this;
  for(int i = 0; i < this->GetLength(); i++) 
  {
    temp.pMem[i] = temp.pMem[i] & bf.pMem[i];
  }
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField temp = *this;
  for(int i = 0; i < this->GetLength(); i++) 
  {
    temp.pMem[i] = ~temp.pMem[i];
  }
  return temp;
}

TELEM& TBitField::operator[](const int &indx)
{
  if(indx < 0 || indx >= this->MemLen)
    throw "Op ERROR: run out of bitfield";

  return this->pMem[indx];
}

TELEM TBitField::GetMemElem(const int n) const 
{
  if(n < 0 || n >= this->MemLen) 
    throw "Can not get mem element";

  return this->pMem[n];
}

int TBitField::GetMemLen() const 
{
  return MemLen;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int temp;
 for(int i = 0; i < bf.GetLength(); i++) 
  {
    istr >> temp;
    if(temp == 1)
      bf.SetBit(i);
    else if(temp == 0)
      bf.ClrBit(i);
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for(int i = 0; i < bf.GetLength() / TELEM_BIT_SIZE; i++) 
  {
    TELEM temp = bf.pMem[i];
    for(int j = 0; j < TELEM_BIT_SIZE; j++)
    {
      ostr << (temp & 1);
      temp >>= 1;
    }
    ostr << ' ';
  }
    
  return ostr;
}
