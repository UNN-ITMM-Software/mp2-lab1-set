#include "tbitfield.h"

#include <cmath>

TBitField::TBitField(int len)
{
    if (len < 1) throw  "Wrong length";
    BitLen = len;
    MemLen = ceil((double)(len) / (sizeof(TELEM) * 8));
    pMem = nullptr;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr) throw "Memmory Error";
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0u;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = nullptr;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr) throw "Memmory Error";
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    if (pMem != nullptr)
        delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) throw "Wrong index";
    return (floor((double)(n) / (sizeof(TELEM) * 8)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen) throw "Wrong index";
    int number = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[number] = pMem[number] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen) throw "Wrong index";
    int number = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[number] = pMem[number] & (~mask);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || BitLen <= n) throw "Wrong index";
    return (pMem[GetMemIndex(n)] >> (n % (sizeof(TELEM) * 8))) & 1u;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (pMem != nullptr)
            delete[] pMem;
        pMem = nullptr;
        pMem = new TELEM[MemLen];
        if (pMem == nullptr) throw "Memmory Error";
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this == &bf) return 1;
    if (this->BitLen != bf.BitLen) return 0;
    for (int i = 0; i < this->BitLen; i++)
        if (this->GetBit(i) != bf.GetBit(i)) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField temp(this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen);
    if (this->BitLen > bf.BitLen)
    {
        for (int i = 0; i < bf.MemLen; i++)
            temp.pMem[i] = bf.pMem[i];
        for (int i = 0; i < this->MemLen; i++)
            temp.pMem[i] |= this->pMem[i];
    }
    else
    {
        for (int i = 0; i < this->MemLen; i++)
            temp.pMem[i] = this->pMem[i];
        for (int i = 0; i < bf.MemLen; i++)
            temp.pMem[i] |= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (BitLen > bf.BitLen)
    {
        TBitField result(BitLen);
        for (int i = 0; i < bf.BitLen; i++)
            if (GetBit(i) & bf.GetBit(i))
                result.SetBit(i);
        return result;
    }
    else
    {
        TBitField result(bf.BitLen);
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) & bf.GetBit(i))
                result.SetBit(i);
        return result;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(*this);
    for (int i = 0; i < BitLen; i++)
    {
        res.pMem[GetMemIndex(i)] ^= res.GetMemMask(i);
    }
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    string input;
    istr >> input;
    TELEM size = input.length();
    TBitField tmp(size);
    for (int i = 0; i < size; i++)
        if (input[i] == '1')
            tmp.SetBit(size - 1 - i);
    bf = tmp;
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
