// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
TBitField::TBitField(int len) {
	if (len < 0)
		throw "Negative length";

	BitLen = len;
	MemLen = (len / SIZE) + 1;

	pMem = new TELEM[BitLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) { // конструктор копирования
	pMem = new TELEM[bf.BitLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() {
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
	if (n < 0 || n > BitLen)
		throw "Incorrect value";

	return pMem[n / SIZE];
}

TELEM TBitField::GetMemMask(const int n) const { // битовая маска для бита n
	if (n < 0 || n > BitLen)
		throw "Incorrect value";

	return 1 << n % SIZE;
}

//// доступ к битам битового поля
//
int TBitField::GetLength(void) const { // получить длину (к-во битов)
	return BitLen;
}

void TBitField::SetBit(const int n) { // установить бит
	if (n < 0 || n > BitLen)
		throw "Incorrect value";

	pMem[n / SIZE] |= GetMemMask(n % SIZE);
}

void TBitField::ClrBit(const int n) { // очистить бит
	if (n < 0 || n > BitLen)
		throw "Incorrect value";

	pMem[n / SIZE] &= ~GetMemMask(n % SIZE);
}


int TBitField::GetBit(const int n) const { // получить значение бита
	if (n < 0 || n > BitLen)
		throw "Incorrect value";

	return pMem[n / SIZE] >> (n % SIZE) & 1;
}
//
//// битовые операции
//
TBitField& TBitField::operator=(const TBitField& bf) { // присваивание
	if (this->BitLen != bf.BitLen) {
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
	}

	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];

	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;

	return *this;
}

bool TBitField::operator==(const TBitField& bf) const { // сравнение
	if (this->BitLen != bf.BitLen)
		return false;

	for (int i = 0; i < bf.MemLen; ++i)
		if (this->pMem[i] != bf.pMem[i])
			return false;

	return true;
}

bool TBitField::operator!=(const TBitField& bf) const { // сравнение
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) { // операция "или"
	TBitField* temp;
	this->BitLen <= bf.BitLen ? temp = new TBitField(bf.BitLen) : temp = new TBitField(this->BitLen);

	int i = 0;
	while (i < this->BitLen && i < bf.BitLen) {
		temp->pMem[i] = pMem[i] | bf.pMem[i];
		++i;
	}
	return *temp;
}
//
TBitField TBitField::operator&(const TBitField& bf) { // операция "и"
	TBitField* temp;
	this->BitLen <= bf.BitLen ? temp = new TBitField(bf.BitLen) : temp = new TBitField(this->BitLen);

	int i = 0;
	while (i < this->BitLen && i < bf.BitLen) {
		temp->pMem[i] = pMem[i] & bf.pMem[i];
		++i;
	}
	return *temp;
}

TBitField TBitField::operator~(void) { // отрицание
	for (int i = 0; i < BitLen; ++i)
		this->GetBit(i) == 0 ? this->SetBit(i) : this->ClrBit(i);
	return *this;
}

//// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) { // ввод
	string str;
	istr >> str;
	int j = str.size() - 1;
	for (int i = 0; i < str.size(); i++, j--)
		if (str[i] == '1')
			bf.SetBit(j);
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) { // вывод
	int j = bf.BitLen - 1;
	for (int i = 0; i < bf.BitLen; i++, j--)
		bf.GetBit(j) == 0 ? ostr << 0 : ostr << 1;

	return ostr;
}