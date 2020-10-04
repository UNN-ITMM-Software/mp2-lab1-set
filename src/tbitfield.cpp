// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Oshibka";
	}
	BitLen = len;
	MemLen = len/(sizeof(TELEM)*8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	if (pMem != NULL) {
		delete[] pMem;
		pMem = NULL;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int index = (n / (sizeof(TELEM) * 8));
	return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int index = (n % (sizeof(int) * 8));
	TELEM Mask = 1 << index;
	return Mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw "Oshibka";
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw "Oshibka";
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
	{
		throw "Oshibka";
	}
	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf)
		return *this;
	else {
		BitLen = bf.BitLen;
		if (MemLen != bf.MemLen) {
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int temp;
	if (BitLen != bf.BitLen)
		temp = 0;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				temp = 0;
			else
				temp = 1;
		}
	}
	return temp;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	int temp;
	if (BitLen != bf.BitLen)
		temp = 1;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				temp = 1;
			else
				temp = 0;
		}
	}
	return temp;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int BitLen_temp = BitLen;

	if (bf.BitLen > BitLen_temp) {
		BitLen_temp = bf.BitLen;
	}

	TBitField temp(BitLen_temp);

	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++) {
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int BitLen_temp = BitLen;
	if (bf.BitLen > BitLen_temp) {
		BitLen_temp = bf.BitLen;
	}
	TBitField temp(BitLen_temp);

	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++) {
		temp.pMem[i] &= bf.pMem[i];
	}
	
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(*this);

	for (int i = 0; i < temp.BitLen; i++) {
		if (temp.GetBit(i)) {
			temp.ClrBit(i);
		}
		else
			temp.SetBit(i);
	}
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int k = 0;
	char temp;
	do {
		istr >> temp;
	} while (temp != ' ');

	while (1) {
		istr >> temp;
		if (temp == '0')
			bf.ClrBit(k++);
		else if (temp == '1')
			bf.SetBit(k++);
		else 
			break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	int temp = bf.GetLength();
	for (int i = 0; i < temp; i++) {
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
