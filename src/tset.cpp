// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) {
    if (mp <= 0) throw out_of_range("Length should be positive");
    this->MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField) {
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf) {
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField() {
    TBitField tmp(this->BitField);
    return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet &TSet::operator=(const TSet &s) // присваивание
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (this->BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (this->BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(this->BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp(this->BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp(this->BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(this->BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(~this->BitField);
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    // { 1 3 4 5} - формат
    int elem;
    char ch;
    do { istr >> ch; } while (ch != '{');
    while(true){
        istr>>elem;
        s.InsElem(elem);
        do{ istr >> ch;} while (ch != ' ' && ch != '}');
        if(ch == '}') break;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TSet &s) // вывод
{
    // { 1 3 4 5} - формат
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.BitField.GetBit(i)) {
            ostr << i << " ";
        }
    }
    ostr << " }\n";
    return ostr;
}
