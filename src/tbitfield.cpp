// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		MemLen = (len / 32) + 1;
		BitLen = len;
		pMem = new TELEM[len];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else throw logic_error("Invalide value of bitfield length in constructor");

}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	this->MemLen = bf.MemLen;
	this->BitLen = bf.BitLen;
	int len = (bf.GetLength() / 32) + 1;
	this->pMem = new TELEM[len];
	for (int i = 0; i < len; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}


}

TBitField::~TBitField()
{
	MemLen = 0;
	BitLen = 0;
	for (int i = 0; i < MemLen; i++)
	{
		delete[] & pMem[i];
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n >= 0) && (n < BitLen))
	{
		return(n / (sizeof(TELEM) * 8));
	}
	else throw logic_error("Invalide value of index in method");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n >= 0) && (n < BitLen))
	{
		int i = (n % (sizeof(TELEM) * 8));
		TELEM m = 1 << i;
		return m;
	}
	else throw logic_error("Invalide value of index in method");
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int m = (*this).GetMemMask(n);
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | m;
	}
	else throw logic_error("Invalide value of index in method");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		int m = (*this).GetMemMask(n);
		TELEM k = pMem[GetMemIndex(n)];
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~m);
	}
	else throw logic_error("Invalide value of index in method");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		int m = (*this).GetMemMask(n);
		int k = pMem[GetMemIndex(n)];
		m = k & m;
		if (m == 0)
			return 0;
		else return 1;
	}
	else throw logic_error("Invalide value of index in method");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf)
	{
		return *this;
	}
	this->MemLen = bf.MemLen;
	this->BitLen = bf.BitLen;
	delete[] this->pMem;
	if (this->MemLen != bf.MemLen)
		this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		this->pMem[i] = bf.pMem[i];
	return(*this);
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (this->BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
		if (this->pMem[i] != bf.pMem[i])
		{
			return 0;
			break;
		}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (this->BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < MemLen; i++)
		if (this->pMem[i] == bf.pMem[i])
		{
			return 0;
			break;
		}
	return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int l;
	if (this->BitLen < bf.BitLen)
		this->BitLen = bf.BitLen;
	l = (*this).GetLength();
	TBitField res(l);
	if (this->MemLen < bf.MemLen)
	{
		TELEM* temp = (this->pMem);
		this->MemLen = bf.MemLen;
		pMem = new TELEM[bf.MemLen];
		pMem = 0;
		pMem = temp;
		delete[]temp;
		res.pMem = (*this).pMem;
		for (int i = 0; i < MemLen; i++)
			res.pMem[i] = res.pMem[i] | bf.pMem[i];
		
	}
	res.pMem = (*this).pMem;
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = res.pMem[i] | bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (this->BitLen < bf.BitLen)
		this->BitLen = bf.BitLen;
	TBitField res(this->BitLen);
	if ((this->MemLen) < bf.MemLen)
	{
		TELEM* temp = (this->pMem);
		pMem = new TELEM[bf.MemLen];
		pMem = temp;
		pMem = 0;
		delete[]temp;
		MemLen = bf.MemLen;

	}
	res.pMem = (*this).pMem;
	for (int i = 0; i < bf.MemLen; i++)
	{
		res.pMem[i] = res.pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField m(BitLen);
	TBitField p(*this);
	for (int i = 0; i < m.GetLength(); i++)
	{
		m.SetBit(i);
	}
	for (int i = 0; i < MemLen; i++)
	{
		p.pMem[i] = ~p.pMem[i];
		p.pMem[i] = p.pMem[i] & m.pMem[i];
	}
	return p;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	istr >> bf.BitLen;
	istr >> bf.MemLen;
	for (int i = 0; i < bf.MemLen; i++)
		istr >> bf.pMem[i];
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	ostr << "Bitovoe pole rasmerom" << bf.GetLength() << endl;
	for (int i = 0; i < bf.MemLen; i++)
		for (int j = 0; j < bf.BitLen; j++)
			ostr << bf.GetBit(32 * i + j) << "  " << endl;
	return ostr;

}