
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw - 1;
	BitLen = len;
	MemLen = (len + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	
}


TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
	
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > -1 && n < BitLen)
		return(n / (sizeof(TELEM) * 8));
	else
		throw logic_error("Input error: incorrect bit length");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen)
		throw - 8;
	int i = GetMemIndex(n);
	pMem[i] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen)
		throw - 1;
	int i = GetMemIndex(n);
	pMem[i] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen)
		throw 8;
	int i = GetMemIndex(n);
	if ((pMem[i] & GetMemMask(n)) != 0)
	{
		return 1;
	}
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL) delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;
	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return false;
	}
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return true;
	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return true;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return true;
	}
	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		bf.pMem[i] = ~pMem[i];
	}
	return bf;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char C;
	do {
		istr >> C;
	} while (C != ' ');
	while (1)
	{
		istr >> C;
		if (C == '0') bf.ClrBit(i++);
		else
			if (C == '1') bf.SetBit(i++);
			else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
