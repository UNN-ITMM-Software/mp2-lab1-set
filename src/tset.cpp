// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp) //комментарий 
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
	TBitField result(BitField);
	return result;
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
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return BitField | s.BitField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > BitField.GetLength())
	{
		throw ("Elem > Length");
	}
	TBitField temp(MaxPower);
	temp.SetBit(Elem);
	TSet result(BitField | temp);
	return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > BitField.GetLength())
	{
		throw ("Elem > Length");
	}
	TBitField temp(MaxPower);
	temp.SetBit(Elem);
	TSet result(BitField & temp);
	return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char res;
	unsigned int tmp;
	do
	{
		istr >> res;
	} while (res != '{');
	do
	{
		istr >> tmp;
		s.InsElem(tmp);
		do
		{
			istr >> res;
		} while ((res != ',') && (res != '}'));
	} while (res != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << '{';
	for (register int i = 1; i < s.MaxPower; i++)
		if (s.IsMember(i))
		{
			ostr << ' ' << i << ',';
		}
	ostr << '}';
	return ostr;
}
