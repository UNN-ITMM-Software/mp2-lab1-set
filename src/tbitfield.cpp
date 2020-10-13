// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tbitfield.h"
#include <cmath>

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = ceil((double)(len) / (sizeof(TELEM) * 8));
		if ((len % (sizeof(TELEM) * 8)) > 0)
		{
			MemLen++;
		}
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		throw "Не положительное количество элементов";
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	for (int i = 0; i < bf.MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
	if (pMem != nullptr)
		delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1))
		throw "Неверный индекс";
	else
	{
		int Index = (floor((double)n / (sizeof(TELEM) * 8)));
		return Index;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int position = (n % (sizeof(TELEM) * 8));		//на какой позиции находится бит в ячейке массива
	mask = mask << position;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = this->GetMemIndex(n); //в какой ячейке массива содержится бит	
		pMem[num] = pMem[num] | GetMemMask(n); // устанавливаем бит
	}
	else
	{
		throw "Некорректный индекс бита";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = this->GetMemIndex(n); //в какой ячейке массива содержится бит
		pMem[num] = pMem[num] & ~(*this).GetMemMask(n); // очищаем бит
	}
	else
	{
		throw "Некорректный индекс бита";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); //в какой ячейке массива содержится бит		
		if ((pMem[num] & GetMemMask(n)) == GetMemMask(n))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		throw "Некорректный индекс бита";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this->BitLen == bf.BitLen)
	{
		for (int i = 0; i <= bf.MemLen; i++)
		{
			this->pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		delete[] this->pMem;
		this->BitLen = bf.BitLen;
		this->MemLen = ceil((double)(bf.BitLen) / (sizeof(TELEM) * 8));
		if ((bf.BitLen % (sizeof(TELEM) * 8)) > 0)
		{
			this->MemLen++;
		}
		this->pMem = new TELEM[this->MemLen];
		for (int i = 0; i <= bf.MemLen; i++)
		{
			this->pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len;
	int minMlen;
	int k = 1;
	if (BitLen < bf.BitLen)
		k = 0;
	if (k == 1) {
		len = BitLen;
		minMlen = bf.MemLen;
	}
	else {
		len = bf.BitLen;
		minMlen = MemLen;
	}
	TBitField res(len);
	for (int i = 0; i < mMlen; i++)
		res.pMem[i] = pMem[i] | bf.pMem[i];
	if (k == 1)
		for (int i = mMlen; i < res.MemLen; i++)
			res.pMem[i] = pMem[i];
	else
		for (int i = mMlen; i < res.MemLen; i++)
			res.pMem[i] = bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int maxMemLen, bitlen;
	if (bf.BitLen > BitLen) {
		maxMemLen = MemLen;
		bitlen = bf.BitLen;
	}
	else {
		maxMemLen = bf.MemLen;
		bitlen = BitLen;
	}
	TBitField crossing(bitlen);
	for (int i = 0; i < maxMemLen; i++)
		crossing.pMem[i] = pMem[i] & bf.pMem[i];
	return crossing;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < BitLen; i++)
	{
		res.pMem[GetMemIndex(i)] ^= res.GetMemMask(i);
	}
	return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int k;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> k;
		while ((k != 1) && (k != 0))
			istr >> k;
		if (k == 1)
			bf.SetBit(i);
		else
			bf.ClrBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if ((bf.pMem[(int)(i / (sizeof(TELEM) * 8))] & bf.GetMemMask(i)) == bf.GetMemMask(i))
		{
			ostr << "1";
		}
		else
		{
			ostr << "0";
		}
	}
	return ostr;
}
