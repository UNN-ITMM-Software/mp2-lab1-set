#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
}

TSet::operator TBitField()
{
	return TBitField(0);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return 0;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(0);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	return 0;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	return 0;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(0);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(0);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
