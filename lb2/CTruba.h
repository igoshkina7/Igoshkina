#pragma once
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

class Truba
{
	friend ostream& operator << (ostream& out, const Truba& t);   //����� � �������
	friend istream& operator >> (istream& in, Truba& new_tr);     //���� � �������
	friend ofstream& operator << (ofstream& out, const Truba& t);   //����� � ����
	friend fstream& operator >> (fstream& in, Truba& new_tr);    //���������� �� �����
	
	int id;  //��������� ����������, ����� ������������ �� ������� �� �������� ������
public:
	string name;
	double diametr;
	double length;
	bool remont;
	static int IDT;
	Truba();
	Truba(std::fstream& fin);
	void EditTrubaTrue();
	int get_id() const;
	int get_length() const;
};