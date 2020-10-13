// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw exception("Error: Negative index.");
	BitLen = len;
	MemLen = len / 32 + 1;
	pMem = new TELEM[(TELEM)MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[(TELEM)MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if (pMem != NULL)
		delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / 32); 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (BIT_32 >> (n % 32)); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return (BitLen);
}

void TBitField::SetBit(const int n) // установить бит
{
	int		i;
	TELEM	mask;

	if (n < 0 || n > BitLen)
		throw exception("Error: Negative index bit.");
	i = GetMemIndex(n);		// определяем номер октета.
	mask = GetMemMask(n);	// получение маски.
	pMem[i] = pMem[i] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int		i;
	TELEM	mask;

	if (n < 0 || n > BitLen)
		throw exception("Error: Negative index bit.");
	i = GetMemIndex(n);		// определяем номер октета.
	mask = GetMemMask(n);	// получение маски.
	pMem[i] = pMem[i] & ~mask;
}

/*
** Возвращяет 0 или 1 бита под номером n.
*/
int TBitField::GetBit(const int n) const // получить значение бита
{
	int		i;
	int		len;
	TELEM	temp;
	TELEM	mask;

	len = 0;
	if (n < 0 || n > BitLen)
		throw exception("Error: Negative index bit.");
	i = GetMemIndex(n);		// определяем номер октета.
	mask = GetMemMask(n);	// получение маски.
	temp = pMem[i] & mask;
	if (temp != 0)
		return (1);
	else
		return (0);
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (bf == *this)
		return (*this);
	BitLen = bf.BitLen;;
	MemLen = bf.MemLen;;
	if (pMem != NULL)
		delete[] pMem;
	pMem = new TELEM[(TELEM)MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return (*this);
}


bool TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	if (MemLen != bf.MemLen)
		return false;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return false;
	return true;
}


bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

// Объединяем множества
TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len;

	if (BitLen > bf.BitLen)
		len = BitLen;
	else
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return (temp);
}

// Пересечение множеств
TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len;

	if (BitLen > bf.BitLen)
		len = BitLen;
	else
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
	TBitField temp(*this);
	for (int i = 0; i < BitLen; i++)
		if (temp.GetBit(i))
			temp.ClrBit(i);
		else
			temp.SetBit(i);
	return (temp);
}

// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char	ch;
	string	st;

	for (int i = 0; 21; i++)
	{
		cout << "Enter 0 or 1 and press enter." << endl;
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i);
		else if (ch == '1')
			bf.SetBit(i);
		else
			break;
		st += ch;
		cout << st << endl;
	}
	return (istr);
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
		ostr << std::bitset<sizeof(bf.pMem[i])* CHAR_BIT>(bf.pMem[i]) << " ";
	cout << endl;
	return (ostr);
}
