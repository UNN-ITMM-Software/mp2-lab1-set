// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(0)
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(0)
{
    this->BitField = bf;
    this->MaxPower = ((bf.GetLength() / (sizeof(TELEM) * 8)) + 1) * (sizeof(TELEM) * 8);
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
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    this->BitField = s.BitField;
    this->MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return (this->MaxPower == s.MaxPower && this->BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return (this->MaxPower != s.MaxPower || this->BitField != s.BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    if (this->MaxPower < s.MaxPower)
        MaxPower = s.MaxPower;
    this->BitField | s.BitField;
    return *this;
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
    if ((this->MaxPower) < s.MaxPower)
        MaxPower = s.MaxPower;
    this->BitField& s.BitField;
    return *this;
}

TSet TSet::operator~(void) // дополнение
{
    this->BitField = ~BitField;
    return *this;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int tmp;
    istr >> tmp;
    TSet t(tmp);
    char ch;
    int ind;
    istr >> ch;
    for (int i = 0; i < ch; i++) {
        istr >> ind;
        t.InsElem(ind);
    }
    s = t;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.MaxPower << endl;
    for (int i = 0; i < s.BitField.GetLength(); i++) {
        if (s.BitField.GetBit(i))
            ostr << i;
    }
    return ostr;
}
