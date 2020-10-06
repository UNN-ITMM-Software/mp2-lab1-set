
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len)
{
    if (len > 0)
    {
        BitLen = len;
        MemLen = ceil((double)BitLen / 8 * sizeof(TELEM));
        pMem = nullptr;
        pMem = new TELEM[MemLen];
        if (pMem != nullptr)
            for (int i = 0; i < MemLen; i++)
                pMem[i] = 0;
        else
            throw - 1;
    }
    else
        throw - 1;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = nullptr;
    pMem = new TELEM[MemLen];
    if (pMem != nullptr)
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    else
        throw - 1;
}

TBitField::~TBitField()
{
    if (pMem != nullptr)
    {
        delete[] pMem;
        pMem = nullptr;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= 0 && n < BitLen)
        return n / (8 * sizeof(TELEM));
    else
        throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n >= 0 && n < BitLen)
    {
        int tempBN = n % (8 * sizeof(TELEM));
        TELEM mask = 1 << tempBN;
        return mask;
    }
    else
        throw - 1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину 
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else
        throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= 0 && n < BitLen)
    {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
    else
        throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= 0 && n < BitLen)
    {
        TELEM elem = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        return ((bool)(pMem[elem] & mask));
    }
    else
        throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this == &bf)
        return 1;
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return true;
    }
    for (int i = 0; i < MemLen - 1; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return true;
    }
    for (int i = (MemLen - 1) * 32; i < BitLen; i++)
    {
        if (GetBit(i) != bf.GetBit(i))
            return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int templen = BitLen;
    if (bf.BitLen > templen)
        templen = bf.BitLen;
    TBitField temp(templen);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        temp.pMem[i] |= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int templen = BitLen;
    if (bf.BitLen > templen)
        templen = bf.BitLen;
    TBitField temp(templen);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        temp.pMem[i] &= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    int templen = BitLen;
    TBitField temp(templen);
    for (int i = 0; i < templen; i++)
        if (this->GetBit(i) == 0)
            temp.SetBit(i);
        else
            temp.ClrBit(i);
    return temp;
}

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char ch;
    int i = 0;
    do { istr >> ch; } while (ch != ' ');
    while (true)
    {
        istr >> ch;
        if (ch == '0')
            bf.ClrBit(i++);
        else if (ch == '1')
            bf.SetBit(i++);
        else
            break;
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    int templen = bf.GetLength();
    for (int i = 0; i < templen; i++)
        if (bf.GetBit(i))
            ostr << '1';
        else
            ostr << '0';
    return ostr;
}