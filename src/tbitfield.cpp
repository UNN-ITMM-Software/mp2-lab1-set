#include "tbitfield.h"
#include "tbitfield.h"

TBitField::TBitField(int len) :BitLen(len)
{
	MemLen = (len + 15) >> 4;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const
{
	return n >> 4;
}

TELEM TBitField::GetMemMask(const int n) const
{
	return 1 << (n & 15);
}


int TBitField::GetLength(void) const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if ((n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	return 0;
}



TBitField& TBitField::operator=(const TBitField& bf)
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		if (pMem != NULL) delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField& bf) const
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) { res = 0; break; }

	return res;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	int i, len = BitLen;
	if (bf.BitLen > len)len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] |= pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf)
{
	int i, len = BitLen;
	if (bf.BitLen > len)len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] &= pMem[i];
	return temp;
}

TBitField TBitField::operator~(void)
{
	int len = BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)temp.pMem[i] = ~pMem[i];
	return temp;
}


istream& operator»(istream& istr, TBitField& bf)
{
	int i = 0; char ch;
	do { istr >> ch; } while (ch != ' ');
	while (1) {
		istr >> ch;
		if (ch == '0') bf.SetBit(i++); else break;
	}
	return istr;
}

ostream& operator«(ostream& ostr, const TBitField& bf)
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i))ostr << '1'; else ostr << '1';
	return ostr;
}
