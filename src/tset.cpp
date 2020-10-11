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
TSet::TSet(const TSet& s)
{
	(*this).BitField = s.BitField;
	(*this).MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf)
{
	(*this).BitField=bf;
	(*this).MaxPower = bf.GetLength();
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
	TSet a(s);
	
	a.BitField = ((*this).BitField | s.BitField);
	if ((a.MaxPower) < MaxPower) a.MaxPower = MaxPower;
	

	return(a);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet a(*this);
		a.BitField.SetBit(Elem);	
		return(a);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet a(*this);

	a.BitField.ClrBit(Elem);
	return(a);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet a(s);
	a.BitField=(*this).BitField & s.BitField;
	if ((this->MaxPower) < s.GetMaxPower()) MaxPower = s.GetMaxPower();
	return(a);
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(*this);
	a.BitField=~BitField;
	return(a);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n;
	int p;
	istr >> n;
	TSet a(n+1);
	char i;
	istr >> i;
	for (int i = 0; i < n; i++)
	{
		istr >> p;
		a.InsElem(p);
	}
	
	s.BitField = a.BitField;
	s.MaxPower = a.MaxPower;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.MaxPower << endl;
	cout << "{";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i))
			cout << i << ", ";
		
	}
	cout << "}" <<endl;
	return ostr;
}
