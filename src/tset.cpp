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
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
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
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res(BitField.GetLength());
	res = BitField | s.BitField;
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{

	if (Elem <= MaxPower && Elem > 0)
	{
		TSet res(Elem);
		res.BitField.SetBit(Elem);
		return res;
	}
	else
	{
		throw exception("error");
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(BitField);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(BitField.GetLength());
	res = BitField & s.BitField;
	res.MaxPower = res.BitField.GetLength();
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(BitField.GetLength());
	res = *this;
	res.BitField = ~res.BitField;
	return res;
}

void TSet::InFile(std::string file_name)
{
	fstream fs;
	fs.open(file_name, fstream::in | fstream::out);
	if (!fs.is_open())
	{
		std::cout << "Ошибка открытия файла!" << std::endl;
	}
	else
	{
		std::cout << "Файл открыт" << std::endl;
		fs << "{";
		for (int i = 0; i < BitField.GetLength(); i++)
		{
			if (BitField.GetBit(i))
			{
				if (i == BitField.GetLength() - 1)
				{
					fs << i;
				}
				else
				{
					fs << i;
					fs << ", ";
				}
			}
		}
		fs << "}";
	}
	fs.close();
}

void TSet::FromFile(std::string file_name)
{
	fstream fs;
	fs.open(file_name, fstream::in | fstream::out);
	if (!fs.is_open())
	{
		std::cout << "Ошибка открытия файла!" << std::endl;
	}
	else
	{
		std::cout << "Файл открыт" << std::endl;
		std::string str;
		getline(fs, str);
		str = DelBadSymb(str);
		int NumOfDig = CountNumOfDig(str);
		std::string* arrStr = new std::string[NumOfDig];
		int* arrInt = new int[NumOfDig];
		StrToArrStr(str, arrStr);
		ArrStrToArrInt(arrStr, arrInt, NumOfDig);
		int Max = FindMaxElem(arrInt, NumOfDig);
		TSet res(Max + 1);
		for (int i = 0; i < NumOfDig; i++)
		{
			res.InsElem(arrInt[i]);
		}
		*this = res;
		delete[] arrStr;
		delete[] arrInt;
	}
	fs.close();
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	std::string str;
	getline(istr, str);
	str = DelBadSymb(str);
	int NumOfDig = CountNumOfDig(str);
	std::string* arrStr = new std::string[NumOfDig];
	int* arrInt = new int[NumOfDig];
	StrToArrStr(str, arrStr);
	ArrStrToArrInt(arrStr, arrInt, NumOfDig);
	int Max = FindMaxElem(arrInt, NumOfDig);
	TSet res(Max + 1);
	for (int i = 0; i < NumOfDig; i++)
	{
		res.InsElem(arrInt[i]);
	}
	s = res;
	delete[] arrStr;
	delete[] arrInt;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	std::cout << "{";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i))
		{
			if (i == s.BitField.GetLength() - 1)
			{
				ostr << i;
			}
			else
			{
				ostr << i;
				ostr << ", ";
			}
		}
	}
	std::cout << "}";
	return ostr;
}

std::string DelBadSymb(std::string str)
{
	std::string tmp = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != '{' && str[i] != '}' && str[i] != ',')
		{
			tmp += str[i];
		}
	}
	return tmp;
}

int CountNumOfDig(const std::string& str)
{
	int result = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			result += 1;
		}
	}
	return result;
}

void StrToArrStr(std::string str, std::string* arr)
{
	int count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			arr[count] += str[i];
		}
		else
			count++;
	}
}

int StrToInt(std::string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result = result * 10 + (str[i] - '0');
	}

	return result;
}

void ArrStrToArrInt(std::string* arrStr, int* arrInt, int len)
{
	for (int i = 0; i < len; i++)
	{
		arrInt[i] = StrToInt(arrStr[i]);
	}
}

int FindMaxElem(int* arr, int len)
{
	int max = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
