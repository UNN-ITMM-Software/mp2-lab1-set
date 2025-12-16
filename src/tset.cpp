#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    if (mp <= 0) throw mp;
    MaxPower = mp;
}

TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

void TSet::InsElem(const int Elem)
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw Elem;
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw Elem;
    BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw Elem;
    return BitField.GetBit(Elem);
}

int TSet::operator==(const TSet &s) const
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const
{
    return !(*this == s);
}

TSet& TSet::operator=(const TSet &s)
{
    if (this != &s)
    {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

TSet TSet::operator+(const int Elem)
{
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem)
{
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator+(const TSet &s)
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator*(const TSet &s)
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void)
{
    TSet temp(~BitField);
    return temp;
}

istream &operator>>(istream &istr, TSet &s)
{
    return istr >> s.BitField;
}

ostream &operator<<(ostream &ostr, const TSet &s)
{
    return ostr << s.BitField;
}