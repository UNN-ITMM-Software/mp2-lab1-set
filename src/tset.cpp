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
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    TBitField a(BitField);
    return a;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem > MaxPower) {
        throw "error is member";
    }

    if (BitField.GetBit(Elem)) {
        return 1;
    }
    return 0;
    
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "error ins elem";
    }

    BitField.SetBit(Elem);
    
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "error del elen";
    }

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

    if (MaxPower != s.MaxPower || BitField != s.BitField) {
        return 0;
    }

   
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower || BitField != s.BitField) {
        return 1;
    }

    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int maxM = 0;

    if (MaxPower >= s.MaxPower) {
        maxM = MaxPower;
    }
    else {
        maxM = s.MaxPower;
    }

    TSet a(maxM);

    a.BitField = BitField | s.BitField;

    return a;
    
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    int maxM = 0;

    if (MaxPower >= Elem) {
        maxM = MaxPower;
    }
    else {
        maxM = Elem;
    }

    TSet a(maxM);

    
    a.BitField = BitField | a.BitField;
    a.BitField.SetBit(Elem);
    /*if (a.BitField.GetBit(Elem) == 0) {

        a.BitField.SetBit(Elem);
    }*/

    return a;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{

    int maxM = 0;

    if (MaxPower >= Elem) {
        maxM = MaxPower;
    }
    else {
        maxM = Elem;
    }

    TSet a(maxM);

    a.BitField = BitField | a.BitField;

    if (a.BitField.GetBit(Elem) != 0) {

        a.BitField.ClrBit(Elem);

    }

    return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{

    int maxM = 0;

    if (MaxPower >= s.MaxPower) {
        maxM = MaxPower;
    }
    else {
        maxM = s.MaxPower;
    }

    TSet a(maxM);

    a.BitField = BitField & s.BitField;

    return a;
    
}

TSet TSet::operator~(void) // дополнение
{
    TSet a(MaxPower);

    a.BitField = ~BitField;

    return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    s.MaxPower = s.BitField.GetLength();
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{   
    ostr << s.BitField << "\n";
    return ostr;
}
