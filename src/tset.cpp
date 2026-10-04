// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "../include/tset.h"
#include <stdexcept>

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField() { return BitField; }

int TSet::GetMaxPower(void) const { return MaxPower; }

int TSet::IsMember(const int Elem) const { return BitField.GetBit(Elem); }
void TSet::InsElem(const int Elem) { BitField.SetBit(Elem); }
void TSet::DelElem(const int Elem) { BitField.ClrBit(Elem); }

int TSet::operator==(const TSet &s) const { return MaxPower == s.MaxPower && BitField == s.BitField; }
int TSet::operator!=(const TSet &s) const { return !(*this == s); }

TSet& TSet::operator=(const TSet &s) {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

TSet TSet::operator+(const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) throw std::out_of_range("Element out of range");
    TSet t(*this);
    t.InsElem(Elem);
    return t;
}

TSet TSet::operator-(const int Elem) {
    TSet t(*this);
    t.DelElem(Elem);
    return t;
}

TSet TSet::operator+(const TSet &s) {
    int maxLen = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
    TBitField resField = BitField | s.BitField;
    TSet res(resField);
    res.MaxPower = maxLen;
    return res;
}

TSet TSet::operator*(const TSet &s) {
    int maxLen = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
    TBitField resField = BitField & s.BitField;
    TSet res(resField);
    res.MaxPower = maxLen;
    return res;
}

TSet TSet::operator~(void) { return TSet(~BitField); }

istream& operator>>(istream &is, TSet &s) {
    char c;
    for (int i = 0; i < s.MaxPower; i++) { is >> c; if (c == '1') s.InsElem(i); else s.DelElem(i); }
    return is;
}

ostream& operator<<(ostream &os, const TSet &s) {
    for (int i = 0; i < s.MaxPower; i++) os << s.IsMember(i);
    return os;
}