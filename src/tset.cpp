// ��������� - ���������� ����� ������� ����

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(1)
{
    if (mp < 0) 
        throw "Negative power";
    MaxPower = mp;
    BitField = TBitField(MaxPower);
}

// ����������� �����������
TSet::TSet(const TSet& s) : BitField(1)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// ����������� �������������� ����
TSet::TSet(const TBitField& bf) : BitField(1)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
    return MaxPower;
}

bool TSet::IsMember(const int Elem) const // ��������� ������� �������� � ���������
{
    if (Elem < 0 || Elem > MaxPower)
        throw "Elem is out of range";
    if (BitField.GetBit(Elem) == 1) 
        return true;
    return false;
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
    if (Elem < 0 || Elem > MaxPower)
        throw "Elem is out of range";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
    if (Elem < 0 || Elem > MaxPower)
        throw "Elem is out of range";
    BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet& s) // ������������
{
    if (&s == this) return *this;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // ���������
{
    if (MaxPower != s.MaxPower) return false;
    if (BitField != s.BitField) return false;
    return true;
}

int TSet::operator!=(const TSet& s) const // ���������
{
    if (MaxPower != s.MaxPower) return true;
    if (BitField != s.BitField) return true;
    return false;
}

TSet TSet::operator+(const TSet& s) // �����������
{
    TSet tmp(s.MaxPower > MaxPower ? s.MaxPower : MaxPower);
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
    TSet tmp(Elem > MaxPower ? Elem : MaxPower);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
    TSet tmp(MaxPower);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s) // �����������
{
    TSet tmp(s.MaxPower > MaxPower ? s.MaxPower : MaxPower);
    tmp.BitField = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // ����������
{
    TSet tmp(*this);
    tmp = ~BitField;
    return tmp;
}

// ���������� �����/������

istream& operator>>(istream& istr, TSet& s) // ����
{

    int tmp = 0;
    for (int i = 0; i < s.MaxPower; i++)
    {
        istr >> tmp;
        s.InsElem(tmp);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // �����
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        ostr << s.BitField.GetBit(i);
    }
    return ostr;
}