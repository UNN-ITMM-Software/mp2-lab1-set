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
    {
        throw "Negative len";
    }
    BitLen = len;
    MemLen = (BitLen + sizeof(int) * 8 - 1) /(sizeof(int)*8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (this == &bf)
    {
        return;
        //throw "Copy this object";
    }
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for(int i=0; i<MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr)
    {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0)
    {
        throw "Negative number of bit";
    }
    return n / (sizeof(TELEM)*8) ;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1<<(n%(sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n<0 || n> BitLen)
    {
        throw "Large or negative index";
    }
    ClrBit(n);
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n<0 || n> BitLen)
    {
        throw "Large or negative index";
    }
    int number_bit = n-(n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));
    pMem[GetMemIndex(n)] &= ~GetMemMask(number_bit);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n> BitLen)
    {
        throw "Large or negative index";
    }
    int s = pMem[GetMemIndex(n)] & (1 << n);//GetMemMask(n)
    return s;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (pMem != nullptr)
    {
        delete[] pMem;
    }
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (*this == bf)
    {
        return 0;
    }
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField bf1(0);
    if (BitLen == bf.BitLen)
    {
        bf1 = bf;
        for (int i = 0; i < bf1.MemLen; i++)
        {
            bf1.pMem[i] = pMem[i]|bf.pMem[i];
        }
    }
    else
    {
        if (bf.BitLen > BitLen)
        {
            bf1 = bf;
        }
        else
        {
            bf1 = *this;
        }
    }
    for (int i = 0; i < bf1.MemLen; i++)
    {
        bf1.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return bf1;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField bf1(0);
    if (BitLen == bf.BitLen)
    {
        bf1 = bf;
        for (int i = 0; i < bf1.MemLen; i++)
        {
            bf1.pMem[i] &= pMem[i];
        }
    }
    else
    {
        if (bf.BitLen > BitLen)
        {
            bf1 = bf;
        }
        else
        {
            bf1 = *this;
        }
    }
    for (int i = 0; i < bf1.MemLen; i++)
    {
        bf1.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return bf1;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField bf1(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        bf1.pMem[i] = ~pMem[i];
    }
    int lb = BitLen - (MemLen-1)*sizeof(TELEM)*8;
    if (lb != sizeof(TELEM) * 8) {
        int mask = (1 << (lb)) - 1; // Убираем остаток
        bf1.pMem[MemLen - 1] &= mask;
    }
    return bf1;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    istr >> bf.BitLen;
    bf.MemLen = (bf.BitLen + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
    int k = 0;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> k;
        if (k != 0)
        {
            bf.SetBit(k);
        }
    }
    return istr;
}
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    ostr << bf.BitLen << " ";
    ostr << bf.MemLen << " ";
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i) != 0)
            ostr << "1";
        else
            ostr << "0";
    }
    return ostr;
}