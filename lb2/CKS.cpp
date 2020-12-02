#include "CKS.h"
#include "Utils.h"

using namespace std;

ostream& operator << (ostream& out, const CKS& compr)
{
	out << "Compressor"
		<< " id: " << compr.id
		<< " Name: " << compr.name
		<< " Number of workshops in work/Number of workshop = " << compr.kolvo_workshops_in_work << "/" << compr.kolvo_workshops << " = " << compr.kolvo_workshops_in_work*100/compr.kolvo_workshops << "%"
		<< " Efficiency: " << compr.efficiency << endl;
	return out;
}

istream& operator >> (istream& in, CKS& new_ks)
{
	cout << "Type name: " << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, new_ks.name);
	cout << "Type number of workshops: " << endl;
	new_ks.kolvo_workshops = GetCorrectNumber(100);
	cout << "Type number of workshops in work: " << endl;
	new_ks.kolvo_workshops_in_work = GetCorrectIndex(new_ks.kolvo_workshops); //указываем число цехов всего, чтобы не превышать их количество
	cout << "Type efficiency: " << endl;
	new_ks.efficiency = GetCorrectNumber(1.0);
	return in;
}

ofstream& operator<<(ofstream& fout, const CKS& compr)
{
	fout << compr.id << endl << compr.name << endl << compr.kolvo_workshops << endl << compr.kolvo_workshops_in_work << endl << compr.efficiency;
	return fout;
}

CKS::CKS(fstream& fin)
{
	fin >> this->id >> this->name >> this->kolvo_workshops >> this->kolvo_workshops_in_work >> this->efficiency;
}

int CKS::IDC = 0; //объявляем переменную, чтобы не присвоились другие значения
CKS::CKS()
{
	this->id = ++IDC;
	cout << "Name: " << endl;
	cin.ignore(10000, '\n');
	getline(cin, this->name);
	cout << "Numbers of workshops: " << endl;
	this->kolvo_workshops = GetCorrectNumber(100);
	cout << "Numbers of workshops in work: " << endl;
	this->kolvo_workshops_in_work = GetCorrectNumber(this->kolvo_workshops);
	cout << "Efficiency: " << endl;
	this->efficiency = GetCorrectNumber(10.0);
}

int CKS::set_id() const
{
	int id_value = id;
	return id_value;
}