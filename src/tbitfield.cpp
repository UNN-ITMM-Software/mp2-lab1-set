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
    if (len < 0) {
        throw "negative";
    }
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования 
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n 
{
    if (n < 0 || n > BitLen)
        throw "eror";
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{
    if (n < 0 || n > BitLen)
        throw "eror";
    return 1 << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит 
{
    if (n < 0 || n > BitLen)
        throw ("eror");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит 
{
    if (n < 0 || n > BitLen)
        throw "eror";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита 
{
    if (n < 0 || n > BitLen)
        throw "eror";
    return  pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание 
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение 
{
   if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen))
       return 0;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
   return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение 
{
    if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen))
        return 1;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return 1;
    }
   return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или" 
{
    int max1 = max(BitLen, bf.BitLen);
    TBitField tmp(max1);
    int max2 = max(MemLen, bf.MemLen);
    for (int i = 0; i < max2; i++) {
            tmp.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int max1 = max(BitLen, bf.BitLen);
    TBitField tmp(max1);
    int max2 = max(MemLen, bf.MemLen);
    for (int i = 0; i < max2; i++) {
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание 
{
    TBitField tmp(BitLen);
    int i = 0;
    for (i = 0; i < MemLen; i++)
        tmp.pMem[i] = ~pMem[i];
    int k = BitLen & ((1 << 5) - 1);
        tmp.pMem[i - 1] = tmp.pMem[i - 1] & ((1 << k) - 1);
    return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод 
{
    istr >> bf.BitLen;
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    ostr << bf.BitLen;
    ostr << bf.MemLen;
    for (int i = 0; i < bf.BitLen; i++) {
        cout << bf.GetBit(i) << " ";
    }
    return ostr;
}
