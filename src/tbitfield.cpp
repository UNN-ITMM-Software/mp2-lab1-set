// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{

    if (len < 0) {
        throw "error";
    }
    BitLen = len;
    int s = sizeof(TELEM) * 8;
    MemLen = ((s - 1 + BitLen) / s);

    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {

        pMem[i] = bf.pMem[i];
    }

}

TBitField::~TBitField()
{
    if (pMem != NULL) {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n > BitLen || n < 0) {
        throw "error memIndex";
    }

    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n > BitLen) {

        throw "uncorrect mem mask value";
    }
    return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen) {

        throw "uncorrect set bit";
    }

    int mask = GetMemIndex(n);

    int numOfBit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));

    pMem[mask] |= GetMemMask(numOfBit);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen) {

        throw "uncorrect clr bit";

    }

    int mask = GetMemIndex(n);

    int numOfBit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));

    pMem[mask] &= ~GetMemMask(numOfBit);
    
}

int TBitField::GetBit(const int n) const // получить значение бита
{

    if (n < 0 || n > BitLen) {

        throw "uncorrect get bit";

    }

    int mask = GetMemIndex(n);

    int numOfBit = n - (n / (sizeof(TELEM) * 8) * (sizeof(TELEM) * 8));
    
    
    if (pMem[mask] & GetMemMask(numOfBit)) {
        return 1;
    }
    else {
        return 0;
    }

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    if (pMem != nullptr) {
        delete[]pMem;
    }
    BitLen = bf.BitLen;

    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {

        pMem[i] = bf.pMem[i];
    }

    return *this;
    
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen) {
        return 0;
    }
    
    for (int i = 0; i < MemLen; i++) {

        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    
    return 1;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{

    if (BitLen != bf.BitLen || MemLen != bf.MemLen) {
        return 1;
    }

    for (int i = 0; i < MemLen; i++) {

        if (pMem[i] != bf.pMem[i]) {
            return 1;
        }
    }

    return 0; 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int size = 0;
    if (BitLen >= bf.BitLen) {

        size = BitLen;
    }
    else {
        size = bf.BitLen;
    }

    int sizeTEL = 0;

    if (MemLen >= bf.MemLen) {

        sizeTEL = MemLen;
    }
    else {
        sizeTEL = bf.MemLen;
    }

    TBitField a(size);

    for (int i = 0; i < sizeTEL; i++) {

        a.pMem[i] = 0;

        if (i < MemLen) {
            a.pMem[i] |= pMem[i];
        }

        if (i < bf.MemLen) {
            a.pMem[i] |= bf.pMem[i];
        }
    }
    return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

    int size = 0;
    if (BitLen >= bf.BitLen) {

        size = BitLen;
    }
    else {
        size = bf.BitLen;
    }

    int sizeTEL = 0;

    if (MemLen >= bf.MemLen) {

        sizeTEL = MemLen;
    }
    else {
        sizeTEL = bf.MemLen;
    }

    TBitField a(size);

    for (int i = 0; i < sizeTEL; i++) {

        if (i < MemLen && i < bf.MemLen) {
            a.pMem[i] = pMem[i] & bf.pMem[i];
        }

        else {
            a.pMem[i] = 0;
        }
    }


    return a;
}

TBitField TBitField::operator~(void) // отрицание
{
    // 0010 -> 1101   ~ - инвертирует

    TBitField a(BitLen);

    for (int i = 0; i < MemLen; i++) {

        a.pMem[i] = ~pMem[i];
    }

    *this = a;

    int lastNumBit = BitLen - (MemLen - 1) * (sizeof(TELEM) * 8);
    if (lastNumBit < sizeof(TELEM) * 8) {
        int mask = (1 << (lastNumBit)) - 1;
        a.pMem[MemLen - 1] &= mask;
    }
    return a;
    
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int size;

    istr >> size;

    TBitField a(size);
     

    int numberPos = 0;

    for (int i = 0; i < size; i++) {

        istr >> numberPos;

        if (numberPos) {

            a.SetBit(i);
        }
    }

    bf = a;

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

    ostr << "Our Arr: " << "\n";

    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.pMem[i] << " ";
    }
    return ostr;
}
