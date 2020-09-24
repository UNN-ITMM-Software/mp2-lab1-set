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
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
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
    if (Elem <= MaxPower && Elem >= 0)
    {
        BitField.SetBit(Elem);
    }
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (IsMember(Elem))
    {
        BitField.ClrBit(Elem);
    }
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
    if (BitField == s.BitField)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (BitField != s.BitField)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet res(BitField.GetLength());
    res = BitField | s.BitField;
    res.MaxPower = res.BitField.GetLength();
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    
    if (Elem <= MaxPower && Elem > 0)
    {
        TSet res(Elem);
        res.BitField.SetBit(Elem);
        return res;
    }
    else
    {
        throw exception("error");
    }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(BitField);
    res.BitField.ClrBit(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(BitField.GetLength());
    res = BitField & s.BitField;
    res.MaxPower = res.BitField.GetLength();
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(BitField.GetLength());
    res = *this;
    res.BitField = ~res.BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    std::string str;
    istr >> str;
    TSet tmp(str.size());
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            tmp.BitField.SetBit(i);
        }
        else
        {
            tmp.BitField.ClrBit(i);
        }
    }
    s = tmp;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.BitField.GetLength(); i++)
    {
        if (s.BitField.GetBit(i))
        {
            ostr << "1";
        }
        else
        {
            ostr << "0";
        }
    }
    return ostr;
}
