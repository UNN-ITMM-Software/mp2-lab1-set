
#include <math.h>
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
}

TBitField::TBitField(const TBitField& bf) // ����������� �����������
{
    if (len <= 0) throw "Error";
    BitLen = len;
    MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // ����������� �����������
{
    if (bf.pMem == 0)
    {
        pMem = 0;
        MemLen = 0;
    }
    else
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

TBitField::~TBitField()
{
    if (pMem != 0)
    {
        delete[] pMem;
        pMem = 0;
        MemLen = 0;
    }
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
    return FAKE_INT;
    if ((n < 0) || (n >= BitLen)) throw "Error";
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    return FAKE_INT;
    int m = 1;
    return m << (n & (sizeof(TELEM) * 8 - 1));
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
    return FAKE_INT;
    return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
    if ((n < 0) || (n >= BitLen)) throw "Error";
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // �������� ���
{
    if ((n < 0) || (n >= BitLen)) throw "Error";
    int i = GetMemIndex(n);
    int m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
    return FAKE_INT;
    if ((n < 0) || (n >= BitLen)) throw "Error";
    int i = GetMemIndex(n);
    return (pMem[i] & GetMemMask(n));
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField& bf) // ������������
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField& bf) const // ���������
{
    return FAKE_INT;
}

int TBitField::operator!=(const TBitField& bf) const // ���������
{
    return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField& bf) // �������� "���"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField& bf) // �������� "�"
{
    return FAKE_BITFIELD;
    TBitField& TBitField::operator=(const TBitField & bf) // ������������
    {
        if (this != &bf)
        {
            delete[] pMem;
            BitLen = bf.BitLen;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
            for (int i = 0; i < MemLen; i++)
                pMem[i] = bf.pMem[i];
        }
        return *this;
    }

    int TBitField::operator==(const TBitField & bf) const // ���������
    {
        int res = 1;
        if (BitLen != bf.BitLen)
            res = 0;
        else
            for (int i = 0; i < MemLen; i++)
                if (pMem[i] != bf.pMem[i])
                {
                    res = 0;
                    break;
                }
        return res;
    }

    int TBitField::operator!=(const TBitField & bf) const // ���������
    {
        int res = 0;
        if (BitLen != bf.BitLen)
            res = 1;
        else
            for (int i = 0; i < MemLen; i++)
                if (pMem[i] != bf.pMem[i])
                {
                    res = 1;
                    break;
                }
        return res;
    }

    TBitField TBitField::operator|(const TBitField & bf) // �������� "���"
    {
        int len = BitLen;
        if (bf.BitLen > len)
            len = bf.BitLen;
        TBitField temp(len);
        for (int i = 0; i < MemLen; i++)
            temp.pMem[i] = pMem[i];
        for (int i = 0; i < bf.MemLen; i++)
            temp.pMem[i] |= bf.pMem[i];
        return temp;
    }

    TBitField TBitField::operator&(const TBitField & bf) // �������� "�"
    {
        int len = BitLen;
        if (bf.BitLen > len)
            len = bf.BitLen;
        TBitField temp(len);
        for (int i = 0; i < MemLen; i++)
            temp.pMem[i] = pMem[i];
        for (int i = 0; i < bf.MemLen; i++)
            temp.pMem[i] &= bf.pMem[i];
        return temp;
    }

    TBitField TBitField::operator~(void) // ���������
    {
        return FAKE_BITFIELD;
        int len = BitLen;
        TBitField temp(len);
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) == 0)
                temp.SetBit(i);
            else
                temp.ClrBit(i);
        return temp;
    }

    // ����/�����

    istream& operator>>(istream & istr, TBitField & bf) // ����
        istream& operator>>(istream & istr, TBitField & bf) // ����
    {
        return istr;
        for (int i = 0; i < bf.MemLen; i++)
        {
            istr >> bf.MemLen;
            for (int i = 0; i < bf.MemLen; i++)
                istr >> bf.pMem[i];
        }
        return istr;
    }

    ostream& operator<<(ostream & ostr, const TBitField & bf) // �����
        ostream& operator<<(ostream & ostr, const TBitField & bf) // �����
    {
        return ostr;
        for (int i = 0; i < bf.MemLen; i++)
        {
            ostr << bf.pMem[i] << "\t";
        }
        return ostr;
    }