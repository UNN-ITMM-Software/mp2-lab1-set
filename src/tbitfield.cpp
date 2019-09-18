// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)	//конструктор инициализации
{
	if (len < 0)
		throw len;
	else
	{
		BitLen = len;
		MemLen = (BitLen-1) / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()		//деструктор
{
	BitLen = 0;
	MemLen = 0;
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw n;
	else
		return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw n;
	else
	{
		int m = n % (sizeof(int) * 8);		
		TELEM Mask = 1 << m;
		return Mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);

	}

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] &~ GetMemMask(n);

	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		int tmp = pMem[GetMemIndex(n)];
		tmp = tmp & GetMemMask(n);
		if (tmp != 0) return 1;
		else return 0;
	}

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf != this)
	{
		if (BitLen == bf.BitLen)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		else
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return false;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return false;
		}
		return true;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int k = 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.GetBit(i))
			k = 1;
	}
  return k;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(*this);
	int min = bf.MemLen;

	if (BitLen < bf.BitLen)
	{	
		min = MemLen;
		tmp = bf;		
	}

	for (int i = 0; i < min; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];

	return tmp;
	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < bf.BitLen; i++)
		{
			if (GetBit(i) && (bf.GetBit(i)))
				tmp.SetBit(i);
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) && (bf.GetBit(i)))
				tmp.SetBit(i);
		}
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)			res.SetBit(i);
		
		else res.ClrBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int Len;
	int tmp;
	istr >> Len;
	bf = TBitField(Len);
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> tmp;
		if (tmp == 1)
			bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++) 
	{
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
