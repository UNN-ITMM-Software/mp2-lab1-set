// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) {
    if (len < 0) throw out_of_range("Length should be positive");

    this->BitLen = len;
    // sizeof(TELEM) = 4; bits in TELEM = 32; log2(bits) = 5; to make 1-31 work properly +31;
    this->MemLen = (len + 31) >> 5;
    this->pMem = new TELEM[this->MemLen];

    if (this->pMem != NULL) {
        for (int i = 0; i < this->MemLen; ++i) {
            this->pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < this->MemLen; ++i) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    if (this->pMem != NULL) {
        delete[] this->pMem;
        this->pMem = NULL;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    // sizeof(TELEM) = 4; bits in TELEM = 32; log2(bits) = 5;
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    return (1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    this->pMem[this->GetMemIndex(n)] = (this->pMem[this->GetMemIndex(n)] | this->GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    this->pMem[this->GetMemIndex(n)] = (this->pMem[this->GetMemIndex(n)] & ~this->GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= this->BitLen) throw out_of_range("Bit index out of boundaries");
    return (this->pMem[this->GetMemIndex(n)] & this->GetMemMask(n)) != 0;
}

// битовые операции

TBitField &TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf != this) {
        if (this->MemLen != bf.MemLen) {
            if (this->pMem != NULL) {
                delete[] this->pMem;
                this->pMem = NULL;
            }
            this->pMem = new TELEM[bf.MemLen];
        }
        this->BitLen = bf.BitLen;
        this->MemLen = bf.MemLen;
        for (int i = 0; i < this->MemLen; ++i) {
            this->pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (&bf == this) return 1;
    if (this->BitLen == bf.BitLen) {
        for (int i = 0; i < this->MemLen; ++i) {
            if (this->pMem[i] != bf.pMem[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (&bf == this) return 0;
    if (this->BitLen == bf.BitLen) {
        for (int i = 0; i < this->MemLen; ++i) {
            if (this->pMem[i] != bf.pMem[i]) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int max_length = this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen;
    TBitField tmp(max_length);
    for (int i = 0; i < this->MemLen; ++i) {
        tmp.pMem[i] = this->pMem[i];
    }
    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] |= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int max_length = this->BitLen > bf.BitLen ? this->BitLen : bf.BitLen;
    TBitField tmp(max_length);
    for (int i = 0; i < this->MemLen; ++i) {
        tmp.pMem[i] = this->pMem[i];
    }
    for (int i = 0; i < bf.MemLen; ++i) {
        tmp.pMem[i] &= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    int fullMems = (this->BitLen) / (sizeof(TELEM) * 8);
    int exceedBits = (this->BitLen) % (sizeof(TELEM) * 8);

    TBitField tmp(this->BitLen);

    // отрицание полностью заполненных pMem
    for (int i = 0; i < fullMems; ++i) {
        tmp.pMem[i] = ~this->pMem[i];
    }

    //побитное отрицание неполного pMem
    for (int i = 0; i < exceedBits; ++i) {
        int index = sizeof(TELEM) * 8 * fullMems;
        if (!this->GetBit(index + i)) {
            tmp.SetBit(index + i);
        }
    }

    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    // 10100101 - формат
    int index = 0;
    char ch;
    do { istr >> ch; } while (ch != ' ');
    while (true) {
        istr >> ch;
        if (ch == '0') {
            bf.ClrBit(index);
            index++;
        } else if (ch == '1') {
            bf.SetBit(index);
            index++;
        } else {
            break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    // 10100101 - формат
    int len = bf.GetLength();
    for (int i = 0; i < len; ++i) {
        ostr << bf.GetBit(i);
    }
    ostr << "\n";
    return ostr;
}
