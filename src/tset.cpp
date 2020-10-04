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
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField t(BitField);
	return t;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem > MaxPower)
		return 0;
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
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	if (MaxPower == s.GetMaxPower() && BitField == s.BitField)
		return 1;
	else
		return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if (MaxPower == s.GetMaxPower() && BitField == s.BitField)
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	int tmpsize = (MaxPower >= s.GetMaxPower()) ? MaxPower : s.GetMaxPower();
	TSet tmp(tmpsize);
	for (int i = 0; i < MaxPower; i++)
		if (IsMember(i))
			tmp.InsElem(i);
	for (int i = 0; i < s.GetMaxPower(); ++i)
		if (s.IsMember(i))
			tmp.InsElem(i);
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	int tmpsize = (MaxPower >= Elem) ? MaxPower : Elem;
	TSet tmp(tmpsize);
	for (int i = 0; i < MaxPower; i++)
		if (IsMember(i))
			tmp.InsElem(i);
	tmp.InsElem(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(*this);
	if (MaxPower < Elem)
		tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	if (MaxPower >= s.GetMaxPower()) {
		TSet tmp(MaxPower);
		for (int i = 0; i < s.GetMaxPower(); i++) {
			if (IsMember(i) == 1 && s.IsMember(i) == 1)
				tmp.InsElem(i);
		}
		return tmp;
	}
	else {
		TSet tmp(s.GetMaxPower());
		for (int i = 0; i < MaxPower; i++) {
			if (IsMember(i) == 1 && s.IsMember(i) == 1)
				tmp.InsElem(i);
		}
		return tmp;
	}
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(MaxPower);
	for (int i = 0; i < MaxPower; ++i)
		if (!IsMember(i))
			tmp.InsElem(i);
	return tmp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	ostr << s.BitField;
	return ostr;
}