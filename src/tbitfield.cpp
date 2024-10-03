
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  if (len > 0)
  {
    memLen = (len + 31) >> sizeof(TELEM);
    pMem = new TELEM[memLen];
    bitLen = len;
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = 0;
    }
  }
  else
    throw "error";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  if (bf.bitLen >= 0)
  {
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    bitLen = bf.bitLen;
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
  else
    throw "error";

}

TBitField::~TBitField()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = 0;
  }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > itLen))
  {
    throw "error";
  }
  else
    return n>>5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 && n < bitLen) 
    throw "error";
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n<0) || (n>bitLen))
    throw out_of_range("Error");
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] | m;
  }
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n<0) || (n>bitLen))
    throw out_of_range("Error");
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n<0) || (n>bitLen))
    throw out_of_range("Error");
  else
  {
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    return (pMem[i] & m);
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
    return *this;
  else
  {
    delete[] pMem;
    memLen = bf.memLen;
    bitLen = bf.bitLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
    return *this;
  }

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (memLen != bf.memLen || bitLen != bf.bitLen)
    return 0;
  else
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
        return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  const int length = max(bitLen, bf.bitLen);
  TBitField res(length);
  int i = 0;
  for (i; i < memLen; i++)
    res.pMem[i] = pMem[i];
  for (i=0; i < bf.memLen; i++)
    res.pMem[i] = res.pMem[i] | bf.pMem[i];
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  const int length = max(bitLen, bf.bitLen);
  TBitField res(length);
  int i = 0;
  for (i; i < memLen; i++)
    res.pMem[i] = pMem[i];
  for (i = 0; i < bf.memLen; i++)
    res.pMem[i] = res.pMem[i] & bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);
  for (int i = 0; i < res.bitLen; i++)
  {
    if (res.GetBit(i))
      res.ClrBit(i);
    else
      res.SetBit(i);
  }
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int length;
  istr >> length;
  TBitField res(length);
  char* mas=new char[length];
  istr >> mas;
  for (int i = 0; i < bf.bitLen; i++)
    if (mas[i] == 0)
      bf.ClrBit(i);
    else if (mas[i] == 1)
      bf.SetBit(i);
    else throw "Special Symvol";
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
