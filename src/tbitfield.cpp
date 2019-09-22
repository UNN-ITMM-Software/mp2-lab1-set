// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
//using namespace std;
TBitField::TBitField(int len) : BitLen(len) //инициализатор
{
	if (len < 0) {
		throw std::runtime_error("не верно введена  длина");
	}
	MemLen = (BitLen-1) / 32 +1;
	pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen]();
	for (int i = 0; i < BitLen; i++) 
		if (bf.GetBit(i)) 
			SetBit(i);
}

TBitField::~TBitField()
{
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
		BitLen = 0;
		MemLen = 0;
	}
}
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > BitLen) || (n < 0)) {
		throw std::runtime_error("не верно введены данные");
	}
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{	TELEM mask = 1;
	if ((n > 31) || (n < 0)) {
		throw std::runtime_error("не верно введены данные");
	}
	return mask << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] | GetMemMask(n - i * 32);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & (~GetMemMask(n - 32*i ));   
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int i = GetMemIndex(n);
	return pMem[i] & GetMemMask(n - i * 32); 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen]();
	for (int i = 0; i < BitLen; i++) 
		if (bf.GetBit(i)) 
			SetBit(i);
		
	
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return false;
	}
	for (int i = 0; i < BitLen; i++) 
		if (GetBit(i) != bf.GetBit(i)) 
			return false;
		
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return true;
	}
	for (int i = 0; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i)) {
			return true;
		}
	}
	return false;
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	int  len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int  len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; ++i)
		tmp.pMem[i] =~pMem[i];
	return tmp;
	
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	istr >> bf.BitLen;
	istr >> bf.MemLen;

	for (int i = 0; i < bf.MemLen; ++i)
		istr >> bf.pMem[i];
	return istr; 
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.MemLen; ++i)
		ostr << bf.pMem[i] << " ";
	ostr << bf.BitLen << bf.MemLen << " ";
	ostr << endl;
	return ostr;
}
