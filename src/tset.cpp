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
TSet::TSet(const TSet &s) 
{

	(*this).BitField = s.BitField;
	(*this).MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) 
{

	(*this).BitField = bf;
	(*this).MaxPower = bf.GetMemLen() * sizeof(TELEM) * 8;
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
	TSet tempor_2(*this);
	tempor_2.BitField = (this->BitField) | s.BitField;
	if ((tempor_2.MaxPower) < s.GetMaxPower()) tempor_2.MaxPower = s.GetMaxPower();
	return(tempor_2);
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
	TSet tempor_2(*this);
	tempor_2.BitField = BitField & s.BitField;
	if ((tempor_2.MaxPower) < s.GetMaxPower()) tempor_2.MaxPower = s.GetMaxPower();
	return(tempor_2);
}

TSet TSet::operator~(void) // дополнение
{
	TSet tempor_2(*this);
	tempor_2.BitField = ~tempor_2.BitField;
	return(tempor_2);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	TSet q(s.MaxPower);
	//char a;
	int num, n;
	cout << "Number of elements: ";
	istr >> n;
	//istr >> a;
	for (int i = 0; i < n; i++)
	{
		istr >> num;
		q.InsElem(num);
	}
	s = q;
	//istr >> a;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.MaxPower << endl;
	ostr << "{";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i)) {
			ostr << i;
			if (i != s.BitField.GetLength() - 1)
				ostr << " ";
		}

	}
	ostr << "}";
	return ostr;
}
