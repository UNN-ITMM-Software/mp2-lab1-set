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
        throw - 1;
    BitLen = len;
    MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
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
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != NULL)
    {
        delete[] pMem;
        pMem = NULL;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen; ;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen)
        throw - 8;
    int i = GetMemIndex(n);
    pMem[i] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen)
        throw - 1;
    int i = GetMemIndex(n);
    pMem[i] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen)
        throw 8;
    int i = GetMemIndex(n);
    if ((pMem[i] & GetMemMask(n)) != 0)
    {
        return 1;
    }
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
        return *this;
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen)
    {
        MemLen = bf.MemLen;
        delete[] pMem;
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
    if (this == &bf)
        return 1;
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (*this == bf)
        return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (MemLen > bf.MemLen)
    {
        TBitField result(*this);
        for (int i = 0; i < bf.MemLen; i++)
            result.pMem[i] = pMem[i] | bf.pMem[i];
        return result;
    }
    else
    {
        TBitField result(bf);
        for (int i = 0; i < MemLen; i++)
            result.pMem[i] = pMem[i] | bf.pMem[i];
        return result;
    }
}


TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (BitLen > bf.BitLen)
    {
        TBitField result(BitLen);
        for (int i = 0; i < bf.BitLen; i++)
            if (GetBit(i) & bf.GetBit(i))
                result.SetBit(i);
        return result;
    }
    else
    {
        TBitField result(bf.BitLen);
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) & bf.GetBit(i))
                result.SetBit(i);
        return result;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField bf(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        bf.pMem[i] = ~pMem[i];
    }
    return bf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char c;
    int k = 0;
    do
    {
        istr >> c;
        if (c == '1')
        {
            bf.SetBit(k);
        }
        if (c == '0')
        {
            bf.ClrBit(k);
        }
        k++;
    } while ((c == '1') || (c == '0'));
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}