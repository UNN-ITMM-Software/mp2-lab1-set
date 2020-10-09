// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len >= 0) {
		BitLen = len;
		MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw logic_error("Input error: invalide value of bitfield length in constructor");
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}


TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int i = n % (sizeof(TELEM) * 8);
	TELEM mask = 1 << i;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen) {
		TELEM mask = GetMemMask(n);
		pMem[GetMemIndex(n)] |= mask;
	}
	else
		throw logic_error("Input error: invalide value of bitfield length in bit setting");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen) {
		TELEM mask = GetMemMask(n);
		pMem[GetMemIndex(n)] &= ~mask;
	}
	else
		throw logic_error("Input error: invalide value of bitfield length in bit clearing");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen) {
		TELEM mask = GetMemMask(n);
		TELEM i = pMem[GetMemIndex(n)];
		i &= mask;
		if (i == 0)
			i = 0;
		else
			i = 1;
		return i;
	}
	else
		throw logic_error("Input error: invalide value of bitfield length in bit getting");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
		return *this;
	}
	else
		return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (this->BitLen == bf.BitLen) {
		for (int i = 0; i < this->MemLen; i++) {
			if (this->pMem[i] != bf.pMem[i])
				return 0;
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (this->BitLen == bf.BitLen) {
		for (int i = 0; i < this->MemLen; i++) {
			if (this->pMem[i] != bf.pMem[i])
				return 1;
		}
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField tmp(BitLen);
	tmp = *this;
	if (tmp.BitLen < bf.BitLen)
		tmp.BitLen = bf.BitLen;
	if (tmp.MemLen < bf.MemLen) {
		TELEM* tmppMem = tmp.pMem;
		delete[] tmp.pMem;
		tmp.pMem = new TELEM[bf.MemLen];
		for (int i = 0; i < tmp.MemLen; i++)
			tmp.pMem[i] = tmppMem[i] | bf.pMem[i];
		for (int i = tmp.MemLen; i < bf.MemLen; i++)
			tmp.pMem[i] = 0;
		delete[] tmppMem;
		tmp.MemLen = bf.MemLen;
	}
	for (int i = 0; i < tmp.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}


TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField tmp(BitLen);
	tmp = *this;
	if (tmp.BitLen < bf.BitLen)
		tmp.BitLen = bf.BitLen;
	if (tmp.MemLen < bf.MemLen) {
		TELEM* tmppMem = tmp.pMem;
		delete[] tmp.pMem;
		tmp.pMem = new TELEM[bf.MemLen];
		for (int i = 0; i < tmp.MemLen; i++)
			tmp.pMem[i] = tmppMem[i] & bf.pMem[i];
		for (int i = tmp.MemLen; i < bf.MemLen; i++)
			tmp.pMem[i] = 0;
		delete[] tmppMem;
		tmp.MemLen = bf.MemLen;
	}
	for (int i = 0; i < tmp.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	tmp = *this;
	TBitField a(BitLen);
	for (int i = 0; i < a.BitLen; i++)
		a.SetBit(i);
	for (int i = 0; i < tmp.MemLen; i++) {
		tmp.pMem[i] = ~pMem[i];
		tmp.pMem[i] &= a.pMem[i];
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int tmp;
	istr >> tmp;
	TBitField tb(tmp);
	for (int i = 0; i < tmp; i++) {
		istr >> tmp;
		if (tmp) tb.SetBit(i);
	}
	bf = tb;
	return istr;

}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	ostr << bf.BitLen << endl;
	for (int i = 0; i < bf.MemLen; i++)
		ostr << (bf.pMem[i]) << endl;
	return ostr;
}

int TBitField::GetMemLen() const 
{
	return MemLen;
}