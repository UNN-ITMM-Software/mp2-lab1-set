// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>
#include <bitset>
#include <climits>

# define BIT_32 0x80000000

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
	int  BitLen; // длина битового поля - макс. к-во битов
	TELEM* pMem; // память для представления битового поля
	int  MemLen; // к-во эл-тов Мем для представления бит.поля

	// методы реализации
	int   GetMemIndex(const int n) const; // индекс в pМем для бита n       
	TELEM GetMemMask(const int n) const; // битовая маска для бита n       
public:
	TBitField(int len);                                                
	TBitField(const TBitField& bf);                                     
	~TBitField();                                                        

	// доступ к битам
	int GetLength(void) const;      // получить длину (к-во битов)           
	void SetBit(const int n);       // установить бит                       
	void ClrBit(const int n);       // очистить бит                         
	int  GetBit(const int n) const; // получить значение бита               

	// битовые операции
	bool operator==(const TBitField& bf) const; // сравнение                 
	bool operator!=(const TBitField& bf) const; // сравнение
	TBitField& operator=(const TBitField& bf); // присваивание              
	TBitField  operator|(const TBitField& bf); // операция "или"            
	TBitField  operator&(const TBitField& bf); // операция "и"              
	TBitField  operator~(void);                // операция отрицания                  

	friend istream& operator>>(istream& istr, TBitField& bf);       
	friend ostream& operator<<(ostream& ostr, const TBitField& bf);   
};

// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)


#endif
