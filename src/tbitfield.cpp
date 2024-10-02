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

TBitField::TBitField(int len): BitLen(len)
{
    if (len < 0)
        throw exception("TBitField::TBitField: Cannot create BitField with negative length");

    MemLen = (len > TELEMBits * (len / TELEMBits)) ? (len / TELEMBits) + 1 : (len / TELEMBits);
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf): BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
    pMem = new TELEM[MemLen];
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen)
        throw out_of_range("TBitField::GetMemIndex:  n (bit position) is out of range");

    return n / (TELEMBits - 1);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
        throw out_of_range("TBitField::GetMemMask: n (bit position) is out of range");

    return 1 << (n & (TELEMBits - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > BitLen)
        throw out_of_range("TBitField::SetBit: n (bit position) is out of range");

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > BitLen)
        throw out_of_range("TBitField::ClrBit: n (bit position) is out of range");

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n > BitLen)
        throw out_of_range("TBitField::GetBit: n (bit position) is out of range");

  return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete[] pMem;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return false;

    bool NotEqual = false;

    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
        {
            NotEqual = true;
            break;
        }
    
    return !NotEqual;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return true;

    bool NotEqual = false;

    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
        {
            NotEqual = true;
            break;
        }

    return NotEqual;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField Result(max(BitLen, bf.BitLen));

    if (BitLen > bf.BitLen)
        Result = *this;

    else
        Result = bf;

    //for (int i = 0; i < min(BitLen, bf.BitLen); i++)
    //    if (GetBit(i) || bf.GetBit(i))
    //        Result.SetBit(i);

    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Result.pMem[i] = pMem[i] | bf.pMem[i];

    return Result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField Result(max(BitLen, bf.BitLen));

    //for (int i = 0; i < min(BitLen, bf.BitLen); i++)
    //    if (GetBit(i) && bf.GetBit(i))
    //        Result.SetBit(i);

    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Result.pMem[i] = pMem[i] & bf.pMem[i];

    return Result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField Result(BitLen);

    for (int i = 0; i < BitLen; i++)
        if (!GetBit(i))
            Result.SetBit(i);

    
    //for (int i = 0; i < MemLen; i++)
    //    Result.pMem[i] = ~pMem[i];

    //for (int i = MemLen * TELEMBits - 1; i >= BitLen; i--)
    //     Result.pMem[i / (TELEMBits - 1)] &= ~(1 << (i & (TELEMBits - 1)));
    

    return Result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string State;
    for (int i = 0; i < bf.BitLen; i++)
        State += bf.GetBit(i);

    istr >> State;
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    string State;
    for (int i = 0; i < bf.BitLen; i++)
        State += bf.GetBit(i);

    ostr << State;
    return ostr;
}
