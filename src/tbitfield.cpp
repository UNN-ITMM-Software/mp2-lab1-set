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
        throw  logic_error("ERROR");
    }
    BitLen = len;
    MemLen = (len / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{

    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
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
    if (pMem != NULL)
    {
        delete[]pMem;
        pMem = NULL;
        MemLen = NULL;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int index = (n % (sizeof(TELEM) * 8));
    TELEM mask = 1;
    mask = mask << index;
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= (*this).BitLen))
    {
        throw logic_error("ERORR");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
    {
        throw logic_error("ERORR");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || (n >= BitLen))
    {
        throw logic_error("ERORR");
    }
    return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
    {
        return *this;
    }

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (bf.MemLen != MemLen)
    {
        MemLen = bf.MemLen;
        delete pMem;
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
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] != bf.pMem[i])
            {
                return 0;
                break;
            }
        }
    }
    return 1;
}


int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen == bf.BitLen)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
        {
            if (pMem[i] == bf.pMem[i])
            {
                return 1;
                break;
            }
        }
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (bf.BitLen > BitLen)
    {
        BitLen = bf.BitLen;
    }

    TBitField temp(BitLen);

    for (int i = 0; i < MemLen; i++)
    {
        temp.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++)
    {
        temp.pMem[i] |= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (bf.BitLen > BitLen)
    {
        BitLen = bf.BitLen;
    }

    TBitField temp(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        temp.pMem[i] = pMem[i];
    }

    for (int i = 0; i < bf.MemLen; i++)
    {
        temp.pMem[i] &= bf.pMem[i];
    }

    if (bf.BitLen < BitLen)
    {
        for (int i = bf.BitLen; i < MemLen; i++)
        {
            temp.pMem[i] = 0;
        }
    }
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(*this);

    for (int i = 0; i < temp.BitLen; i++)
    {
        if (temp.GetBit(i))
        {
            temp.ClrBit(i);
        }
        else
        {
            temp.SetBit(i);
        }
    }
    return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    int temp;
    istr >> temp;
    TBitField s(temp);
    for (int i = 0; i < temp; i++)
    {
        istr >> temp;
        if (temp == 1)
        {
            s.SetBit(i);
        }
    }
    bf = move(s);
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    ostr << bf.GetLength() << endl;
    for (int i = 0; i < bf.MemLen; i++)
    {
        ostr << sizeof(TELEM) * 8;
    }
    return ostr;
}


