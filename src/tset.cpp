// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) :BitField(mp), MaxPower(mp)
{

}

// конструктор копирования
TSet::TSet(const TSet& s) :BitField(s.BitField), MaxPower(s.MaxPower)
{

}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
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

int TSet::IsMember(const int Elem) const // элемент множества
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
    if (this == &s)
    {
        return *this;
    }

    (*this).BitField = s.BitField;
    (this->MaxPower) = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    BitField.SetBit(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    BitField.ClrBit(Elem);
    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int temp;
    istr >> temp;
    TSet q(temp);
    istr >> q.BitField;
    s.BitField = move(q.BitField);
    s.MaxPower = q.MaxPower;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.MaxPower << endl;
    ostr << s.BitField;
    return ostr;
}

