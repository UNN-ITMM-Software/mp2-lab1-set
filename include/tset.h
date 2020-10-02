#pragma once
#ifndef __SET_H__
#define __SET_H__
#include "tbitfield.h"
class TSet
{
private:
	int MaxPower;//максимальный мощность множества 
	TBitField BitField;
public:
	TSet(int maxPower);
	TSet(const TSet& set);//конструктор копирования
	TSet(TBitField& bf);//конструктор преобразования 
	//Доступ к битам
	int GetMaxPower()const;//максимальное мощноесть множества
	void InsElem(const int n);//включить элемнт в множество 
	void DelElem(const int n);//удалить элемнеть в множество
	bool IsMember(const int n);//проверить наличие элементов в множестве
	//операции
	bool operator==(const TSet& set)const;//сравнение 
	TSet& operator=(const TSet& set);//Присваивание
	TSet operator+(const TSet& set)const;//Объединение
	TSet operator*(const TSet& set)const;//Пересечение 
	TSet operator+(const int n);//Включение эл-та в мн-ва
	TSet operator-(const int n);//Исключение эл-та из мн-ва
	TSet operator~();//инверсия
	friend istream& operator >>(istream& itsr, TSet& bf);
	friend ostream& operator <<(ostream& ostr, TSet& bf);
};
#endif __SET_H__