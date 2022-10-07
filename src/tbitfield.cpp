// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <locale.h>
// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


TBitField::TBitField(int len)
{
    if (len <= 0) throw "incorrect data";
    BitLen = len;
    MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
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
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n > BitLen))
        throw "incorrect index";

    return int(n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n > BitLen))
        throw "incorrect index";
    return 1 << (n % (8 * sizeof(TELEM) - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) throw "incorrect index";
    return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        delete[]pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    else
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
                return 0;
        }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    else
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
                return 1;
        }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int a;
    if (BitLen >= bf.BitLen)
        a = BitLen;
    else a = bf.BitLen;
    TBitField temp(a);
    for (int i = 0; i < temp.MemLen; i++)
    {
        temp.pMem[i] = bf.pMem[i] | pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int a;
    if (BitLen >= bf.BitLen)
        a = BitLen;
    else a = bf.BitLen;
    TBitField temp(a);
    for (int i = 0; i < temp.MemLen; i++)
    {
        temp.pMem[i] = bf.pMem[i] & pMem[i];
    }
    return temp;
}


TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);

    for (int i = 0; i < MemLen - 1; i++)
    {
        temp.pMem[i] = ~temp.pMem[i];
    }

    int lb = BitLen - (MemLen - 1) * sizeof(TELEM) * 8;
    if (lb < sizeof(TELEM) * 8)
    {
        int mask = (1 << (lb)) - 1;
        temp.pMem[MemLen - 1] &= mask;
    }
    
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
    char temp;
    while (true) {
        istr >> temp;
        if (temp == '0')
        {
            bf.ClrBit(i);
            i++;
        }
        else if (temp == '1')
        {
            bf.SetBit(i);
            i++;
        }
        else break;
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i) == 1) ostr << '1';
        else ostr << '0';
    }
    return ostr;
}
