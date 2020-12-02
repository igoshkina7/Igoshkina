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
		<< " Diameter: " << tr.diametr
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
	cout << " Type diametr: " << endl;
	new_tr.diametr = GetCorrectNumber(2000.0);
	new_tr.remont = false;
	return in;
}

ofstream& operator<<(ofstream& fout, const Truba& tr)
{
	fout << tr.id << endl << tr.name << endl << tr.diametr << endl << tr.length << endl << tr.remont << endl;
	return fout;
}

Truba::Truba(fstream& fin)
{
	fin >> this->id >> this->name >> this->diametr >> this->length >> this->remont;
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
	cout << "Diametr: " << endl;
	this->diametr = GetCorrectNumber(2000.0);
	this->remont = false;
}

void Truba::EditTrubaTrue()
{
	this->remont = true;
}


int Truba::get_id() const
{
	return id;
}

int Truba::get_length() const
{
	return length;
}

