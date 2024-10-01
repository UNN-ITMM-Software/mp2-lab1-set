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
    {
        throw "ERROR";
    }
    else
    {
        BitLen = len;
        if (len % (sizeof(TELEM) * 8) == 0)
        {
            MemLen = len / (sizeof(TELEM)*8);//(32 / (4*8)) = 1
        }
        else
        {
            MemLen = (len / (sizeof(TELEM) * 8) + 1);//(35/(4*8) +1) = 2
        }
        pMem = new TELEM[MemLen];
        for (int i = 0;i < MemLen;i++)
            pMem[i] = 0;
    }
    

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen;i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
        delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if((n < 0) || (n > BitLen))
        throw "ERROR";
    else
        return n / (sizeof(TELEM) * 8);
    
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen))
        throw "ERROR";
    return 1 <<  (n - 1) % (8 * sizeof(TELEM));


}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if((n<0)||(n >= BitLen))
        throw "ERROR";
    pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "ERROR";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen))
        throw "ERROR";
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0)
        return 1;
    else
        return 0;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        if (BitLen != bf.BitLen)
        {
            delete[] pMem;
            BitLen = bf.BitLen;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; ++i)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) {

        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return 0;
            }
            else {}

        }
        return 1;
    }
    else {
        return 0;
    }
    
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return 1;
            }
        }
        return 0;
    }
    else {
        return 1;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int tmp;
    if (bf.BitLen > BitLen) {
        tmp = bf.BitLen;
    }
    else {
        tmp = BitLen;
    }
    TBitField result(tmp);

    for (int i = 0; i < bf.MemLen; i++)
    {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

    int tmp;
    if (bf.BitLen > BitLen) {
        tmp = bf.BitLen;
    }
    else {
        tmp = BitLen;
    }
    TBitField result(tmp);

    for (int i = 0; i < result.MemLen; i++)
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(*this);
    
    for (int i = 0; i < result.BitLen; i++) {
        if (result.GetBit(i)) {
            result.ClrBit(i);
        }
        else
            result.SetBit(i);
    }
    

    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string input;
    istr >> input;
    TBitField temp(input.length());
    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '1') {
            temp.SetBit(i);
        }
    }
    bf = temp;
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; ++i) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
