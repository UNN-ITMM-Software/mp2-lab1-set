 // ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	if (len > -1) {
		MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw logic_error("Input error: incorrect length of BitField in constructor");

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > -1 && n < BitLen)
		return(n / (sizeof(TELEM) * 8));
	else
		throw logic_error("Input error: incorrect bit length");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM)*8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen)) 
		pMem[GetMemIndex(n)] |= GetMemMask(n);// pMem[] = pMem[]|GetMemMask
	else
		throw logic_error("Input error: incorrect bit index");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw logic_error("Input error: incorrect bit index");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
      return pMem[GetMemIndex(n)]  & GetMemMask(n);
	else
		throw logic_error("Input error: incorrect bit index");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL) delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (BitLen != bf.BitLen) res = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 1;
				break;
			}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];//копируем биты 1 аргумента
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];//делаем или со 2 аргументом
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField temp(len);
	//for (int i = 0; i < MemLen; i++) temp.pMem[i] = ~pMem[i];
	for (int i = 0; i < BitLen; i++)
		if (!GetBit(i))
			temp.SetBit(i);
	return temp;
}

// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	string tmp;
	istr >> tmp;
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (tmp[i] == '0')
			bf.ClrBit(i);
		else
			if (tmp[i] == '1')
				bf.SetBit(i);
			else break;
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	return ostr;
}
// ввод/вывод
ifstream& operator>>(ifstream& ifstr, TBitField& bf) // ввод
{
	string tmp;
	ifstr >> tmp;
	cout << tmp << endl;
	
	for (int i = 0; i < bf.GetLength(); i++)
	{
		if (tmp[i] == '0')
			bf.ClrBit(i);
		else
			if (tmp[i] == '1')
				bf.SetBit(i);
			else break;
	}
	return ifstr;
}
ofstream& operator << (ofstream& ofstr, const TBitField& bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i)) ofstr << "1";
		else ofstr << "0";
	return ofstr;
}
