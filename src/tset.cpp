
#include "tset.h"

TSet::TSet(int mp): BitField(mp)
{
	if (mp > 0)
	{
	(*this).MaxPower = mp;
	TBitField::TBitField(mp);
	}
	else throw logic_error("Invalide value of set max pover in constructor");
}

// конструктор копирования
TSet::TSet(const TSet &s):BitField(s.BitField)
{
	(*this).MaxPower = s.MaxPower;
	(*this).BitField = s.BitField;
	
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) :BitField(bf)
{
	(*this).MaxPower = bf.GetLength();
	(*this).BitField = bf;
}

TSet::operator TBitField()
{
	this->MaxPower = (*this).BitField.GetLength();
	return *this;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return (*this).MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return (*this).BitField.GetBit(Elem);
}

int TSet::GetNumOst(int c)
{
	int m = 0;
	for (int i = 0; i < MaxPower; i++)
	{
		if (this->IsMember(i) == 0)
			continue;
		if (i % c == 0)
			m++;
	}
	if (m == 0)
		throw logic_error("no_needed_signs");
	return m;
}

int* TSet::Ostatok(int k)
{
	int m = this->GetNumOst(k);
	int j = 0;
	int* mas = new int[m];
	for (int i = 0; i < MaxPower; i++)
	{
		if (this->IsMember(i) == 0)
			continue;
		if (i % k == 0)
		{
			mas[j]=i;
			j++;
		}

	}
	return mas;
}

void TSet::FindClr(int k)
{
	for (int i = 0; i < MaxPower; i++)
	{
		if (this->IsMember(k) == 1)
		{
			this->DelElem(k);
			break;
		}

	}
}

void TSet::WriteF()
{
	ofstream file("a.txt");
	file << (*this).MaxPower<<endl;
	for (int i = 0; i < MaxPower; i++)
	{
		if(this->IsMember(i)==1)
		file <<i<<endl;
	}
	file.close();
}

void TSet::ReadF()
{
	int k = 0;
	ifstream file("a.txt");
	file >> MaxPower;
	TSet s(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		file >> k;
		s.InsElem(k);
	}
	file.close();
	*this = s;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	(*this).BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	(*this).BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this == &s)
	{
		return *this;
	}
	(*this).MaxPower = s.MaxPower;
	(*this).BitField = s.BitField;
	return *this;

}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((*this).MaxPower != s.MaxPower)
		return 0;
	if ((*this).BitField != s.BitField)
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((*this).MaxPower != s.MaxPower)
		return 1;
	if ((*this).BitField != s.BitField)
		return 1;
	return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{

	if ((this->MaxPower) < s.GetMaxPower())
	{
		(*this).MaxPower = s.GetMaxPower();

	}
	(*this).BitField | s.BitField;
	return(*this);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	int mp;
	if ((*this).MaxPower < Elem)
		mp = Elem;
	else mp =(*this).MaxPower;
	TBitField bf(mp);
	TSet temp(bf);
	temp.InsElem(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((*this).MaxPower < Elem)
		return *this;
	(*this).DelElem(Elem);
	return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	if ((this->MaxPower) < s.GetMaxPower())
	{
		(*this).MaxPower = s.GetMaxPower();

	}
	this->BitField& s.BitField;
	return(*this);
}

TSet TSet::operator~(void) // дополнение
{
	(*this).BitField = ~(*this).BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.MaxPower;
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "Mnozhestvo moschnost'u" <<" "<< s.GetMaxPower() << endl;
	for (int i = 0; i < (s.GetMaxPower()/32)+1; i++)
		for (int j = 0; j < s.BitField.GetLength(); j++)
			if (s.BitField.GetBit(i * 32 + j) == 1)
		      ostr << i*32+j << "  " << endl;
	return ostr;
}
