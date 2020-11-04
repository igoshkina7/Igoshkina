#include "CTruba.h"
#include "Utils.h"

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
	new_tr.length = GetCorrectNumber(1000.0); //��� double �� ���� �����
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

ifstream& operator>>(ifstream& fin, Truba& tr)
{
	fin >> tr.id >> tr.name >> tr.diametr >> tr.length >> tr.remont;
	return fin;
}

int Truba::IDT = 0; //��������� ����������, ����� �� ����������� ������ ��������
Truba::Truba()
{
	id = IDT++;
}

void Truba::EditTrubaTrue()
{
	remont = 1;
}

void Truba::EditTrubaFalse()
{
	remont = 0;
}
