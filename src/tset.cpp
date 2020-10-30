// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <fstream>
#include <string>


void TSet::Add() {
    int comma = 0;
    int MaxOdd = -1;
    cout << "first array" << endl; // заполняем массив
    cout << "{";
    for (int i = 0; i < GetMaxPower(); i++) 
        if (IsMember(i)) {
            if (i % 2 == 1) MaxOdd = i;
            if (comma > 0) cout << ", ";
            comma++;
            cout << i;
        }
    cout << "}"<<endl;
    comma = 0;
   
    cout << "second array" << endl; // удаляем максимальное нечетное число и печатаем соседнием числа, если они не входят в первый массив
    cout << "{";
    for (int i = 0; i < GetMaxPower(); i++) 
        if (IsMember(i)){
            if (i == MaxOdd) {
                DelElem(MaxOdd);
                if (!IsMember(MaxOdd - 1)) cout <<", " <<MaxOdd - 1;
                if (!IsMember(MaxOdd + 1)) cout << ", " <<MaxOdd + 1;
            }
                if (comma > 0 && i!=MaxOdd) cout << ", ";
                comma++;
               if(i!=MaxOdd) cout << i;
            
        }
    cout << "}" << endl;
   
}


void TSet::Infile() {
    string path = "File.txt";
    ifstream in;
    in.open(path);
    if (!in.is_open())
        throw logic_error("Infile open error");
    else
        cout << "file open" << endl;
    char tmp;
    while (in.get(tmp))
        cout << tmp;
    in.close();
}

void TSet::Outfile() {
    string path = "File.txt";
    ofstream out;
    out.open(path);
    int comma = 0;
    out << "{";
    if (!out.is_open())
        throw logic_error("Outfile open error");
    else
        for (int i = 0; i < GetMaxPower(); i++)
            if (IsMember(i)) {
                if (comma > 0) out << ", ";
                comma++;
                out << i;
            }
    out << "}"<<endl;
    out.close();
}


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
    cout << "}"<<endl;
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


