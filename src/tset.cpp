// Множество - реализация через битовые поля

#include "tset.h"

using namespace std;

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.MaxPower)
{
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TSet temp(this->BitField);
	return (temp);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return (MaxPower);
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return (BitField.GetBit(Elem));
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
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return (*this);
}

int TSet::operator==(const TSet& s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	return (!(BitField == s.BitField));
}

TSet TSet::operator+(const TSet& s) // объединение
{
	return (TSet(BitField | s.BitField));
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet one(BitField);
	one.InsElem(Elem);
	return (one);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet one(BitField);
	one.DelElem(Elem);
	return (one);
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	return (TSet(BitField & s.BitField));
}

TSet TSet::operator~(void) // дополнение
{
	return (TSet(~BitField));
}

// перегрузка ввода/вывода
istream& operator>>(istream& istr, TSet& s) // ввод
{
	string	nums;

	cout << "Enter elements separated by spaces and press Enter." << endl;
	getline(istr, nums);
	istringstream istrim(nums);
	for (int num; istrim >> num; cout << num << endl)
	{
		s.InsElem(num);
	}
	return (istr);

}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i))
			ostr << i << " ";
	ostr << endl;
	return (ostr);
}

TSet TSet::multiples_of_k(const int k) const // получить элементы кратные k (Доп. задание №1)
{
	TSet mult(MaxPower);
	for (int i = 0; i < MaxPower; i++)
		if (IsMember(i) && i % k == 0)
			mult.InsElem(i);
	return (mult);
}


void TSet::save_to_file() const // Доп. задание №2 запись
{
	string fileName = "BitFieldO.txt";

	
	ofstream output(fileName);
	if (!output)
	{
		cout << "Error open file " << fileName << endl;
		return;
	}
	output << MaxPower << endl;
	output << *this;
	output.close();
}

TSet TSet::read_from_file() //Доп. задание №2 чтение
{
	string	fileName = "BitFieldI.txt";
	string	line;
	int		MaxPower;

	
	ifstream input(fileName);
	if (!input)
	{
		cout << "Error open file " << fileName << endl;
		return (TSet(0));
	}
	input >> MaxPower;
	input.ignore();
	TSet newSet(MaxPower);
	getline(input, line);
	istringstream istrim(line);
	for (int num; istrim >> num; cout << num << endl)
		newSet.InsElem(num);
	input.close();
	return (newSet);
}
void TSet::change_item() //Доп. задание №3
{
	int number;
	int	value;

	cout << "Enter the number of the item to change." << endl;
	cin >> number;
	if (!(BitField.GetBit(number)))
	{
		cout << "No item under the number " << number << endl;
		return;
	}
	cout << "Enter a new value." << endl;
	cin >> value;
	InsElem(value);
	
}

void TSet::change_item_for_gtests(const int number, const int value)// Доп. задание №3 специально для google test
{
	if (!(BitField.GetBit(number)))
	{
		cout << "No item under the number " << number << endl;
		return;
	}
	BitField.ClrBit(number);
	this->InsElem(value);
}
