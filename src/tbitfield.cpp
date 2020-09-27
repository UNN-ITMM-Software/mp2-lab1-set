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
		MemLen = log(sizeof(TELEM) * 8 * len) / log(2);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else {
		throw invalid_argument("len < 0");
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
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");

	int size = sizeof(TELEM) * 8;
	int res = (n + size - 1) / size;
	return res;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");

	TELEM res = pMem[GetMemIndex(n)] & (1 << n);
	return res;
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
	int i = n / MemI;
	pMem[MemI] |= 1 << i;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");
	int MemI = GetMemIndex(n);
	int i = n / MemI;
	pMem[MemI] &= (1 << i);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw std::logic_error("Negative length");
	if (n >= BitLen) throw std::logic_error("Too large ind");
	int MemI = GetMemIndex(n);
	int i = n / MemI;
	int res = pMem[MemI] & (1 << i);
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
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

	for (int i = 0; i < mLen; i++)
	{
		Res.pMem[i] = pMem[i] | bf.pMem[i];
	}
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
	for (int i = 0; i < mLen; i++)
		Res.pMem[i] = pMem[i] & bf.pMem[i];
	
	return Res;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = ~pMem[i];
	}
	return *this;
}

// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	//int c = 1;
	for (int i = 0; i < bf.MemLen; i ++)
	{
		istr >> bf.pMem[i];
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int c = 1;
	ostr << "<";
	for (int i = 0; i < bf.MemLen; i++)
	{
		TELEM temp = bf.pMem[i];
		while (temp > 0)
		{
			if (temp % 2 == 0)
				ostr << 0 << " ";
			else
				ostr << 1 << " ";
			temp /= 2;
		}
	}
	ostr << ">" << endl;
	return ostr;
}
