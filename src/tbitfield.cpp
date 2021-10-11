// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
	if (len < 1)
	{
		throw "Incorrect length";
	}

	BitLen = len;
	MemLen = len / 32 + 1;
	pMem = new TELEM(MemLen);
	if (pMem != 0)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
	{
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	//delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int size = (sizeof(TELEM) * 8);
	int pos = n / size;
	return pos;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int k = n - sizeof(TELEM)*GetMemIndex(n);
	return 1 << k;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen) {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen) {
		pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
	}
	else throw - 1;

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen) {
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
	else throw - 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (bf.GetBit(i) != GetBit(i))
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen)
	{
		TBitField temp(bf);
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] |= pMem[i];
		}
		return temp;
	}
	TBitField temp(*this);
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
	{
		temp.pMem[i] &= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;
	for (int i = 0; i < temp.BitLen; i++)
	{
		if (temp.GetBit(i))
		{
			temp.ClrBit(i);
		}
		else
		{
			temp.SetBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c = istr.get();
	for (int i = 0, c = istr.get(); c != '\n'; ++i, c = istr.get())
	{
		if (c == '0')
		{
			bf.ClrBit(i);
		}
		else if (c == '1')
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << 1;
		}
		else
		{
			ostr << 0;
		}
	}
	return ostr;
}
