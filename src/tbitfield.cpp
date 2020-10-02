#include "tbitfield.h"
#include <iostream>
#include <exception>
TBitField::TBitField()
{
	BitLen = 10;
	MemLen = (BitLen + 15) >> 4;
	pMem = new TELEM[MemLen];
	for (auto i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}
TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen + 15) >> 4;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		throw std::exception("Invaled exeption");
	}
}
TBitField::TBitField(const TBitField& bf)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for ( int i = 0;i < MemLen;i++)
	{
		pMem[i] = bf.pMem[i];
	}

}
TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}
void TBitField::SetBit(const int n)
{
	if ((n > -1)&&(n < BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}
void TBitField::ClrBit(const int n)
{
	if ((n > -1) && (n< BitLen))
	{
		pMem[GetMemIndex(n)] |= ~GetMemMask(n);
	}
}
int TBitField::GetBit(const int n)
{
	if ((n > -1) && (n < BitLen))
	{
		return pMem[GetMemIndex(n)] && GetMemMask(n);
	}
	else
		return 0;
}
int TBitField::GetMemIndex(const int n)
{
	return n >> 4;
}

TELEM TBitField::GetMemMask(const int n)
{
	return 1 << (n & 15);
}

int TBitField::GetLenght()
{
	return BitLen;
}

bool TBitField::operator==(const TBitField& bf)const
{
	int res = 1;
	if (BitLen != bf.BitLen)
	{
		res = 0;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
		}
	}
	return res;
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
		{
			delete pMem;
		}
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

TBitField TBitField::operator|(const TBitField& bf)const
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf)const
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] &= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~()
{
	int len = BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = ~pMem[i];
	}
	return temp;
}


std::istream& operator>>(istream& istr, TBitField& bf)
{
	int i = 0; char ch;
	/*do
	{
		istr >> ch;
	} while (ch != ' ');
	*/
	int Source=1;
	while (Source!=bf.GetLenght())
	{
		istr >> ch;
		if (ch == '0')
		{
			bf.ClrBit(i++);
			Source++;
		}
		else
			if (ch == '1')
			{
				bf.SetBit(i++);
				Source++;
			}
			else
				break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, TBitField& bf)
{
	int len = bf.GetLenght();
	for (int i = 0; i < len; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}
