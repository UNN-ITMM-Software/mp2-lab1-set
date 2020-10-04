// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len) // конструктор преобразования типа
{
	if (len <= 0)
		throw "Invalid len parameter";
	MemLen = int(ceil(len / (sizeof(TELEM) * 8.0)));
	pMem = new TELEM[MemLen];
	BitLen = len;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() // деструктор
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
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
	if ((n < 0) || (n >= BitLen))
		throw "Parameter n out of range";
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] = pMem[index] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "Parameter n out of range";
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] = pMem[index] & ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw "Parameter n out of range";
	TELEM elem = pMem[GetMemIndex(n)];
	TELEM mask = GetMemMask(n);
	return int(bool(pMem[GetMemIndex(n)] & mask));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	if (MemLen != bf.MemLen)
	{
		delete[] pMem;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this == &bf)
		return 1;
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i))
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (MemLen > bf.MemLen)
	{
		TBitField result(*this);
		for (int i = 0; i < bf.MemLen; i++)
			result.pMem[i] = pMem[i] | bf.pMem[i];
		return result;
	}
	else 
	{
		TBitField result(bf);
		for (int i = 0; i < MemLen; i++)
			result.pMem[i] = pMem[i] | bf.pMem[i];
		return result;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField result(BitLen);
		for (int i = 0; i < bf.BitLen; i++)
			if (GetBit(i) & bf.GetBit(i))
				result.SetBit(i);
		return result;
	}
	else
	{
		TBitField result(bf.BitLen);
		for (int i = 0; i < BitLen; i++)
			if (GetBit(i) & bf.GetBit(i))
				result.SetBit(i);
		return result;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < result.MemLen; i++)
		result.pMem[i] = ~pMem[i];
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int len;
	istr >> len;
	TBitField result(len);
	for (int i = 0; i < len; i++)
	{
		int bit;
		istr >> bit;
		if (bit == 1)
			result.SetBit(len - i - 1);
	}
	bf = result;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(bf.BitLen - i - 1);
	return ostr;
}
