#pragma once
#include <iostream>
using namespace std;
typedef unsigned int TELEM;
class TBitField
{
private:
	int BitLen;//����� �������� ����
	int MemLen;//���-�� ��������� Mem ��� ������������� �������� ����
	TELEM* pMem;//������ ��� ������������� �������� ����
public:
	TBitField();
	TBitField(int len);
	TBitField(const TBitField& bf);
	~TBitField();
	//������ � �����
	void SetBit(const int n);//���������� ���
	void ClrBit(const int n);//�������� ��� 
	int GetBit(const int n);// const;�������� �������� ����
	int GetMemIndex(const int n);//������ Mem ��� ���� n
	TELEM GetMemMask(const int n);//������� ����� ��� ���� n 
	int GetLenght();//�������� ����� ����
	//������� ��������
	bool operator ==(const TBitField& bf)const;//���������
	TBitField& operator=(const TBitField& bf);//������������
	TBitField operator | (const TBitField & bf)const;//�������� ���
	TBitField operator &(const TBitField& bf)const;//�������� �
	TBitField operator ~();//��������� 
	friend istream&operator>> ( istream& istr, TBitField& bf);
	friend ostream&operator<<(ostream& ostr, TBitField& bf);
};