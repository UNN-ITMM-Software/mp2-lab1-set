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
    if (len < 0)
        throw "Negative length";

    BitLen = len;
    MemLen = (BitLen + (8 * sizeof(TELEM) - 1)) / (8 * sizeof(TELEM));  // округление вверх
    pMem = new TELEM[MemLen];
    memset(pMem, 0, MemLen * sizeof(TELEM));  // обнуляем память
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));  // копируем данные
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen)
        throw "Out of bounds";
    return n / (8 * sizeof(TELEM));  // номер элемента массива pMem
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
        throw "Out of bounds";
    return 1 << (n % (8 * sizeof(TELEM)));  // маска для бита
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int index = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[index] |= mask;  // установка бита
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int index = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[index] &= ~mask;  // очистка бита
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int index = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    return (pMem[index] & mask) ? 1 : 0;  // возвращает 1, если бит установлен
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
        memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField temp(len);

    int minLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    for (int i = 0; i < minLen; i++)
        temp.pMem[i] = pMem[i] | bf.pMem[i];

    if (MemLen > bf.MemLen)
        for (int i = minLen; i < MemLen; i++)
            temp.pMem[i] = pMem[i];
    else
        for (int i = minLen; i < bf.MemLen; i++)
            temp.pMem[i] = bf.pMem[i];

    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int maxSize = max(BitLen, bf.BitLen);
    TBitField result(maxSize);

    for (int i = 0; i < min(BitLen, bf.BitLen); i++) {
        if (GetBit(i) && bf.GetBit(i)) {
            result.SetBit(i);
        }
    }

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);

    for (int i = 0; i < BitLen; i++) {
        if (!GetBit(i)) {
            result.SetBit(i);  // Инвертируем биты
        }
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
            bf.SetBit(i);
        else
            bf.ClrBit(i);
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
