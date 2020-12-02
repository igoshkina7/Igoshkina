#pragma once
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

class Truba
{
	friend ostream& operator << (ostream& out, const Truba& t);   //вывод в консоль
	friend istream& operator >> (istream& in, Truba& new_tr);     //ввод в консоль
	friend ofstream& operator << (ofstream& out, const Truba& t);   //вывод в файл
	friend fstream& operator >> (fstream& in, Truba& new_tr);    //считывание из файла
	
	int id;  //приватная переменная, чтобы пользователь не поменял на неверные данные
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