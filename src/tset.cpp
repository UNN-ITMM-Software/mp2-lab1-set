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
    BitField = TBitField(s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    TBitField temp(this->BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem) == 0 ? 0 : 1;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw ("The element is out of bounds of the set");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw ("The element is out of bounds of the set");
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
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int length;
    if (MaxPower > s.MaxPower)
        length = MaxPower;
    else
        length = s.MaxPower;
    TSet res(length);
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower) throw ("The element is out of bounds of the set");
    BitField.SetBit(Elem);
    TSet res(BitField);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower) throw ("The element is out of bounds of the set");
    BitField.ClrBit(Elem);
    TSet res(BitField);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(BitField & s.BitField);
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(~BitField);
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int temp;
    char ty;
    for (int i = 0; i < s.GetMaxPower(); i++) {
        s.DelElem(i);
    }
    do {
        istr >> ty;
    } while (ty != '{');
    istr >> temp;
    s.InsElem(temp);
    do {
        do {
            istr >> ty;
        } while ((ty != ',') && (ty != '}'));
        if (ty == ',') istr >> temp;
        s.InsElem(temp);
    } while (ty != '}');

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int a = s.GetMaxPower();
    ostr << '{';

    int i = 0;
    while (i < a) {
        if (s.IsMember(i)) {
            ostr << i;
            break;
        }
        i++;
    }
    i++;
    while (i < a) {
        if (s.IsMember(i)) ostr << ',' << i;
        i++;
    }

    ostr << '}';

    return ostr;
}
