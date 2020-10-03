// Битовое поле

#include "../include/tbitfield.h"

TBitField::TBitField(int len) : BitLen(len) 
{
	if (BitLen < 0)
		throw 1;
	MemLen = (len + 15) >> 4;
	pMem = new TELEM[MemLen];
	if (pMem != NULL) {
		for(int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL){
		for(int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 4;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 15);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ( (n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ( (n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ( (n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else 
		throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete pMem;
		pMem = new TELEM[MemLen];
	}
	if( pMem != NULL ) {
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool res = true;
	if (BitLen != bf.BitLen)
		res = false;
	else {
		for(int i = 0; i < MemLen; i++) {
			if(pMem[i] != bf.pMem[i]) {
				res = false;
				break;
			}
		}
	}
	return res;
}
bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField temp(bf.BitLen > BitLen ? bf.BitLen : BitLen);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for(int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField temp(bf.BitLen > BitLen ? bf.BitLen : BitLen);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for(int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~() // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = ~pMem[i];
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;
	do {
		istr >> ch;
	} while (ch != ' ');
	while (true) {
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1') 
			bf.SetBit(i++);
		else
			break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++) {
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
