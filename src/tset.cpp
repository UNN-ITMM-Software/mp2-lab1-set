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
TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
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
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return(*this);
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) {
        return 1;
    }
    else
        return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) {
        return 0;
    }
    else
        return 1;
}

TSet TSet::operator+(const TSet& s) // объединение
{

    if (MaxPower > s.MaxPower)
    {
        TBitField tmp(MaxPower);
        tmp = BitField | s.BitField;
        TSet res(tmp);
        return res;
    }
    else
    {
        TBitField tmp(s.MaxPower);
        tmp = BitField | s.BitField;
        TSet res(tmp);
        return res;
    }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TBitField t(MaxPower);
    t = BitField;
    t.SetBit(Elem);
    TSet res(t);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TBitField t(MaxPower);
    t = BitField;
    t.ClrBit(Elem);
    TSet res(t);
    return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TBitField t(MaxPower);
    t = BitField & s.BitField;
    TSet res(t);
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    return ~BitField;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int num;
    char st;
    do {
        istr >> st;
    } while (st != '{');
    do {
        istr >> num;
        s.InsElem(num);
        do {
            istr >> st;
        } while (st != ',' && st != '}');
    } while (st != '}');
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << "{";
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << ",";
        }
    }
    return ostr;
}


