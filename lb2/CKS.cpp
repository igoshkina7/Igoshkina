#include "CKS.h"
#include "Utils.h"

using namespace std;

ostream& operator << (ostream& out, const CKS& compr)
{
	out << "Compressor"
		<< " id: " << compr.id
		<< " Name: " << compr.name
		<< " Number of workshops in work/Number of workshop = " << compr.kolvo_workshops_in_work << "/" << compr.kolvo_workshops
		<< " Efficiency: " << compr.efficiency << endl;
	return out;
}

istream& operator >> (istream& in, CKS& new_ks)
{
	//cout << "id=" << endl;
	//new_ks.id = GetCorrectNumber(1000);
	cout << "Type name: " << endl;
	/*cin.ignore(10000, '\n');
	getline(cin, new_ks.Name);*/
	cout << "Type number of workshops: " << endl;
	new_ks.kolvo_workshops = GetCorrectNumber(100);
	cout << "Type number of workshops in work: " << endl;
	new_ks.kolvo_workshops_in_work = GetCorrectNumber(new_ks.kolvo_workshops); //указываем число цехов всего, чтобы не превышать их количество
	cout << "Type efficiency: " << endl;
	new_ks.efficiency = GetCorrectNumber(10.0);
	return in;
}

ofstream& operator<<(ofstream& fout, const CKS& compr)
{
	fout << compr.id << endl << compr.name << endl << compr.kolvo_workshops << endl << compr.kolvo_workshops_in_work << endl << compr.efficiency;
	return fout;
}

ifstream& operator>>(ifstream& fin, CKS& compr)
{
	fin >> compr.id >> compr.name >> compr.kolvo_workshops >> compr.kolvo_workshops_in_work >> compr.efficiency;
	return fin;
}

int CKS::IDC = 0; //объявляем переменную, чтобы не присвоились другие значения
CKS::CKS()
{
	id = IDC++;
}