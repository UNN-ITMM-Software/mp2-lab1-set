// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

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

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this != &s)
    {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

bool TSet::operator!=(const TSet& s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~BitField);
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    TSet result(s.MaxPower);
    char ch;
    if (!(istr >> ch)) return istr;
    if (ch != '{') { istr.setstate(ios::failbit); return istr; }
    istr >> ws;
    if (istr.peek() == '}') { istr.get(); s = result; return istr; }
    while (istr)
    {
        int elem;
        if (!(istr >> elem)) return istr;
        if (elem < 0 || elem >= s.MaxPower)
        {
            istr.setstate(ios::failbit); return istr;
        }
        result.InsElem(elem);
        istr >> ws;
        if (istr.peek() == '}') { istr.get(); s = result; return istr; }
        if (istr.peek() == ',') istr.get();
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s)
{
    ostr << '{';
    bool first = true;
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
        {
            if (!first) ostr << ", ";
            ostr << i;
            first = false;
        }
    return ostr << '}';
}
#include <random>
void TSet::GenerateRandom(TSet& s) {
    TBitField bf(s.GetMaxPower());
    bf.GenerateRandom(bf);
    s = TSet(bf);
}