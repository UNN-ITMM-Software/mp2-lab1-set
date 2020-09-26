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
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return *this;
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

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return false;
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return true;
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tempSet(MaxPower);
    tempSet.BitField = BitField | s.BitField;
    tempSet.MaxPower = tempSet.BitField.GetLength();
    return tempSet;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tempSet(*this);
    tempSet.BitField.SetBit(Elem);
    return tempSet;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tempSet(*this);
    tempSet.BitField.ClrBit(Elem);
    return tempSet;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tempSet(MaxPower);
    tempSet.BitField = this->BitField & s.BitField;
    tempSet.MaxPower = tempSet.BitField.GetLength();
    return tempSet;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tempSet(*this);
    tempSet.BitField.operator~();
    return tempSet;
}

// перегрузка ввода/вывода

void InsElem(TSet& s, const int Elem)
{
    s.InsElem(Elem);
}

void DelElem(TSet& s, const int Elem)
{
    s.DelElem(Elem);
}

TSet create(const int n)
{
    TSet tempSet(n);
    return tempSet;
}

TSet up(TSet& s, const int n)
{
    TSet tempSet(s.GetMaxPower() + n);
    tempSet = tempSet + s;
    return tempSet;
}

TSet low(TSet& s, const int n)
{
    TSet tempSet(s.GetMaxPower() - n);
    for (int i = 0; i < tempSet.GetMaxPower(); i++)
        if (s.IsMember(i))
            tempSet.InsElem(i);
    return tempSet;
}

istream &operator>>(istream &istr, TSet &s) // ввод
{
    map <string, void (*)(TSet&, int)> commands_V_TI =
    {
        {"ADD", InsElem}, {"INS", InsElem}, {"INSERT", InsElem},
        {"DEL", DelElem}, {"RMV", DelElem}, {"DELETE", DelElem}, {"REMOVE", DelElem}
    };
    map <string, TSet(*)(int)> commands_T_I =
    {
        {"NEW", create}, {"CRT", create}, {"CREATE", create}
    };
    map <string, TSet(*)(TSet&, int)> commands_T_TI =
    {
        {"UP", up},
        {"LOW", low}
    };
    map <string, int> throws =
    {
        {"EXIT", -1}, {"CLOSE", -1}
    };
    string command;
    istr >> command;
    transform(command.begin(), command.end(), command.begin(), toupper);
    if (throws.count(command) != 0)
    {
        throw throws[command];
    }
    if (command == "FILL")
    {
        char symbol;
        int number;
        istr >> symbol;
        s = (commands_T_I["NEW"])(s.MaxPower);
        while (symbol != '}')
        {
            istr >> number;
            (commands_V_TI["ADD"])(s, number);
            istr >> symbol;
        }
        return istr;
    }
    int number;
    istr >> number;
    if (commands_V_TI.count(command) == 0)
    {
        if (commands_T_I.count(command) == 0)
        {
            if (commands_T_TI.count(command) == 0)
            {
                throw "Invalid the command";
            }
            else
                s = (commands_T_TI[command])(s, number);
        }
        else
            s = (commands_T_I[command])(number);
    }
    else
        (commands_V_TI[command])(s, number);
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << '{';
    int j = 0;
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
        {
            ostr << i;
            j = i;
            break;
        }
    for (int i = j + 1; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << ", " << i;
    ostr << '}';
    return ostr;
}
