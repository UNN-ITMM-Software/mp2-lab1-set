// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) {
	BitLen = len;
	MemLen = (len + 15) >> 4; // unsigned short int - 16 бит
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = NULL;
}

TBitField::TBitField(const TBitField &bf) {// конструктор копирования
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField(){
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const{// индекс Мем для бита n
	return n >> 4;
}

TELEM TBitField::GetMemMask(const int n) const{ // битовая маска для бита n
	return 1 << (n % 16); // 16 bits
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n){ // установить бит
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n){ // очистить бит
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const{ // получить значение бита
	if (n >= 0 && n < BitLen)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	return 0;
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
	if (MemLen != bf.MemLen || bf.BitLen != bf.BitLen)
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
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf){ // ввод
	int i = 0;
	char c;
	while (1) {
		istr >> c;
		if (c == '0')
			bf.ClrBit(i++);
		else if (c == '1')
			bf.SetBit(i++);
		else
			break;
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
