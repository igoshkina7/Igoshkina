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
	double length;
	double diameter;
	bool remont;
	int id_in;
	int id_out;
	int propusk;
	string name;
public:
	int get_id() const;
	int get_id_in() const;
	int get_id_out() const;
	double get_length() const;
	double get_diameter() const;
	bool get_remont() const;
	int get_propusk() const;
	static int IDT;
	Truba();
	Truba(fstream& fin);
	void EditTruba();
	void Truba_in_out(int id_out, int id_in);
};