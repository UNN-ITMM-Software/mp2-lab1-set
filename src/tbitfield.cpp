// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0)
        throw "Incorrect length!";
    BitLen = len;
    if (BitLen % Bits_in_elem == 0)
        MemLen = BitLen / Bits_in_elem;
    else
        MemLen = (BitLen / Bits_in_elem) + 1;
    pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField &bf): BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= BitLen || n < 0)
        throw "Incorrect index position!";
    return n/Bits_in_elem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n >= BitLen || n < 0)
        throw "Incorrect index position!";
    return 1 << (n%Bits_in_elem);
}

// доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0)
        throw "Incorrect index position!";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0)
        throw "Incorrect index position!";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0)
        throw "Incorrect index position!";
    if((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0)
        return 1;
    return 0;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (*this != bf)
    {
        BitLen = bf.BitLen;
        if (MemLen != bf.MemLen)
        {
            MemLen = bf.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (MemLen != bf.MemLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (operator==(bf))
        return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (MemLen < bf.MemLen)
    {
        TBitField tmp(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            tmp.pMem[i] = pMem[i];
        for (int i = 0; i < tmp.MemLen; i++)
            tmp.pMem[i] |= bf.pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tmp.pMem[i] |= bf.pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (MemLen < bf.MemLen)
    {
        TBitField tmp(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            tmp.pMem[i] = pMem[i];
        for (int i = 0; i < tmp.MemLen; i++)
            tmp.pMem[i] &= bf.pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tmp.pMem[i] &= bf.pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) == 0)
            tmp.SetBit(i);
        else
            tmp.ClrBit(i);
    }
    return tmp;
}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int input;
    for (int i = 0; i < bf.BitLen; i++) 
    {
        istr >> input;
        if (input == 1)
            bf.SetBit(i);
        else if (input == 0)
            bf.ClrBit(i);
        else
            i--;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    cout << "[";
    for (int i = 0; i < bf.BitLen; i++)
        cout << bf.GetBit(i);
    cout << "]";
    return ostr;
}
