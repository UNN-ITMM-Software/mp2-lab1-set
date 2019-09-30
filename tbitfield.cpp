// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>
#include <bitset>

TBitField::TBitField(int len) {
	if (len < 0)
		throw 0;
	BitLen = len;
	MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования 
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; ++i)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() {
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{	if (n >= BitLen || n < 0)
		throw 0; else
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
	if (n < 0 || n >= BitLen)
		throw 0;
	int k = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[k] = pMem[k] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw 0;
	int k = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[k] = pMem[k] & ~(mask);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0)
		throw 0;
	int k = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return (pMem[k] & mask) > 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != bf.pMem) {
		delete[] pMem;
		TELEM *newMem = new TELEM[bf.MemLen];
		for (int i = 0; i < MemLen; i++) {
			newMem[i] = bf.pMem[i];
		}
		this->pMem = newMem;
		this->MemLen = bf.MemLen;
		this->BitLen = bf.BitLen;
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; ++i)
			if (pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tField(BitLen > bf.BitLen ? *this : bf);
	for (int i = 0; i < min(this->MemLen, bf.MemLen); i++) {
		tField.pMem[i] = this->pMem[i] | bf.pMem[i];
	}
	return tField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tField(BitLen > bf.BitLen ? *this : bf);
	for (int i = 0; i < min(this->MemLen, bf.MemLen); i++) {
		tField.pMem[i] = this->pMem[i] & bf.pMem[i];
	}
	return tField;
}

TBitField TBitField::operator~(void) // отрицание
{
	int BitSize = sizeof(TELEM) * 8;
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = ~pMem[i];
	pMem[MemLen - 1] = (pMem[MemLen - 1] << BitSize - (BitLen % BitSize)) >> BitSize - (BitLen % BitSize);
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	//При условии корректного ввода

	char* field;
	istr >> field;
	int i = 0;
	while (field[i] != '\0') {
		i++;
	}
	i--;
	TBitField bit(i);
	while (i >= 0) {
		if (field[i] == '1')
			bit.SetBit(i);
		i--;
	}
	bf = bit;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
	{
		ostr << std::bitset<8 * sizeof(TELEM)>(bf.pMem[i]);
	}