// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) throw -1;
    BitLen = len;
    MemLen = (len + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
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
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen)) throw "Invalid the number";
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen)) throw "Invalid the number";
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&*this == &bf) return *this;
    if (BitLen != bf.BitLen)
    {
        if (MemLen != bf.MemLen)
        {
            delete[]pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        BitLen = bf.BitLen;
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen > bf.BitLen)
    {
        for (int i = 0; i < bf.MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        for (int i = bf.MemLen; i < MemLen; i++)
            if (pMem[i] != 0)
                return 0;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        for (int i = MemLen; i < bf.MemLen; i++)
            if (bf.pMem[i] != 0)
                return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen > bf.BitLen)
    {
        TBitField tempBF(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tempBF.pMem[i] |= bf.pMem[i];
        return tempBF;
    }
    else
    {
        TBitField tempBF(bf);
        for (int i = 0; i < MemLen; i++)
            tempBF.pMem[i] |= pMem[i];
        return tempBF;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen < bf.BitLen)
    {
        TBitField tempBF(bf);
        for (int i = 0; i < MemLen; i++)
            tempBF.pMem[i] &= pMem[i];
        return tempBF;
    }
    else
    {
        TBitField tempBF(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tempBF.pMem[i] &= bf.pMem[i];
        return tempBF;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    int temp = BitLen / (sizeof(TELEM) * 8);
    for (int i = 0; i < temp; i++)
        pMem[i] = ~pMem[i];
    TELEM tempByte = 0;
    pMem[temp] = ~pMem[temp];
    for (int i = 0; i < BitLen % (sizeof(TELEM) * 8); i++)
        tempByte |= pMem[temp] & GetMemMask(i);
    pMem[temp] = tempByte;
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int number;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> number;
        if (number == 1)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for(int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i) << ' ';
    return ostr;
}