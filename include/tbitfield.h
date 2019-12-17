// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля
  // методы реализации
  int   GetMemIndex(const int n) const; // индекс в pМем для бита n       
  TELEM GetMemMask (const int n) const; // битовая маска для бита n       
public:
  TBitField(int len = 10);           // конструктор с параметрами                               
  TBitField(const TBitField &bf);    // конструктор копирования                                  
  ~TBitField();                      // деструктор    

  // доступ к битам
  int GetLength(void) const;      // получить длину (к-во битов)           
  void SetBit(const int n);       // установить бит                       
  void ClrBit(const int n);       // очистить бит                        
  int  GetBit(const int n) const; // получить значение бита               

  // битовые операции
  int operator==(const TBitField &bf) const; // сравнение                 
  int operator!=(const TBitField &bf) const; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание              
  TBitField  operator|(const TBitField &bf) const; // операция "или"            
  TBitField  operator&(const TBitField &bf) const; // операция "и"              
  TBitField  operator~(void) const;                // отрицание                  

  friend istream &operator>>(istream &istr, TBitField &bf);       // чтение из потока 
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); // запись в поток
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)

#endif
