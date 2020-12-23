#include "CTruba.h"
#include "Utils.h"
#include <fstream>

using namespace std;

ostream& operator << (ostream& out, const Truba& tr)
{
	out << "Pipe"
		<< " id: " << tr.id
		<< " Name: " << tr.name
		<< " Length: " << tr.length
		<< " Diameter: " << tr.diameter
		<< (tr.remont ? " V remonte" : " Ne v remonte") << endl;
	return out;
}

istream& operator >> (istream& in, Truba& new_tr)
{
	cout << "Type name: " << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, new_tr.name);
	cout << "Type length: " << endl;
	new_tr.length = GetCorrectNumber(1000.0); //тип double за счет точки
	cout << " Type diameter: " << endl;
	new_tr.diameter = GetCorrectNumber(2000.0);
	new_tr.remont = false;
	return in;
}

ofstream& operator<<(ofstream& fout, const Truba& tr)
{
	fout << tr.id << endl << tr.name << endl << tr.diameter << endl << tr.length << endl << tr.remont << endl;
	return fout;
}

Truba::Truba(fstream& fin)
{
	fin >> this->id >> this->name >> this->diameter >> this->length >> this->remont >> this->id_out >> this->id_in;
}

int Truba::IDT = 0; //объявляем переменную, чтобы не присвоились другие значения
Truba::Truba()
{
	this->id = ++IDT;
	cout << "Name: " << endl;
	cin.ignore(10000, '\n');
	getline(cin, this->name);
	cout << "Length: " << endl;
	this->length = GetCorrectNumber(1000.0);
	cout << "Diameter: " << endl;
	this->diameter = GetCorrectNumber(2000.0);
	this->remont = false;
	this->id_out = 0;
	this->id_in = 0;
}

void Truba::EditTruba()
{
	this->remont = !remont;
}

void Truba::Truba_in_out(int out, int in)
{
	this->id_out = out;
	this->id_in = in;
}

int Truba::get_id() const
{
	int id_value = id;
	return id_value;
}
double Truba::get_diameter() const
{
	double diameter_value = diameter;
	return diameter_value;
}
double Truba::get_length() const
{
	double length_value = length;
	return length_value;
}
int Truba::get_id_in() const
{
	int id_in_value = id_in;
	return id_in_value;
}
int Truba::get_id_out() const
{
	int id_out_value = id_out;
	return id_out_value;
}
bool Truba::get_remont() const
{
	return remont;
}

int Truba::get_propusk() const
{
	int propusk;
	if (diameter > 1420)
		propusk = 95;
	else if (diameter > 1220)
		propusk = 55;
	else if (diameter > 1020)
		propusk = 30;
	else if (diameter > 720)
		propusk = 12;
	else if (diameter > 530)
		propusk = 5;
	else propusk = 1;
	return propusk;
}

