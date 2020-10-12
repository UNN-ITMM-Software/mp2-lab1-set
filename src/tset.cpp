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
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}

TSet TSet::operator+(const TSet& s) // объединение
{
	int l;
	if (MaxPower > s.MaxPower)
		l = MaxPower;
	else
		l = s.MaxPower;
	TSet res(l);
	res.BitField = BitField | s.BitField;
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
	{
		throw "Неположительный элемент";
	}
	else
	{
		TSet ts(MaxPower);
		BitField.SetBit(Elem);
		ts.BitField = BitField;
		return ts;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
	{
		throw "Неположительный элемент";
	}
	else
	{
		TSet ts(MaxPower);
		BitField.ClrBit(Elem);
		ts.BitField = BitField;
		return ts;
	}
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet ts(s.MaxPower);
	ts.BitField = this->BitField & s.BitField;
	return ts;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	int k;
	for (int i = 0; i < s.MaxPower; i++) {
		istr >> k;
		s.InsElem(k);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.BitField.GetBit(i) == 1)
			ostr << i << ' ';
	return ostr;
}