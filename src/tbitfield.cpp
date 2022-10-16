// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
	if (len >= 0)
	{
		BitLen = len;
		MemLen = (len + (sizeof(TELEM) * 8 - 1)) >> sizeof(TELEM);
		pMem = new TELEM[MemLen];
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
	}
	else
	{
		throw("Wrong length");
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) 
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
	{
		throw ("Out of bounds bit field");
	}
	else
	{
		return n / (sizeof(TELEM) * 8);
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen))
	{
		throw ("The bit number is not valid for the bit field");
	}
	else
	{
		return 1 << (n % (sizeof(TELEM) * 8));
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | (GetMemMask(n));
	}
	else
	{
		throw ("error index");
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n), m = GetMemMask(n);
		pMem[i] = pMem[i] & ~m;
	}
	else
	{
		throw "error index";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = GetMemIndex(n), m = GetMemMask(n);
		return (pMem[i] & m) == 0 ? 0 : 1;
	}
	else {
		throw "Error GetBit";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (bf == *this)
		return 0;
	else
		return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (bf == *this)
		return 1;
	else
		return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int l = BitLen;
	if (l < bf.BitLen) l = bf.BitLen;

	TBitField opb(l);

	for (int i = 0; i < MemLen; i++) {
		opb.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) {
		opb.pMem[i] |= bf.pMem[i];
	}

	return opb;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int l = BitLen;
	if (l < bf.BitLen) l = bf.BitLen;

	TBitField opb(l);

	for (int i = 0; i < MemLen; i++) {
		opb.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++)
	{
		opb.pMem[i] &= bf.pMem[i];
	}

	return opb;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField opb = (*this);
	for (int i = 0; i < BitLen; i++)
	{
		if (opb.GetBit(i))
		{
			opb.ClrBit(i);
		}
		else
		{
			opb.SetBit(i);
		}
	}
	return opb;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	size_t a;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		istr >> a;
		if (a == 0)
		{
			bf.ClrBit(i);
		}
		else
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}
