// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp),MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s):BitField(0)
{
	(*this).BitField = s.BitField;
	(*this).MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(0)
{
	(*this).BitField=bf;
	(*this).MaxPower = bf.GetMemLen()*sizeof(TELEM)*8;
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
	return(BitField.GetBit(Elem));
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
	(*this).BitField = s.BitField;
	(this->MaxPower) = s.MaxPower;
	return(*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return(((*this).BitField == s.BitField) && ((this->MaxPower) == s.MaxPower));
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(((*this).BitField == s.BitField) && ((this->MaxPower) == s.MaxPower));
}

TSet TSet::operator+(const TSet &s) // объединение
{
	(this->BitField) | s.BitField;
	if ((this->MaxPower) < s.GetMaxPower()) MaxPower = s.GetMaxPower();

	return(*this);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
		BitField.SetBit(Elem);	
		return(*this);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField.ClrBit(Elem);
	return(*this);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	BitField & s.BitField;
	if ((this->MaxPower) < s.GetMaxPower()) MaxPower = s.GetMaxPower();
	return(*this);
}

TSet TSet::operator~(void) // дополнение
{
	~BitField;
	return(*this);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n;
	istr >> n;
	TSet a(n);
	istr >> a.BitField;
	s.BitField = a.BitField;
	s.MaxPower = a.MaxPower;
	return istr;
}

ostream& operator<<(ostream &ostr,  TSet &s) // вывод
{
	ostr << s.MaxPower << endl;
	ostr << s.BitField;
	return ostr;
}
