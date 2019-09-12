// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0)
		throw Elem;
	return BitField.GetBit(Elem);
   }

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0)
		throw Elem;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0)
		throw Elem;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;	
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 1;
		else
			return 0;
	}
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int k = 1;
	if (MaxPower == s.MaxPower)
	{
		if (BitField != s.BitField)
			k = 1;
		else
			k = 0;
	}
	return k;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp(MaxPower);
	tmp = BitField | s.BitField;
	TSet tmp_set(tmp);
	return tmp_set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
		throw Elem;
	else
	{
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
		throw Elem;
	else
	{
		TSet tmp = *this;
		tmp.DelElem(Elem);
		return tmp;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp(MaxPower);
	tmp = BitField & s.BitField;
	TSet tmp_set(tmp);
	return tmp_set;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(MaxPower);
	tmp.BitField = ~BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	s.MaxPower = s.BitField.GetLength();
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
