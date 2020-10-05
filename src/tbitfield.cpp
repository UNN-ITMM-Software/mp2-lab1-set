#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "wrong_index";
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM temp = 1;
	return temp << (n % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) throw "wrong_index";
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) throw "wrong_index";
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & ~GetMemMask(n);

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		return (pMem[i] & GetMemMask(n)) >> (n % 32);
	}
	else throw "wrong_index";
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			pMem = new TELEM[bf.BitLen];
		}

		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++)
			{
				pMem[i] = bf.pMem[i];
			}
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	TELEM MemMask = 0xffffffff;
	int res = 1;
	if (BitLen != bf.BitLen)
		res = 0;
	else
		for (int i = 0; i < MemLen - 1; i++)
			if ((pMem[i] & MemMask) != (bf.pMem[i] & MemMask))
			{
				res = 0; break;
			}
	for (int i = MemLen - 1; i < MemLen; i++)
		if (GetBit(i) != bf.GetBit(i))
		{
			res = 0; break;
		}
	return res;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	int res = 0;
	if (BitLen != bf.BitLen)
		res = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 1; break;
			}
	return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int i, len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int i, len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = ~pMem[i];
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int i = 0; char ch;
	do { istr >> ch; } while (ch != ' ');
	while (1) {
		istr >> ch;
		if (ch == '0') bf.ClrBit(i++);
		else
			if (ch == '1') bf.SetBit(i++);
			else break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	return ostr;
}