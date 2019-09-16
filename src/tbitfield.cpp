// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "Error length";
	BitLen = len;
	MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr)
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw "Error bit";
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw "Error bit";
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "Error bit";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "Error bit";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw "Error bit";
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != nullptr)
			delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != nullptr)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int check = 1;
	if (BitLen != bf.BitLen)
		check = 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				check = 0;
				break;
			}
	return check;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int check = 0;
	if (BitLen != bf.BitLen)
		check = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				check = 1;
				break;
			}
	return check;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField NewBitField(len);
	for (int i = 0; i < MemLen; i++)
		NewBitField.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		NewBitField.pMem[i] |= bf.pMem[i];
	return NewBitField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField NewBitField(len);
	for (int i = 0; i < MemLen; i++)
		NewBitField.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		NewBitField.pMem[i] &= bf.pMem[i];
	return NewBitField;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField NewBitField(*this);
	for (int i = 0; i < NewBitField.BitLen; i++)
	{
		if (NewBitField.GetBit(i))
			NewBitField.ClrBit(i);
		else
			NewBitField.SetBit(i);
	}
	return NewBitField;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string NewBitField;
	istr >> NewBitField;
	if (NewBitField.size() != bf.GetLength())
		throw "Error length";
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (NewBitField[i] == '0')
			bf.ClrBit(i);
		else if (NewBitField[i] == '1')
			bf.SetBit(i);
		else
			throw "Error input";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i))
			ostr << "0";
		else
			ostr << "1";
	return ostr;
}
