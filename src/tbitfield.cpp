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
        throw std::length_error("TBitField: negative length");
    BitLen = len;
    if (BitLen % (8 * sizeof(TELEM)) == 0) {
        MemLen = BitLen / (8 * sizeof(TELEM));
    }
    else {
        MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
    }
    pMem = new TELEM[MemLen]; // {0}
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}


TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    //if (pMem == nullptr)
        //выдать ошибку
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((0 <= n) && (n <= BitLen - 1)) {
        int index = n / (8 * sizeof(TELEM));
        return index;
    }
    throw std::out_of_range("Индекс выходит за пределы поля");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((0 <= n) && (n <= BitLen - 1)) {
        int j = n % (8 * sizeof(TELEM));
        return ((TELEM)1 << j);
    }
    throw std::out_of_range("Индекс выходит за пределы поля");
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((0 <= n) && (n <= BitLen - 1)) {
        TELEM mask = GetMemMask(n);
        int val = GetMemIndex(n);
        pMem[val] = pMem[val] | mask;
    }
    else throw std::out_of_range("Индекс выходит за пределы поля");
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((0 <= n) && (n <= BitLen - 1)) {
        int val = GetMemIndex(n);
        TELEM mask = ~GetMemMask(n);
        pMem[val] = pMem[val] & mask;
    }
    else throw std::out_of_range("Индекс выходит за пределы поля");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((0 <= n) && (n <= BitLen - 1)) {
        TELEM mask = GetMemMask(n);
        int val = GetMemIndex(n);
        if ((pMem[val] & mask) == 0)
            return 0;
        return 1;
    }
    throw std::out_of_range("Индекс выходит за пределы поля");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
        return *this;
    if (MemLen == bf.MemLen) {
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    else {
        TELEM* newMem = new TELEM[bf.MemLen];
        for (int i = 0; i < bf.MemLen; i++)
            newMem[i] = bf.pMem[i];
        delete[] pMem;
        pMem = newMem;
        MemLen = bf.MemLen;
    }
    BitLen = bf.BitLen;
    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen)
        return 0;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField result(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++) {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }
    for (int i = min(MemLen, bf.MemLen); i < max(MemLen, bf.MemLen); i++) {
        if (MemLen > bf.MemLen)
            result.pMem[i] = pMem[i];
        else
            result.pMem[i] = bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField result(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        result.pMem[i] = pMem[i] & bf.pMem[i];
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i];
    }
    int tail = BitLen % (8 * sizeof(TELEM));
    if (tail == 0)
        return result;
    result.pMem[result.MemLen - 1] &= (((TELEM)1 << tail) - 1);
    return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    TBitField result(bf.BitLen);
    for (int i = 0; i < bf.BitLen; i++)
    {
        char ch;
        if (!(istr >> ch)) return istr;
        if (ch != '0' && ch != '1')
        {
            istr.setstate(ios::failbit);
            return istr;
        }
        if (ch == '1') result.SetBit(i);
    }
    bf = result;
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) ostr << bf.GetBit(i);
    return ostr;
}
#include <random>
void TBitField::GenerateRandom(TBitField& bf) {
    int s = bf.BitLen;
    for (int i = 0; i < s; i++) {
        static std::mt19937 rng{ std::random_device{}() };
        static std::uniform_int_distribution<int> dist(0, 1);
        if (dist(rng)) bf.SetBit(i);
    }
}