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
        throw invalid_argument;
   }
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
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
    pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{    
    return n / (sizeof(TELEM) * 8);
    
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    size_t telem_index = floor(n / sizeof(TELEM) * 8);
    return 1 << (n % sizeof(TELEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0)
    {
        throw std::out_of_range;
    }
    pMem[GetMemIndex(n)] = GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw std::out_of_range;
    }
    pMem[GetMemIndex(n)] &= GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
    {
        throw std::out_of_range;
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

int TBitField::operator==(const TBitField &bf) const // сравнение
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

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int MaxLen = std::max(BitLen, bf.BitLen);
    TBitField result(MaxLen);

    for (int i= 0; i < MemLen; i++)
    {
        result.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++)
    {
        result.pMem[i] |= bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MaxLen = std::max(BitLen, bf.BitLen);
    TBitField result(MaxLen);

    for (int i = 0; i < result.MemLen; i++)
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = ~pMem[i];
    }
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        int bit;
        istr >> bit;
        if (bit == 1)
        {
            bf.SetBit(i);
        }
        else
        {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
