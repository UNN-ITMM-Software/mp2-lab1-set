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
		throw - 1;
	BitLen = len;
	int size = sizeof(TELEM) * 8;
	MemLen = (len + size - 1)/size;
	pMem = new TELEM[MemLen];
    if (pMem != NULL)
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) 
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if(pMem!=NULL)
	{
		delete pMem;
		pMem = NULL;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n /( sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8) - 1);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
		throw -1;
	pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw - 1;
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
		throw -1;
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
        return 1;
    else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	else
	{
		BitLen = bf.BitLen;
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			if (pMem != NULL)
				delete pMem;
			pMem = new TELEM[MemLen];
		}
		if (pMem != NULL) 
	        for (int i = 0; i < MemLen; i++)
			    pMem[i] = bf.pMem[i];
        return *this;
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) 
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) 
				return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len) 
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) 
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) 
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) 
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField temp(len);
	for (int i = 0; i < temp.BitLen; i++)
	{
		if (GetBit(i))
			temp.ClrBit(i);
		else temp.SetBit(i);
	}
	return temp;

    
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0; 
	char ch;
	do { istr >> ch; } 
	while (ch != ' ');
	while (1) 
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else
			if (ch == '1') 
			    bf.SetBit(i++); 
		    else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i)) 
			ostr << '1';
		else ostr << '0';
	return ostr;
}