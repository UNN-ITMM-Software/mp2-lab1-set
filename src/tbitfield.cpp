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
        throw ("wrong lenght");
    BitLen = len;
    if (len % 32 == 0)
    {
        MemLen = len / (sizeof(TELEM) * 8);
    }
    else
    {
        MemLen = len / (sizeof(TELEM) * 8) + 1;
    }  
    pMem = new TELEM [MemLen] {0};
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM [MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    BitLen = 0;
    MemLen = 0;
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > BitLen))
        throw ("Error input");
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
   if ((n < 0) || (n > BitLen))
        throw ("Error input");
    const int j = n % (sizeof(TELEM) * 8);
    const TELEM mask = (1 << j);
    return mask;
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
       throw ("Error input");
    }
    const int i = GetMemIndex(n);
    const int p = GetMemMask(n);
    pMem[i] = (pMem[i] | p);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen))
    {
        throw ("Error input");
    }
    const int i = GetMemIndex(n);
    const int p = GetMemMask(n);
    pMem[i] = (pMem[i] & (~p));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen))
    {
       throw ("Error input");
    }

    const int i = GetMemIndex(n);
    const int p = GetMemMask(n);
    return (pMem[i] & p);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM [MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{

    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    //if (BitLen == bf.BitLen)
    //    return 0;
    //for (int i = 0; i < MemLen; i++)
    //    if (pMem[i] == bf.pMem[i])
    //        return 0;
    //if (BitLen == bf.BitLen)
    //    return 0;
    //return 1;
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField a(len);

    for (int i = 0; i < a.MemLen; i++)
        a.pMem[i] = pMem[i];
    for (int j = 0; j < bf.MemLen; j++)
        a.pMem[j] |= bf.pMem[j];
    return a;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField a(len);

    for (int i = 0; i < a.MemLen; i++)
        a.pMem[i] = pMem[i];
    for (int j = 0; j < bf.MemLen; j++)
        a.pMem[j] &= bf.pMem[j];
    return a;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField a(BitLen);
    TELEM tmp = sizeof(TELEM) * 8;

    for (int i = 0; i < MemLen; i++)
    {
        a.pMem[i] = ~pMem[i];
        if (i == MemLen - 1)
        {
            for (int j = BitLen % tmp; j < tmp; j++)
            {
                a.pMem[i] &= ~(1 << j);
            }
        }
    }

    //for (int i = 0; i < MemLen; i++)
    //{
    //    a.pMem[i] = ~pMem[i];
    //}
    //
    //for (int i = BitLen % tmp; i < tmp; i++)
    //{
    //    a.pMem[MemLen - 1] &= ~(1 << i);
    //}
  //
  //........................
    return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char c;
    int i = 0;
    while (true)
    {
        istr >> c;
        if (c == '0')
        {
            bf.ClrBit(i); 
            i++;
        }
        else if (c == '1')
        {
            bf.SetBit(i);
            i++;
        }
        else
        {
            break;
        }
    }
    return istr;
}
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i) == 0)
        {
            ostr << '0';
        }
        else
        {
            ostr << '1';
        }
    }
    return ostr;
}
