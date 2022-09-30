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

TBitField::TBitField(int len) //конструктор инициализации
{
    if (len > 0)
    {
        BitLen = len;
        MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = 0;
        }
    }
    else
    {
        throw '!';
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    if (bf.pMem == 0)
    {
        BitLen = 0;
        pMem = 0;
        MemLen = 0;
    }
    else
    {
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

TBitField::~TBitField()
{
    if (pMem != 0)
    {
        delete[] pMem;
        BitLen = 0;
        pMem = 0;
        MemLen = 0;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= 0)
    {
        return n >> (int)(log2(8 * sizeof(TELEM)));
    }
    else
    {
        throw '!';
    }
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n >= 0)
    {
        return 1 << (n & (sizeof(TELEM) * 8 - 1));
    }
    else
    {
        throw '!';
    }
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
    }
    else
    {
        throw '!';
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
    }
    else
    {
        throw '!';
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= 0 && n < BitLen)
    {
        return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
    }
    else
    {
        throw '!';
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
    {
        return *this;
    }
    if (pMem != 0)
    {
        delete[] pMem;
    }
    if (bf.pMem == 0)
    {
        BitLen = 0;
        pMem = 0;
        MemLen = 0;
    }
    else
    {
        BitLen = bf.BitLen;
        MemLen = (bf.BitLen - 1) / (sizeof(TELEM) * 8) + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return false;
    }
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) != bf.GetBit(i))
        {
            return false;
        }
    }
    return true;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return true;
    }
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) != bf.GetBit(i))
        {
            return true;
        }
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField res(std::max(BitLen, bf.BitLen));
    for (int i = 0; i < std::min(BitLen, bf.BitLen); i++)
    {
        if ((GetBit(i) == 1) || (bf.GetBit(i) == 1))
        {
            res.SetBit(i);
        }
    }
    for (int i = std::min(BitLen, bf.BitLen); i < std::max(BitLen, bf.BitLen); i++)
    {
        if (BitLen > bf.BitLen)
        {
            if (GetBit(i) == 1)
            {
                res.SetBit(i);
            }
        }
        else
        {
            if (bf.GetBit(i) == 1)
            {
                res.SetBit(i);
            }
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField res(std::max(BitLen, bf.BitLen));
    for (int i = 0; i < std::min(BitLen, bf.BitLen); i++)
    {
        if ((GetBit(i) == 1) && (bf.GetBit(i) == 1))
        {
            res.SetBit(i);
        }
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 1)
        {
            res.ClrBit(i);
        }
        else
        {
            res.SetBit(i);
        }
    }
    return res;
}

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    /*char str[1000] = {'2'};
    int i = 0;
    istr >> str;
    while (str[i] != '2')
    {
      i = i + 1;
    }
    bf.BitLen = i;
    bf.MemLen = (i - 1) / (sizeof(TELEM) * 8) + 1;
    delete[] bf.pMem;
    bf.pMem = new TELEM[bf.MemLen];
    std::cout << str << ' ' << bf.BitLen << ' ' << bf.MemLen << '/n';
    for (i = 0; i < bf.BitLen; i++)
    {
      b.str[i] = s[i];
    }
    b.str[b.len] = 0;
    return istr;*/
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    if (bf.pMem == 0)
    {
        ostr << "";
        return ostr;
    }
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i) == 1)
        {
            ostr << "1";
        }
        else
        {
            ostr << "0";
        }
    }
    return ostr;
}
