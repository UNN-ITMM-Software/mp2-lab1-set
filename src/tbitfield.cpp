// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) throw -1;
    BitLen = len;
    MemLen = (len + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen)) throw "Invalid the number";
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen)) throw "Invalid the number";
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&*this == &bf) return *this;
    if (BitLen != bf.BitLen)
    {
        if (MemLen != bf.MemLen)
        {
            delete[]pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        BitLen = bf.BitLen;
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen > bf.BitLen)
    {
        for (int i = 0; i < bf.MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        for (int i = bf.MemLen; i < MemLen; i++)
            if (pMem[i] != 0)
                return 0;
    }
    else
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        for (int i = MemLen; i < bf.MemLen; i++)
            if (bf.pMem[i] != 0)
                return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen > bf.BitLen)
    {
        TBitField tempBF(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tempBF.pMem[i] |= bf.pMem[i];
        return tempBF;
    }
    else
    {
        TBitField tempBF(bf);
        for (int i = 0; i < MemLen; i++)
            tempBF.pMem[i] |= pMem[i];
        return tempBF;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen < bf.BitLen)
    {
        TBitField tempBF(bf);
        for (int i = 0; i < MemLen; i++)
            tempBF.pMem[i] &= pMem[i];
        return tempBF;
    }
    else
    {
        TBitField tempBF(*this);
        for (int i = 0; i < bf.MemLen; i++)
            tempBF.pMem[i] &= bf.pMem[i];
        return tempBF;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    int temp = BitLen / (sizeof(TELEM) * 8);
    for (int i = 0; i < temp; i++)
        pMem[i] = ~pMem[i];
    TELEM tempByte = 0;
    pMem[temp] = ~pMem[temp];
    for (int i = 0; i < BitLen % (sizeof(TELEM) * 8); i++)
        tempByte |= pMem[temp] & GetMemMask(i);
    pMem[temp] = tempByte;
    return *this;
}

// ввод/вывод

void SetBit(TBitField &bf, const int n)
{
    bf.SetBit(n);
}

void ClrBit(TBitField& bf, const int n)
{
    bf.ClrBit(n);
}

TBitField create(const int n)
{
    TBitField tempBF(n);
    return tempBF;
}

TBitField up(TBitField& bf, const int n)
{
    TBitField tempBF(bf.GetLength() + n);
    tempBF = tempBF | bf;
    return tempBF;
}

TBitField fill(string s)
{
    TBitField tempBF(s.length());
    for (int i = 0; i < s.length(); i++)
        if (s[i] == '1')
            tempBF.SetBit(i);
    return tempBF;
}

TBitField low(TBitField& bf, const int n)
{
    TBitField tempBF(bf.GetLength() - n);
    for (int i = 0; i < tempBF.GetLength(); i++)
        if (bf.GetBit(i))
            tempBF.SetBit(i);
    return tempBF;
}

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    map <string, void (*)(TBitField&, int)> commands_V_TI = 
    { 
        {"ADD", SetBit}, {"SET", SetBit},
        {"DEL", ClrBit}, {"CLR", ClrBit}, {"DELETE", ClrBit}, {"CLEAR", ClrBit}
    };
    map <string, TBitField (*)(int)> commands_T_I =
    {
        {"NEW", create}, {"CRT", create}, {"CREATE", create}
    };
    map <string, TBitField(*)(TBitField&, int)> commands_T_TI =
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
        int number;
        for (int i = 0; i < bf.BitLen; i++)
        {
            istr >> number;
            if (number == 1)
                (commands_V_TI["ADD"])(bf, i);
            else
                (commands_V_TI["DEL"])(bf, i);
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
                bf = (commands_T_TI[command])(bf, number);
        }
        else
            bf = (commands_T_I[command])(number);
    }
    else
        (commands_V_TI[command])(bf, number);
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for(int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i) << ' ';
    return ostr;
}