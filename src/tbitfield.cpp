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
        throw "Invalid len parameter";
    MemLen = int(ceil(len / (sizeof(TELEM) * 8.0)));
    pMem = new TELEM[MemLen];
    BitLen = len;
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.GetLength();
    MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
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
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM tmp = 1 << n;
    return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    throw invalid_argument("Не могу установить отрицательный бит");
    if (n >= BitLen)
        throw invalid_argument("Невозможно установить бит больше максимального размера битового поля");
    pMem[GetMemIndex(n)] |= GetMemMask(n % 32);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0)
        throw invalid_argument("Не могу очистить отрицательный бит");
    if (n >= BitLen)
        throw invalid_argument("Не удается очистить бит, превышающий максимальный размер битового поля");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n % 32);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0)
        throw invalid_argument("Не могу получить отрицательный бит");
    if (n >= BitLen)
        throw invalid_argument("Не может быть немного больше максимального размера битового поля");
    if ((pMem[GetMemIndex(n)] & GetMemMask(n % 32)) > 0)
        return 1;
    else
        return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    BitLen = bf.GetLength();
    MemLen = BitLen / 32 + ((BitLen % 32 == 0) ? 0 : 1);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.GetLength())
        return 0;
    for (int i = 0; i < MemLen; ++i)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.GetLength())
        return 1;
    for (int i = 0; i < MemLen; ++i)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (BitLen >= bf.GetLength())
    {
        TBitField tmp(*this);
        for (int i = 0; i < bf.GetLength(); i++)
            tmp.pMem[i] |= bf.pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(bf);
        for (int i = 0; i < BitLen; i++)
            tmp.pMem[i] |= pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField tmp(BitLen);
    for (int i = 0; i < MemLen; ++i)
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0; i < BitLen; ++i)
    {
        if (!GetBit(i))
            tmp.SetBit(i);
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField& bf) // ввод
{
    char* s;
    istr >> s;
    int len = sizeof(s) / sizeof(char) - 1;
    TBitField tmp(len);
    for (int i = 0; i < len; ++i)
    {
        if (s[i] == '1')
            tmp.SetBit(i);
        else
            tmp.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++)
        ostr << bf.GetBit(i);
    return ostr;
}
