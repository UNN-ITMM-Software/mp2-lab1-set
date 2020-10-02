#pragma once
#ifndef __SET_H__
#define __SET_H__
#include "tbitfield.h"
class TSet 
{
private:
	int MaxPower;//������������ �������� ��������� 
	TBitField BitField;
public:
	TSet(int maxPower);
	TSet(const TSet& set);//����������� �����������
	TSet(TBitField& bf);//����������� �������������� 
	//������ � �����
	int GetMaxPower()const;//������������ ��������� ���������
	void InsElem(const int n);//�������� ������ � ��������� 
	void DelElem(const int n);//������� �������� � ���������
	bool IsMember(const int n);//��������� ������� ��������� � ���������
	//��������
	bool operator==(const TSet& set)const;//��������� 
	TSet& operator=(const TSet& set);//������������
	TSet operator+(const TSet& set)const;//�����������
	TSet operator*(const TSet& set)const;//����������� 
    TSet operator+(const int n);//��������� ��-�� � ��-��
	TSet operator-(const int n);//���������� ��-�� �� ��-��
	TSet operator~();//��������
	friend istream& operator >>(istream, TSet& bf);
	friend ostream& operator <<(ostream, TSet& bf);
};
#endif __SET_H__