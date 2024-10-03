// ������� ����

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len > 0)
    {
        BitLen = len;                                                       
        MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = 0;
        }
    }
    else
        throw "Negative size";
}

TBitField::TBitField(const TBitField& bf) // ����������� �����������
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != 0) delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ p��� ��� ���� n
{
    if (n < 0 || n >= BitLen)
        throw "Parameter is out of range";

    return n >> 5;                            // ������������ ����� �� 32
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    if (n < 0 || n >= BitLen)
        throw "Parameter is out of range";

    return 1 << (n & 31);
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
    if (n < 0 || n >= BitLen)
        throw "Parameter is out of range";

    int i = GetMemIndex(n);
    int m = GetMemMask(n);

    pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // �������� ���
{
    if (n < 0 || n >= BitLen)
        throw "Parameter is out of range";

    int i = GetMemIndex(n);
    int m = GetMemMask(n);

    pMem[i] = pMem[i] & ~m;
}

bool TBitField::GetBit(const int n) const // �������� �������� ����
{
    if (n < 0 || n >= BitLen)
        throw "Parameter is out of range";

    int i = GetMemIndex(n);
    int m = GetMemMask(n);

    return pMem[i] & m;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField& bf) // ������������
{
    if (&bf == this)
        return *this;

    delete[] pMem;

    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField& bf) const // ���������
{
    if (MemLen != bf.MemLen)
        return false;

    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return false;
    }

    return true;
}

int TBitField::operator!=(const TBitField& bf) const // ���������
{
    if (MemLen != bf.MemLen)
        return true;

    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return true;
    }

    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // �������� "���"
{
    if (MemLen != bf.MemLen)
        throw "Error";

    TBitField result(*this);

    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }

    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // �������� "�"
{
    if (MemLen != bf.MemLen)
        throw "Error";

    TBitField result(*this);

    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return result;
}

TBitField TBitField::operator~(void) // ���������
{
    TBitField result(*this);

    for (int i = 0; i < MemLen; i++)
    {
        result.pMem[i] = ~pMem[i];
    }

    int last_number_bit = BitLen - (MemLen - 1) * (sizeof(TELEM) * 8);
    if (last_number_bit < sizeof(TELEM) * 8) 
    {
        int mask = (1 << (last_number_bit)) - 1;
        result.pMem[MemLen - 1] &= mask;
    }

    return result; 
}

// ����/�����

istream& operator>>(istream& istr, TBitField& bf) // ����
{
    int tmp = 0;

    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> tmp;
        bf.SetBit(tmp);
    }

    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // �����
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
            ostr << i << ' ';
    }

    return ostr;
}