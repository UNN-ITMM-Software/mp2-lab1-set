#include "tset.h"

TSet::TSet(int maxPower):MaxPower(maxPower),BitField(maxPower)
{
}

TSet::TSet(const TSet& set):MaxPower(set.MaxPower),BitField(set.BitField)
{
}

TSet::TSet(TBitField& bf):MaxPower(bf.GetLenght()),BitField(bf)
{ 
}

int TSet::GetMaxPower() const
{
	return MaxPower;
}

void TSet::InsElem(const int n)
{
	BitField.SetBit(n);
}

void TSet::DelElem(const int n)
{
	BitField.ClrBit(n);
}

bool TSet::IsMember(const int n)
{
	return BitField.GetBit(n);
}

bool TSet::operator==(const TSet& set) const
{
	return BitField == set.BitField;
}

TSet& TSet::operator=(const TSet& set)
{
	BitField = set.BitField;
	MaxPower = set.MaxPower;
	return *this;
}

TSet TSet::operator+(const TSet& set) const
{
	TBitField tmpB = BitField | set.BitField;
	TSet temp(tmpB);
	return temp;
}

TSet TSet::operator*(const TSet& set) const
{
	TBitField tmpB = BitField & set.BitField;
	TSet temp(tmpB);
	return temp;
}

TSet TSet::operator+(const int n)
{
	BitField.SetBit(n);
}

TSet TSet::operator-(const int n)
{
	BitField.ClrBit(n);
}
TSet TSet::operator~()
{
	TBitField tmpB = ~BitField;
	TSet temp(tmpB);
	return temp;
}

istream& operator>>(istream& istr, TSet& bf)
{
	int temp; char ch;
	do
	{
		istr >> ch;
	} while (ch != '{');
	do
	{
		istr >> temp; 
		bf.InsElem(temp);
		do
		{
			istr >> ch;
		} while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream&ostr, TSet& bf)
{
	int i, n;
	char ch = ' ';
	ostr << '{';
	n = bf.GetMaxPower();
	for (i =0; i < n; i++)
	{
		ostr << ch << ' ' << i;
		ch = ',';
	}
	ostr << '}';
	return ostr;
}
