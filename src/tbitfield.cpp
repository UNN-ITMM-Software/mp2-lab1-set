// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw NegativeLen;
	BitLen = len;
	MemLen = len / (sizeof(TELEM) * 8);
	if (len % (sizeof(TELEM) * 8) != 0) MemLen++;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = 0U;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw NegativeIndex;
	if (n >= BitLen) throw OutOfBound;
	return MemLen - 1 - (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw NegativeIndex;
	if (n >= BitLen) throw OutOfBound;
	return 1U << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0U) return 0;
	else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf) return *this;

	if (pMem) delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int minLen;
	if (MemLen < bf.MemLen)
	{
		minLen = MemLen;
	}
	else
	{
		minLen = bf.MemLen;
	}
	for (int i = 0; i < minLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return (1 - (*this == bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField temp(0);
	int minLen;
	if (this->BitLen < bf.BitLen)
	{
		temp = bf;
		minLen = this->BitLen;
	}
	else
	{
		temp = *this;
		minLen = bf.BitLen;
	}
	for (int i = 0; i < minLen; i++)
	{
		if (this->GetBit(i) | bf.GetBit(i)) temp.SetBit(i);
		else temp.ClrBit(i);
	}
	return temp;
	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField temp(0);
	int minLen;
	if (this->BitLen < bf.BitLen)
	{
		temp = bf;
		minLen = this->BitLen;
	}
	else
	{
		temp = *this;
		minLen = bf.BitLen;
	}
	for (int i = 0; i < minLen; i++)
	{
		if (this->GetBit(i) & bf.GetBit(i)) temp.SetBit(i);
		else temp.ClrBit(i);
	}
	for (int i = minLen; i < temp.BitLen; i++) temp.ClrBit(i);
	return temp;
	
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;
	
	// старшие Mem инверитруются целиком 
	for (int i = MemLen - 1; i > 0; i--)
	{
		temp.pMem[i] = ~pMem[i];
	}
	// в младшем Mem инвертируются только фактиччески используемые биты
	for (int i = (MemLen - 1) * 8 * sizeof(TELEM); i < BitLen; i++)
	{
		if (GetBit(i)) temp.ClrBit(i); else temp.SetBit(i);
	}
	
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int n;
	istr >> n;
	if (bf.BitLen != n) throw DifferentLength;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> n;
		if (n) bf.SetBit(i);
		else bf.ClrBit(i);
	}
	
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << bf.BitLen << ' ';
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i) << ' ';
		if (i % 8 == 7) ostr << ' ';
	}
	return ostr;
}
