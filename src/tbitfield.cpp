// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

enum EXCEPTION { outofrange };

TBitField::TBitField(int len)
{
    /*if (len <= 0)
    {
        throw outofrange;
    }*/
    int i = 0;
    BitLen = len;
    if (len % 32 == 0)
    {
        MemLen = len / 32;
    }
    else
    {
        MemLen = (len / 32) + 1;
    }
    pMem = new TELEM[MemLen];
    for (i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    int i = 0;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int res;
    res = n / 32;
    return (res);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res;
    if (n < 0 || n >= BitLen)
    {
        throw n;
    }
    res = 1 << (n % 32);
    return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int i;
    TELEM mask;
    i = GetMemIndex(n);
    mask = GetMemMask(n);
    pMem[i] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int i;
    TELEM mask;
    i = GetMemIndex(n);
    mask = GetMemMask(n);
    pMem[i] ^= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int res;
    int i;
    TELEM mask;
    i = GetMemIndex(n);
    mask = GetMemMask(n);
    res = pMem[i] & mask;
    return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    int i = 0;
    if (this != &bf)
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return (*this);
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    int i;
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    for ( i =0 ; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int i;
    if (this == &bf)
    {
        TBitField res(*this);
        return res;
    }
    int len, flag = 0;
    if (BitLen < bf.BitLen)
    {
        len = bf.BitLen;
    }
    else
    {
        flag = 1;
        len = BitLen;
    }
    TBitField res(len);
    if (flag == 0)
    {
        for (i = 0; i < MemLen; i++)
        {
            res.pMem[i] = pMem[i];
        }
        for (int i = 0; i < bf.MemLen; i++)
        {
            res.pMem[i] |= bf.pMem[i];
        }
    }
    else
    {
        for (i = 0; i < bf.MemLen; i++)
        {
            res.pMem[i] = bf.pMem[i];
        }
        for (int i = 0; i < MemLen; i++)
        {
            res.pMem[i] |= pMem[i];
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int i;
    if (this == &bf)
    {
        TBitField res(*this);
        return res;
    }
    int len, flag = 0;
    if (BitLen < bf.BitLen)
    {
        len = bf.BitLen;
    }
    else
    {
        flag = 1;
        len = BitLen;
    }
    TBitField res(len);
    if (flag == 0)
    {
        for (i = 0; i < MemLen; i++)
        {
            res.pMem[i] = pMem[i];
        }
        for (int i = 0; i < bf.MemLen; i++)
        {
            res.pMem[i] &= bf.pMem[i];
        }
    }
    else
    {
        for (i = 0; i < bf.MemLen; i++)
        {
            res.pMem[i] = bf.pMem[i];
        }
        for (int i = 0; i < MemLen; i++)
        {
            res.pMem[i] &= pMem[i];
        }
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    int i;
    for (i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 0)
        {
            SetBit(i);
        }
        else
            ClrBit(i);
    }
    return (*this);
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char x;
    int i;
    for (i = 0; i < bf.BitLen; i++)
    {
        istr >> x;
        if (x == '0')
        {
            bf.ClrBit(i);
        }
        else
        {
            if (x == '1')
            {
                bf.SetBit(i);
            }
            else
                return istr;
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    int i;
    for (i = 0; i < bf.BitLen; i++)
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
