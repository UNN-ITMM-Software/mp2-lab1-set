// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include "math.h"


TBitField::TBitField(int len)
{
	if (len < 1) throw  "Wrong length";
	BitLen = len;
	MemLen = ceil((double)(len - 1)/(sizeof(TELEM)*8));
	//MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0 << (sizeof(TELEM)*8);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = 0;
	pMem = new TELEM[MemLen];
	if (pMem = 0) throw "Memmory Error";
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen) throw "Wrong index";
	return (floor((double)n / (sizeof(TELEM) * 8)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	//if (n < 0 || n >= BitLen) throw "Wrong index";
	//int number = n % sizeof(TELEM) * 8;
	//TELEM mask = 1 << number;
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	//if (n < 0 || n > BitLen) throw "Wrong index";
	int number = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[number] = pMem[number] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) throw "Wrong index";
	int number = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[number] = pMem[number] & (~mask);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || BitLen <= n) throw "Wrong index";
	//TELEM res;
	//int mask = GetMemMask(n);
	//int number = GetMemIndex(n);
	//res = pMem[number] & mask;
	//if (res != 0)
		//return 1;
	//return 0;
	return (pMem[GetMemIndex(n)] >> (n % (sizeof(TELEM) * 8))) & 1u;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = 0;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this == &bf) return 1;
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if(*this == bf)  return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TELEM size = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TELEM count = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(size);
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < count; i++)
			res.pMem[i] = pMem[i];
		for (int i = 0; i < size; i++)
			res.pMem[i] = res.pMem[i] | bf.pMem[i];
	}
	else
	{
		for (int i = 0; i < count; i++)
			res.pMem[i] = bf.pMem[i];
		for (int i = 0; i < size; i++)
			res.pMem[i] = res.pMem[i] | pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TELEM size = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(size);
	for (int i = 0; i < size; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = ~pMem[i];
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string input;
	istr >> input;
	TELEM size = input.length();
	TBitField tmp(size);
	for (int i = 0; i < size; i++)
		if (input[i] == '1')
			tmp.SetBit(size - 1 - i);
	bf = tmp;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
