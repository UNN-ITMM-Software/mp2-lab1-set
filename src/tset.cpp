#include "tset.h"

TSet::TSet(int mp) : BitField(mp)//'BitFielf(-1)'
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)//'BitFielf(-1)'
{
	MaxPower = s.MaxPower;
	//BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)//'BitFielf(-1)'
{
	//BitField = bf;
	MaxPower = bf.GetLength();
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
	if ((Elem >= MaxPower) || (Elem < 0))
		throw (4);
	else
		return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem >= MaxPower) || (Elem < 0))
		throw 4;
	else
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem >= MaxPower) || (Elem < 0))
		throw 4;
	else
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с  элементом
{
	TSet res(*this);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet res(s.MaxPower);
	res.BitField = this->BitField & s.BitField;
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	istr >> s.BitField;
	s.MaxPower = s.BitField.GetLength();
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
