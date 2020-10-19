// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <conio.h>



TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw std::logic_error("Input error: invalide value of lenght int in constructor");
	}
	BitLen = len;
	MemLen = (len + 15) >> sizeof(TELEM);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
	//}
	//else
	//{
	//	BitLen = 0;
	//	MemLen = 0;
	//	pMem = NULL;
	//}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw std::logic_error("Input error: invalide value of lenght int in index");
	int temp = n >> sizeof(TELEM);
	return temp;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw std::logic_error("Input error: invalide value of lenght int in mask");
	TELEM temp = n & 15;
	return 1 << temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw std::logic_error("Input error: invalide value of lenght int in create bit");

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw std::logic_error("Input error: invalide value of lenght int in clear bit");

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw std::logic_error("Input error: invalide value of lenght int in get bit");

	return pMem[GetMemIndex(n)] & GetMemMask(n);

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	TELEM test;
	BitLen = bf.BitLen;

	if(MemLen!=bf.MemLen)
		if (pMem != NULL)
		{
			delete[]pMem;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
	
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
			test = pMem[i];
			test = bf.pMem[i];
			test = pMem[i];
		}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen))
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen))
		return 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				return 1;
				break;
			}

	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i<bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i<bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int i, len = BitLen;
	TELEM test;
	TBitField temp(len);
	for (i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
			temp.SetBit(i);

		//temp.pMem[i] = ~pMem[i];

	}
	return temp;
}

// ввод/вывод

istream& operator >> (istream& istr, TBitField& bf) // ввод
{
	char c;
	int res = 0;
	int i = 3;
	bool f = true;
	int j = 0;

	do
	{
		try
		{
			c = _getche();
			if (c == '\x1b')
				break;
			if (c == ' ')
			{
				cout << endl;
				res /= pow(10, i);
				if (res < bf.BitLen)
					bf.SetBit(res);
				res = 0;
				i = 3;
			}
			else
			{
				if (((c - 48) < 10) && ((c - 48) > (-1)) && (i > 0))
				{
					res += (c - 48) * pow(10, i - 1);
					i--;
					if (i == 0)
					{
						cout << endl;
						if (res < bf.BitLen)
							bf.SetBit(res);
						res = 0;
						i = 3;
					}
				}
				else
					throw "You used a character that is not equal to the characters - 0,1,2,3,4,5,6,7,8,9";
			}
		}
		catch (const char* exception)
		{
			cout << "\nERROR: " << exception << endl;
			f = false;
		}
	} while (f);

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		cout << bf.GetBit(i);
	return ostr;
}


//-----------------------------additional task---------------------

//1
void TBitField::all_elem_degree_of_number(const int n)
{
	if ((n > BitLen) ||( n < 2))
		throw std::logic_error("Input error : invalide value of lenght int in degree of numb");

	int temp = n;
	
	do
	{
		if (GetBit(temp) > 0)
		{
			cout << temp<<" ";
		}

		temp *= n;

	} while (temp < BitLen);

	cout << endl;
}

//2
void TBitField::all_elem_multiple(const int n)
{
	if ((n > BitLen) || (n < 1))
		throw std::logic_error("Input error : invalide value of lenght int in degree of numb");


	int temp = n;

	do
	{
		if (GetBit(temp) > 0)
		{
			cout << temp << " ";
		}
		temp += n;
	} while (temp < BitLen);

	cout << endl;
}

//3

int TBitField::specified_number(const int n)
{	
	if ((n > BitLen) || (n < 0))
		throw std::logic_error("Input error : invalide value of lenght int in degree of numb");

	if (GetBit(n) == 0)
		return 0;

	int summa = 0;

	for (int i = 0; i < n; i++)
	{
		if(GetBit(i)!=0)
			summa ++;
	}

	return ++summa;
}

//--------------------------------------------------------------