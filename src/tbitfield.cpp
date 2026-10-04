// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "../include/tbitfield.h"
#include <stdexcept>

TBitField::TBitField(int len) : BitLen(len) {
    if (len < 0) throw std::invalid_argument("Length cannot be negative");
    MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    if (MemLen == 0) MemLen = 1;
    pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField &bf) : BitLen(bf.BitLen), MemLen(bf.MemLen) {
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() { delete[] pMem; }

int TBitField::GetLength(void) const { return BitLen; }

int TBitField::GetMemIndex(const int n) const { return n / (sizeof(TELEM) * 8); }
TELEM TBitField::GetMemMask(const int n) const { return 1 << (n % (sizeof(TELEM) * 8)); }

void TBitField::SetBit(const int n) {
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
}

TBitField& TBitField::operator=(const TBitField &bf) {
    if (this != &bf) {
        delete[] pMem; BitLen = bf.BitLen; MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const {
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++) if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const { return !(*this == bf); }

TBitField TBitField::operator|(const TBitField &bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField t(maxLen);
    for (int i = 0; i < t.MemLen; i++) {
        TELEM a = (i < MemLen) ? pMem[i] : 0, b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        t.pMem[i] = a | b;
    }
    return t;
}

TBitField TBitField::operator&(const TBitField &bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField t(maxLen);
    for (int i = 0; i < t.MemLen; i++) {
        TELEM a = (i < MemLen) ? pMem[i] : 0, b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        t.pMem[i] = a & b;
    }
    return t;
}

TBitField TBitField::operator~(void) {
    TBitField t(BitLen);
    for (int i = 0; i < MemLen; i++) t.pMem[i] = ~pMem[i];
    int r = BitLen % (sizeof(TELEM) * 8);
    if (r) t.pMem[MemLen - 1] &= (1 << r) - 1;
    return t;
}

istream& operator>>(istream &is, TBitField &bf) {
    char c;
    for (int i = 0; i < bf.BitLen; i++) { is >> c; if (c == '1') bf.SetBit(i); else bf.ClrBit(i); }
    return is;
}

ostream& operator<<(ostream &os, const TBitField &bf) {
    for (int i = 0; i < bf.BitLen; i++) os << bf.GetBit(i);
    return os;
}