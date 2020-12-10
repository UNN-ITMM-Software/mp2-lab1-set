// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <cstdlib>

TSet::TSet(int mp) : BitField(mp-1)
{
    if (mp < 0) throw - 1;
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
    MaxPower = bf.GetLength()+1;
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
    if (Elem < 0||Elem>=MaxPower) throw - 1;
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw - 1;
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw - 1;
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (MaxPower == s.MaxPower && BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (!(*this == s));
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower) throw - 1;
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower) throw - 1;
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(MaxPower>s.MaxPower?*this:s);
    res.BitField =BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int tmp;
    char ch;
    do {
        istr >> ch;
    } while (ch != '{');
    do {
        istr >> tmp;
        s.InsElem(tmp);
        do {
            istr >> ch;
        } while ((ch != ',') && ch != '}');
    } while (ch != '}');
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    int i, n;
    char ch = ' ';
    ostr << "{";
    n = s.GetMaxPower();
    for (i = 0; i < n; i++) {
        if (s.IsMember(i)) {
            ostr << ch << ' ' << i;
            ch = ',';
        }
    }
    ostr << "}";
    return ostr;
}

ifstream& operator>>(ifstream& istr, TSet& bf)
{
    int Elem;
    string str="$";
    do {
        istr >> str;
        if (str != "$") {
            Elem = atoi(str.c_str());
            bf.InsElem(Elem);
        }
    } while (str != "$");
    return istr;
}

ofstream& operator<<(ofstream& ofstr, TSet& bf)
{
    for (int i = 0; i < bf.MaxPower; i++) {
        if (bf.IsMember(i)) {
            ofstr << i<<' ';
        }
    }
    ofstr << '$';
    return ofstr;
}

TSet TSet::dividedByK(const int k) 
{
    TSet res(MaxPower);
    for (int i = 0; i < MaxPower; i += k) 
    {
        if (IsMember(i)) 
        {
            res.InsElem(i);
        }
    }
    return res;
}

void TSet::changeElem(const int Elem, const int n)
{
    if (Elem < 0 || Elem >= MaxPower) throw - 1;
    int val = IsMember(Elem);
    if (val) {
        InsElem(n);
        DelElem(Elem);
    }
}
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
