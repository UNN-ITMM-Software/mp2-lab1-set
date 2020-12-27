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
    if (len >= 0)
    {
        BitLen = len;
        // MemLen = (BitLen + 8*sizeof(TELEM) - 1) >> 5;
        MemLen = log(sizeof(TELEM) * 8 * len) / log(2);
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = 0;
        }
    }
    else
    {
        throw std::logic_error("Input error:negative len of tbitfield in constructor");
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    if (pMem != NULL)
    {
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

TBitField::~TBitField()
{
    delete pMem;
    pMem = NULL;
    BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    //return n >> 5;
    int size = sizeof(TELEM) * 8;
    int mi = (n + size - 1) / size;
    return mi;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    //return 1 << (n & 31);
    TELEM mm = pMem[GetMemIndex(n)] & (1 << n);
    return mm;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n > -1) && (n < BitLen))
    {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else
    {
        throw std::logic_error("Input error:negative index of tbitfield in setbit");
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen))
    {
        throw std::logic_error("Input error:negative index of tbitfield in clrbit");
    }
    else
    {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n > -1) && (n < BitLen))
    {
        return pMem[GetMemIndex(n)] & GetMemMask(n);
    }
    else
    {
        throw std::logic_error("Input error:negative index of tbitfield in getbit");
    }
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen)
    {
        MemLen = bf.MemLen;
        if (MemLen != NULL)
        {
            delete pMem;
            pMem = new TELEM[MemLen];
        }
    }
    if (pMem != NULL)
    {
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int res = 1;
    if (BitLen != bf.BitLen)
    {
        res = 0;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if ((pMem[i]) << (8 * sizeof(TELEM) - BitLen) != bf.pMem[i] << (8 * sizeof(TELEM) - BitLen))
            {
                res = 0;
                break;
            }
        }
    }
    return res;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    int res = 0;
    if (BitLen != bf.BitLen)
    {
        res = 1;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if ((pMem[i]) << (8 * sizeof(TELEM) - BitLen) != bf.pMem[i] << (8 * sizeof(TELEM) - BitLen))
            {
                res = 1;
                break;
            }
        }
    }
    return res;
    //return !(bf == *this);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i;
    int len = BitLen;
    if (bf.BitLen > len)
    {
        len = bf.BitLen;
    }
    TBitField temp(len);
    for (i = 0; i < MemLen; i++)
    {
        temp.pMem[i] = pMem[i];
    }
    for (i = 0; i < bf.MemLen; i++)
    {
        temp.pMem[i] |= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int i;
    int len = BitLen;
    if (bf.BitLen > len)
    {
        len = bf.BitLen;
    }
    TBitField temp(len);
    for (i = 0; i < MemLen; i++)
    {
        temp.pMem[i] = pMem[i];
    }
    for (i = 0; i < bf.MemLen; i++)
    {
        temp.pMem[i] &= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    /*
    int len = BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen; i++)
    {
        temp.pMem[i] = ~pMem[i];
    }
    return temp;
    */
    
    int i;
    int len = BitLen;
    TBitField temp(len);
    for (i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 0)
        {
            temp.SetBit(i);
        }
    }
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
    char ch;
    while (1)
    {
        istr >> ch;
        if (ch == '0')
        {
            bf.ClrBit(i++);
        }
        else if (ch == '1')
        {
            bf.SetBit(i++);
        }
        else
        {
            break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int len = bf.GetLength();
    for (int i = 0; i < len; i++)
    {
        if (bf.GetBit(i))
        {
            ostr << '1';
        }
        else
        {
            ostr << '1';
        }
    }
    return ostr;
}

