// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <iostream>

TBitField::TBitField(int len)
{
	MemLen = 0;
	BitLen = len;
	if (len >= 0) {
		MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
		return(n / (sizeof(TELEM) * 8));
	else
		throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << (n - GetMemIndex(n) * sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < BitLen) && (n >= 0))
		pMem[this->GetMemIndex(n)] = pMem[this->GetMemIndex(n)] | this->GetMemMask(n);
	else
		throw 1;

	 
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < BitLen)
		pMem[this->GetMemIndex(n)] = pMem[this->GetMemIndex(n)] & ~this->GetMemMask(n);
	else
		throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen)
		if (pMem[this->GetMemIndex(n)] & this->GetMemMask(n))
			return 1;
		else
			return 0;
	else throw 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.BitLen)
	{
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return false;
		}
		return true;
	}
	else
		return false;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return false;
	else
		return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = bf.pMem[i] | pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = bf.pMem[i] & pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{

	int i = 0;
	char sym;
	istr >> sym;
	while ((sym == '0') || (sym == '1')) {
		if (sym == '0')
			bf.ClrBit(i);
		else
			bf.SetBit(i);
		i++;
		istr >> sym;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i) << " ";
	}
	return ostr;
}

