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
		MemLen = (len + sizeof(TELEM)*8) >> sizeof(TELEM);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else {
		throw logic_error("len < 0");
	} 
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i ++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");

	//int size = sizeof(TELEM) * 8;
	//int res = n / size;
	return n >> sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int s = sizeof(TELEM) * 8;
	return 1 << (n & (s - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // устан
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");
	int MemI = GetMemIndex(n);
	pMem[MemI] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");
	int MemI = GetMemIndex(n);
	pMem[MemI] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");
	int MemI = GetMemIndex(n);
	int res = pMem[MemI] & GetMemMask(n);
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this) {
		return *this;
	}

	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		delete []pMem;
		pMem = new TELEM[MemLen];
	}

	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

	if (MemLen == bf.MemLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
	}
	else
	{
		return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 1;
	}
	else
	{
		return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int mLen;
	if (bf.MemLen > MemLen)
	{
		mLen = bf.MemLen;
	}
	else
	{
		mLen = MemLen;
	}
	TBitField Res(mLen);
	for (int i = 0; i < MemLen; i++)
		Res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Res.pMem[i] |= bf.pMem[i];

	return Res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int mLen;
	if (bf.MemLen > MemLen)
	{
		mLen = bf.MemLen;
	}
	else
	{
		mLen = MemLen;
	}
	TBitField Res(mLen);
	for (int i = 0; i < MemLen; i++)
		Res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Res.pMem[i] &= bf.pMem[i];
	
	return Res;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField res(len);
	for (int i = 0; i < len; i++)
	{
		if (GetBit(i) == 0)
			res.SetBit(i);
	}
	return res;
}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char c;

	istr >> c;
	while (c != ' ') {
		istr >> c;
	}

	while (1)
	{
		istr >> c;
		if (c == '0') bf.ClrBit(i++);
		else
			if (c == '1') bf.SetBit(i++);
			else
				break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int l = bf.GetLength();
	for (int i = 0; i < l; i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	return ostr;
}
