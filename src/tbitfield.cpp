// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    MemLen = sizeof(int) * 8;
    pMem = new TELEM[(len + MemLen - 1) / MemLen];
    if (pMem != NULL)
        for (int i = 0;i < MemLen;i++)
            pMem[i] = 0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen;i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    MemLen = -1;
    delete pMem;
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / MemLen;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return n % MemLen;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    (*pMem) |= 1 << n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    (*pMem) &= ~(1 << n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
     return (*pMem & (1 << n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen;i++)
        pMem[i] = bf.pMem[i];
    return *this;


}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0;i < MemLen;i++)
        if(pMem[i]!= bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    for (int i = 0;i < MemLen;i++)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;

}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len;
    if (BitLen > bf.BitLen)
        len = BitLen;
    else len = bf.BitLen;
    TBitField tmp(len);
    for (int i = 0;i < MemLen;i++)
        tmp.pMem[i] = pMem[i];
    for (int i = 0;i < bf.MemLen;i++)
        tmp.pMem[i] |=bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len;
    if (BitLen > bf.BitLen)
        len = BitLen;
    else len = bf.BitLen;
    TBitField tmp(len);
    for (int i = 0;i < MemLen;i++)
        tmp.pMem[i] = pMem[i];
    for (int i = 0;i < bf.MemLen;i++)
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;

}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0;i < MemLen;i++)
        tmp.pMem[i] = ~pMem[i];
    return tmp;

}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char c;
    int i = 0;

    while (c != ' ' && (c == '0' || c == '1')) {
        istr >> c;
        if (c == '0')
            bf.ClrBit(i);
        else bf.SetBit(i);
        i++;
    }
    return istr;
}




ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0;i < bf.MemLen;i++)
        ostr << bf.GetBit(i);
    return ostr;

}
