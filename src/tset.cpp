// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include <iostream>
#include <algorithm>
#include "tset.h"
#include <string>

TSet::TSet(int mp) :BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) :BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) :BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() {
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	if (!(*this == s))
	{
		BitField = s.BitField;
		MaxPower = s.MaxPower;
		return *this;
	}
	else return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
	TSet tField(std::max(MaxPower, s.MaxPower));
	tField.BitField = BitField | s.BitField;
	return tField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tField(*this);
	tField.BitField.SetBit(Elem);
	return tField;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tField(*this);
	tField.BitField.ClrBit(Elem);
	return tField;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet tField(max(s.MaxPower, MaxPower));
	tField.BitField = BitField & s.BitField;
	return tField;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tField(MaxPower);
	tField.BitField = ~BitField;
	return tField;
}

void TSet::swap(int n, int new_elem)
{
	if (n == new_elem) {}			// Ecli nomer elementa = new element -> nichego ne delayem
	else {
		if ((n < 0) || (new_elem < 0 || new_elem > MaxPower))
		{
			throw std::out_of_range("Input error: invalide value of tset in swap");
		}
		else {
			int tmp = 0;
			int count = 0;
			for (int i = 0; count < n; i++)
			{
				if (BitField.GetBit(i))
				{
					tmp = i;
					count++;
				}
			}
			DelElem(tmp);
			InsElem(new_elem);
		}
	}
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	string text;
	string tmp;
	getline(istr, tmp);
	int space = 1;
	for (int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] != '{' && tmp[i] != '}' && tmp[i] != ',')
		{
			text += tmp[i];									// Chistyui text
		}
		if (tmp[i] == ' ')
		{
			space++;
		}
	}

	string* delSpace = new string[space];
	int index = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] != ' ')
		{
			delSpace[index] += text[i];
		}
		else index++;
	}

	int* textConvertInt = new int[space];

	int maxElement = 0;
	TSet res(maxElement + 1);
	for (int i = 0; i < space; i++)
	{
		res.InsElem(textConvertInt[i]);
	}

	delete[] delSpace;
	delete[] textConvertInt;

	s = res;

	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	cout << "{";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i))
		{
			if (i == s.BitField.GetLength() - 1)
			{
				ostr << i;
			}
			else
			{
				ostr << i;
				ostr << ", ";
			}
		}
	}
	cout << "}";

	return ostr;
}