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
    {
        throw("Out_Of_Range");
    }
    BitLen = len;
    if (len % (sizeof(TELEM)* 8) == 0)
    {
        MemLen = len / (sizeof(TELEM) * 8);
    }
    else
    {
        MemLen = (len / (sizeof(TELEM) * 8)) + 1;
    }
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
    delete[] pMem;
}

void TBitField::CheckRange(const int& v) const
{
    if (v > BitLen || v <= 0)
    {
        throw("OUT_OF_RANGE");
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    CheckRange(n);
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    CheckRange(n);
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    CheckRange(n);
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    CheckRange(n);
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    CheckRange(n);
    return(pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (bf == NULL)
    {
        throw("NULL_REFERENCE_EXEPTION");
    }
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        delete[] pMem;
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
    if (BitLen == bf.BitLen)
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem [i] != bf.pMem[i])
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return ((*this == bf) ^ 1);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int btLen = BitLen;
    if (bf.BitLen > btLen)
    {
        btLen = bf.BitLen;
    }
    TBitField tmp(btLen);
    for (int i = 0; i < bf.MemLen; i++)
    {
        tmp.pMem[i] = bf.pMem[i] | pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int btLen = BitLen;
    if (btLen < bf.BitLen)
    {
        btLen = bf.BitLen;
    }
    TBitField tmp(btLen);
    for (int i = 0; i < bf.MemLen; i++)
    {
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i))
        {
            tmp.ClrBit(i);
        }
        else
        {
            tmp.SetBit(i);
        }
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char sign;
    int i = 1;
    istr >> sign;
    while (((sign == '0') || (sign == '1')) && (i < (bf.BitLen - 1)))
    {
        if (sign == '0')
        {
            bf.ClrBit(i);
        }
        else
        {
            bf.SetBit(i);
        }
        istr >> sign;
        i++;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
        {
            ostr << 1;
        }
        else
        {
            ostr << 0;
        }
        if (((i+1)%(8*sizeof(TELEM))) == 0)
        {
            ostr << ' ';
        }
        ostr << endl;
        return ostr;
    }
}

