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
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return *this;
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
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return false;
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return true;
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tempSet(MaxPower);
    tempSet.BitField = BitField | s.BitField;
    tempSet.MaxPower = tempSet.BitField.GetLength();
    return tempSet;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tempSet(*this);
    tempSet.BitField.SetBit(Elem);
    return tempSet;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tempSet(*this);
    tempSet.BitField.ClrBit(Elem);
    return tempSet;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tempSet(MaxPower);
    tempSet.BitField = this->BitField & s.BitField;
    tempSet.MaxPower = tempSet.BitField.GetLength();
    return tempSet;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tempSet(*this);
    tempSet.BitField.operator~();
    return tempSet;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    char symbol;
    int number;
    istr >> symbol;
    s = TSet(s.MaxPower);
    while (symbol != '}')
    {
        istr >> number;
        s.InsElem(number);
        istr >> symbol;
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << '{';
    int j = 0;
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
        {
            ostr << i;
            j = i;
            break;
        }
    for (int i = j + 1; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << ", " << i;
    ostr << '}';
    return ostr;
}
