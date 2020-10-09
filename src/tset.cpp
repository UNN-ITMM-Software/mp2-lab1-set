// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

int TSet::Foo(int length) {
    int tmp = 0;
    cout << "{";
    for (int i = 1; i <= length; i++) {
        if (IsMember(i)) {
            if (i % 4 == 0) {
                if (tmp > 0) cout << ", ";
                tmp++;
                cout << i * i;
            }
        }
           
    }
    cout << "}";
    return 0;
}

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    this->MaxPower = (bf.GetMemLen() * sizeof(TELEM) * 8);
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
    if (this != &s) {
        this->BitField = s.BitField;
        this->MaxPower = s.MaxPower;
        return *this;
    }
    else return *this;
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
    TSet tmp(MaxPower);
    tmp = *this;
    if (tmp.MaxPower < s.MaxPower)
        tmp.MaxPower = s.MaxPower;
    tmp.BitField = tmp.BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp(MaxPower);
    tmp = *this;
    tmp.BitField.SetBit(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp(MaxPower);
    tmp = *this;
    tmp.BitField.ClrBit(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet tmp(MaxPower);
    tmp = *this;
    if (tmp.MaxPower < s.MaxPower)
        tmp.MaxPower = s.MaxPower;
    tmp.BitField = tmp.BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{ 
    TSet tmp(MaxPower);
    tmp = *this;
    tmp.BitField = ~tmp.BitField;
    return tmp;
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
    ostr << "{";
    int tmp = 0;
    for (int i = 0; i < s.BitField.GetLength(); i++) {
        if (s.BitField.GetBit(i)) {
            if (tmp > 0) ostr << ", ";
            ostr << i;
            tmp++;
        }
    }
    ostr << "}";
    return ostr;
}