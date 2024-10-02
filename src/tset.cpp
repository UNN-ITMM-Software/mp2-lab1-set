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

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

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
    if (Elem < 0 || Elem >= MaxPower)
        throw "Element out of bounds";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Element out of bounds";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Element out of bounds";
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int maxPower = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
    TSet temp(maxPower);
    temp.BitField = BitField | s.BitField;
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Element out of bounds";
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "Element out of bounds";
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int maxSize = max(MaxPower, s.MaxPower);  // Результирующее множество должно быть максимального размера
    TSet result(maxSize);

    int minSize = min(MaxPower, s.MaxPower);  // Пересекаем по минимальному размеру
    for (int i = 0; i < minSize; i++) {
        if (IsMember(i) && s.IsMember(i)) {
            result.InsElem(i);
        }
    }

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);

    for (int i = 0; i < MaxPower; i++) {
        if (!IsMember(i)) {
            result.InsElem(i);  // Включаем элемент, если он отсутствует в исходном множестве
        }
        else {
            result.DelElem(i);  // Убираем элемент, если он присутствует
        }
    }

    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int temp;
    for (int i = 0; i < s.MaxPower; i++)
    {
        istr >> temp;
        if (temp == 1)
            s.InsElem(i);
        else
            s.DelElem(i);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        ostr << s.IsMember(i) << " ";
    }
    return ostr;
}
