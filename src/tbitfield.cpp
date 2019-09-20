// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) {
		throw "negative_length";
	}
	BitLen = len;
	MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0) throw "negative_index/too_large_index";
	pMem[GetMemIndex(n)] = (pMem[GetMemIndex(n)] | GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0) throw "negative_index/too_large_index";
	pMem[GetMemIndex(n)] = (pMem[GetMemIndex(n)] & ~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0) throw "negative_index/too_large_index";
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	if (MemLen != bf.MemLen)
		return 0;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	if (MemLen != bf.MemLen)
		return 1;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] == bf.pMem[i])
			return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField just(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++) {
		just.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++) {
		just.pMem[i] = just.pMem[i] | bf.pMem[i];
	}
	return just;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField just(BitLen > bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++) {
		just.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++) {
		just.pMem[i] = just.pMem[i] & bf.pMem[i];
	}
	return just;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField just(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
		{
			just.SetBit(i);
		}
	}
	return just;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a, b;
	istr >> a;
	bf = TBitField(a);
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> b;
		if (b)
			bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << bf.BitLen << " ";
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i) << " ";
	}
	return ostr;
}
