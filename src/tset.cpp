// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
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

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = BitField.GetLength();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField.GetLength() != s.BitField.GetLength()) return 0;
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return 1 - ((*this) == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(0);
	temp.BitField = BitField | s.BitField;
	temp.MaxPower = temp.BitField.GetLength();
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet temp(*this);
	temp.BitField.SetBit(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet temp(*this);
	temp.BitField.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(0);
	temp.BitField = BitField & s.BitField;
	temp.MaxPower = temp.BitField.GetLength();
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(*this);
	temp.BitField = ~temp.BitField;
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i)) ostr << i << ' ';
	}
	return ostr;
}
