// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len) {
	if (len > -1) {
		BitLen = len;
		MemLen = (len + 8 * sizeof(TELEM) - 1) >> (int)(log2(8 * sizeof(TELEM)) + 0.1);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = NULL;
	}
	else
		throw exception();
}

TBitField::TBitField(const TBitField &bf) {// конструктор копирования
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField(){
	if (pMem != NULL) {
	delete[] pMem;
		pMem = NULL;
	}
}

int TBitField::GetMemIndex(const int n) const{// индекс Мем для бита n
	return n >> (int)(log2(8 * sizeof(TELEM)) + 0.1);
}

TELEM TBitField::GetMemMask(const int n) const{ // битовая маска для бита n
	return 1 << (n%(sizeof(TELEM)*8)); // 32 bits
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n){ // установить бит
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw exception();
}

void TBitField::ClrBit(const int n){ // очистить бит
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw exception();
}

int TBitField::GetBit(const int n) const{ // получить значение бита
	if (n >= 0 && n < BitLen)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else
		throw exception();
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf){ // присваивание
	if (this == &bf)
		return *this;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (pMem != NULL)
		delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const{ // сравнение
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf){ // операция "или"
	int len = max(BitLen, bf.BitLen);
	TBitField result(len);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		result.pMem[i] |= bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf){ // операция "и"
	int len = max(BitLen, bf.BitLen);
	TBitField result(len);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		result.pMem[i] &= bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void){ // отрицание
	TBitField res(*this);
	for (int i = 0; i < res.BitLen; i++) {
		if (res.GetBit(i))
			res.ClrBit(i);
		else
			res.SetBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf){ // ввод
	int i = 0;
	char c;
	do {
		istr >> c;
	} while (c == ' ');
	while (1) {
		if (c == '0')
			bf.ClrBit(i++);
		else if (c == '1')
			bf.SetBit(i++);
		else
			break;
		istr >> c;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
