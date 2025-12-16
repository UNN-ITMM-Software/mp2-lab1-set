#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0) throw len;
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

int TBitField::GetLength(void) const
{
    return BitLen;
}

void TBitField::SetBit(const int n)
{
    if ((n < 0) || (n >= BitLen)) throw n;
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
    if ((n < 0) || (n >= BitLen)) throw n;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
    if ((n < 0) || (n >= BitLen)) throw n;
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField &bf) const
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const
{
    return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField &bf)
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        if (MemLen != bf.MemLen)
        {
            MemLen = bf.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

TBitField TBitField::operator|(const TBitField &bf)
{
    int len = BitLen;
    if (bf.BitLen > len) len = bf.BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        temp.pMem[i] |= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf)
{
    int len = BitLen;
    if (bf.BitLen > len) len = bf.BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        temp.pMem[i] &= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator~(void)
{
    TBitField temp(BitLen);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = ~pMem[i];
    
    int bits = BitLen % (sizeof(TELEM) * 8);
    if (bits != 0)
    {
        TELEM mask = (1 << bits) - 1;
        temp.pMem[MemLen - 1] &= mask;
    }
    return temp;
}

istream &operator>>(istream &istr, TBitField &bf)
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        char ch;
        istr >> ch;
        if (ch == '0') bf.ClrBit(i);
        else if (ch == '1') bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << (bf.GetBit(i) ? '1' : '0');
    return ostr;
}