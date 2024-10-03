// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
//static const int FAKE_INT = -1;
//static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len >= 0)
    {
        BitLen = len;
        MemLen = BitLen / (sizeof(TELEM) * 8);
        if (BitLen % (sizeof(TELEM) * 8))
            MemLen++;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
    else
        throw "Error.";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int index;
    if (n < 0 || n > BitLen)
        throw "Error.";
    index = n / (sizeof(TELEM) * 8);
    return index;
    //return FAKE_INT;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n > BitLen)
        throw "Error.";
    TELEM mask = 1 << (n % (sizeof(TELEM) * 8));
    return mask;
    //return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int index;
    if (n < 0 || n > BitLen)
        throw "Error.";
    index = GetMemIndex(n);
    pMem[index] = pMem[index] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    TELEM mask = 1;
    int index;
    if (n < 0 || n > BitLen)
        throw "Error.";
    mask = GetMemMask(n);
    index = GetMemIndex(n);
    pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    TELEM mask = 1;
    int index = GetMemIndex(n);
    if (index < 0 || index > BitLen)
        throw "Error.";
    mask = pMem[index] & GetMemMask(n);
    if (mask > 0)
        return 1;
    else
        return 0;
    //return FAKE_INT;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
    //return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (MemLen != bf.MemLen || BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
    //return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf)
        return 0;
    else
        return 1;
    //return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int minMemLen, len, temp = 1;
    if (BitLen < bf.BitLen)
        temp = 0;
    if (temp == 1)
    {
        len = BitLen;
        minMemLen = bf.MemLen;
    }
    else
    {
        len = bf.BitLen;
        minMemLen = MemLen;
    }
    TBitField result(len);
    for (int i = 0; i < minMemLen; i++)
        result.pMem[i] = pMem[i] | bf.pMem[i];
    if (temp == 1)
        for (int i = minMemLen; i < result.MemLen; i++)
            result.pMem[i] = pMem[i];
    else
        for (int i = minMemLen; i < result.MemLen; i++)
            result.pMem[i] = bf.pMem[i];
    return result;
    //return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len;
    if (bf.BitLen > BitLen)
        len = bf.BitLen;
    else
        len = BitLen;
    TBitField result(len);
    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        result.pMem[i] &= bf.pMem[i];
    return result;
    //return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(*this);
    for (int i = 0; i < result.BitLen; i++)
    {
        if (result.GetBit(i))
            result.ClrBit(i);
        else
            result.SetBit(i);
    }
    return result;
    //return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int temp;
    cin >> temp;
    while (temp > -1)
    {
        bf.SetBit(temp);
        cin >> temp;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        cout << bf.GetBit(i);
    return ostr;
}
