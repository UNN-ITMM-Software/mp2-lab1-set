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

TSet::TSet(int mp) : BitField(1)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(1)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(1)
{
}

TSet::operator TBitField()
{
    return FAKE_BITFIELD;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return FAKE_INT;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return FAKE_INT;
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
    return FAKE_SET;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return FAKE_INT;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return FAKE_INT;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return FAKE_SET;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    return FAKE_SET;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    return FAKE_SET;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return FAKE_SET;
}

TSet TSet::operator~(void) // дополнение
{
    return FAKE_SET;
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
