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
	if (len >= 0) {
		MemLen = len/(sizeof(TELEM)*8) + 1;
		pMem = new TELEM[MemLen];
		BitLen = len;
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = 0;
		}
	}
	else throw - 1;
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
	MemLen = 0;
	BitLen = 0;
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw - 1;
	return (n) / (sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw - 1;
	TELEM m = 1 << (n % (sizeof(TELEM)*8));
	return m;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) throw - 1;
	TELEM m = GetMemMask(n);
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) throw - 1;
	TELEM m = ~GetMemMask(n);
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) throw - 1;
	TELEM m = GetMemMask(n);
	int i = GetMemIndex(n);
	int res = (pMem[i] & m) > 0 ? 1 : 0;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen && BitLen == bf.BitLen) {
		bool res = true;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				res = false;
		return res;
	}
	return false;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (!(*this == bf)) return true;
	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int l = bf.MemLen > MemLen ? MemLen : bf.MemLen;
	TBitField res(bf.BitLen > BitLen ? bf:*this);
	for (int i = 0; i < l; i++) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int l1 = bf.BitLen > BitLen ? bf.BitLen : BitLen, l2 = bf.BitLen > BitLen ? BitLen : bf.BitLen;
	TBitField res(l1);
	for (int i = 0; i < res.MemLen; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen - 1; i++)
		res.pMem[i] = ~pMem[i];
	TELEM m = (~(0)) << (BitLen % (sizeof(TELEM)*8));
	res.pMem[MemLen - 1] = ~(pMem[MemLen - 1]) & ~m;
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string s;
	istr >> s;
	bf = *new TBitField(s.length());
	for (int i = 0; i < bf.BitLen; i++) {
		if (s[i] == '1') bf.SetBit(i);
		else if (s[i] != '0') throw - 1;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}
