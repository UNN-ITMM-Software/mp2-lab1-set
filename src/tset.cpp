// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp),BitField(MaxPower)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
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
	if ((Elem < 0) || (Elem > MaxPower)) {
		throw runtime_error("Improbable index!");
	}
	if (BitField.GetBit(Elem)) {
		return true;
	}
	return false;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower)) {
		throw runtime_error("Improbable index!");
	}
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower)) {
		throw runtime_error("Improbable index!");
	}
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
	if (MaxPower != s.MaxPower) {
		return false;
	}
	if (BitField != s.BitField) {
		return false;
	}
	return true;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower) {
		return true;
	}
	if (BitField != s.BitField) {
		return true;
	}
	return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(*this);
	tmp.InsElem(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(*this);
	tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
	tmp.BitField = BitField & s.BitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(*this);
	tmp.BitField = ~BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.MaxPower;
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.MaxPower << endl;
	ostr << s.BitField << endl;
	return ostr;
}
