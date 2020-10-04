#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{

}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField (s.BitField), MaxPower (s.MaxPower)
{

}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return *this;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества
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
    BitField = s.BitField;
    MaxPower = s.GetMaxPower();
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    BitField.SetBit(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    BitField.ClrBit(Elem);
    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    ~BitField;
    return(*this);
}


istream& operator>>(istream& istr, TSet& s) // ввод
{
    int n;
    istr >> n;
    TSet q(n);
    istr >> q.BitField;
    s.BitField = move(q.BitField);
    s.MaxPower = q.MaxPower;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.MaxPower << endl;
    ostr << s.BitField;
    return ostr;
}
