// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "Incorrect lenght";

	BitLen = len;
	MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
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
	BitLen = MemLen = 0;
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1))
	{
		throw "Incorrect bit";
	}
	else
	{
		return n / (sizeof(TELEM) * 8);
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen - 1))
	{
		throw "Incorrect bit";
	}
	else
	{
		return 1 << (n % (sizeof(TELEM) * 8));
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen - 1))
	{
		throw "Incorrect bit";
	}
	else
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);

	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen - 1))
	{
		throw "Incorrect bit";
	}
	else
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen - 1))
	{
		throw "Incorrect bit";
	}
	else
	{
		if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
			return 1;
		return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) // проверка (указатель на меня) 
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this; // возврат себя
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
			else
				return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 1;
			else
				return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmp;
	if (bf.BitLen > BitLen)
		tmp = bf.BitLen;
	else
		tmp = BitLen;

	TBitField res(tmp);

	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];

	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] |= bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmp;
	if (bf.BitLen > BitLen)
		tmp = bf.BitLen;
	else tmp = BitLen;

	TBitField res(tmp);
	if (bf.MemLen > MemLen)
		MemLen = bf.MemLen;

	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] &= bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res = *this;
	for (int i = 0; i < res.BitLen; i++)
	{
		if (res.GetBit(i))
			res.ClrBit(i);
		else
			res.SetBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int length, res;
	istr >> length;
	bf = TBitField(length);
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> res;

		if (res == 1)
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << bf.BitLen << " ";
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) == 1)
			ostr << 1 << " ";
		else
			ostr << 0 << " ";
	}
	return ostr;
}
