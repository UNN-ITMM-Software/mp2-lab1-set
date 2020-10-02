#pragma once
#ifndef __BITFIELD_H__
#define __BITFIELD_H__
#include <iostream>
using namespace std;
typedef unsigned int TELEM;
class TBitField
{
private:
	int BitLen;//длина битового пол€
	int MemLen;//кол-во элементов Mem дл€ представлени€ битового пол€
	TELEM* pMem;//ѕам€ть дл€ представлени€ битового пол€
public:
	TBitField();
	TBitField(int len);
	TBitField(const TBitField& bf);
	~TBitField();
	//ƒоступ к битам
	void SetBit(const int n);//установить бит
	void ClrBit(const int n);//очистить бит 
	int GetBit(const int n);// const;получить значени€ бита
	int GetMemIndex(const int n);//»ндекс Mem дл€ бита n
	TELEM GetMemMask(const int n);//Ѕитова€ маска дл€ бита n 
	int GetLenght();//ѕолучить длину кода
	//битовые операции
	bool operator ==(const TBitField& bf)const;//сравнение
	TBitField& operator=(const TBitField& bf);//присваивание
	TBitField operator | (const TBitField & bf)const;//операци€ или
	TBitField operator &(const TBitField& bf)const;//операци€ и
	TBitField operator ~();//отрицание 
	friend istream&operator>> ( istream& istr, TBitField& bf);
	friend ostream&operator<<(ostream& ostr, TBitField& bf);
};
#endif __BITFIELD_H__