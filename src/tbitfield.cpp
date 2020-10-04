#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw logic_error("Invalid size");

	BitLen = len;
	MemLen = len;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
	BitLen = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1;
}


int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= (*this).BitLen)) throw logic_error("invalid position");
	pMem[GetMemIndex(n)] = 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) throw logic_error("invalid position");
	pMem[GetMemIndex(n)] = 0;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || (n >= BitLen)) throw logic_error("Invalid index");
	TELEM mask = GetMemMask(n);
	TELEM bit = pMem[GetMemIndex(n)];
	bit = bit & mask;
	(bit != 0) ? (bit = 1) : (bit);
	return bit;
}


TBitField& TBitField::operator=(const TBitField& bf) // присваивание
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

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
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

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	int res = 0;
	if (BitLen == bf.BitLen)
	{
		res = 1;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] == bf.pMem[i])
			{
				res = 1;
				break;
			}
		}
	}
	return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = MemLen;

	if (bf.MemLen > len)
	{
		len = bf.MemLen;
	}

	TBitField temp(len);

	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int i, len = BitLen;
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

	if (bf.BitLen < len)
	{
		for (int i = bf.BitLen; i < MemLen; i++)
		{
			temp.pMem[i] = 0;
		}
	}
	return temp;
}
TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] == 0)
		{
			pMem[i] = 1;
		}
		else if (pMem[i] == 1)
		{
			pMem[i] = 0;
		}
	}
	return *this;
}


istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int n;
	istr >> n;
	TBitField s(n);
	for (int i = 0; i < n; i++)
	{
		istr >> n;
		if (n == 1)
		{
			s.SetBit(i);
		}
	}
	bf = move(s);
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	int len = bf.GetLength();
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