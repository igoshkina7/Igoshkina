#include <iostream>
#include <vector>
#include <fstream>
#include "CTruba.h"
#include "CKS.h"
#include "Utils.h"

using namespace std;

Truba& SelectTruba(vector <Truba>& tr)
{
	cout << "Enter index(0-" << tr.size()-1 << "): ";
	unsigned int index = GetCorrectNumber(tr.size() - 1);
	return tr[index];
}

CKS& SelecCKS(vector <CKS>& ks)
{
	cout << "Enter index(0-" << ks.size()-1 << "): ";
	unsigned int index = GetCorrectNumber(ks.size() - 1); //только положиетльные числа, диапазон в два раза больше
	return ks[index];
}


void change_status(Truba& t) 
{
	t.EditTruba();
}

void PrintMenu()
{
	cout << "1. Add pipe" << endl;
	cout << "2. Add compressor" << endl;
	cout << "3. Change pipe status" << endl;
	cout << "4. Print pipe's info" << endl;
	cout << "5. Print compressor's info" << endl;
	cout << "6. Save pipe to file" << endl;
	cout << "7. Save compressor to file" << endl;
	cout << "8. Load pipe's info" << endl;
	cout << "9. Load compressor's info" << endl;
	cout << "10. Delete pipe" << endl;
	cout << "11. Delete compressor" << endl;
	cout << "12. Search for pipe by length" << endl;
	cout << "13. Search for pipe by characteristic: v remonte or not" << endl;
	cout << "14. Search for compressor by name" << endl;
	cout << "15. Search for compressor by percentage of non-working workshops" << endl;
	cout << "16. Edit pipe" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose action: ";
}


template<typename T> //для ввода любого типа данных
using FilterTR = bool(*)(const Truba& t, T param);

template<typename T>
using FilterСKS = bool(*)(const CKS& c, T param);

bool CheckByLength(const Truba& t, double param)
{
	return t.length > param;
}

bool CheckByRemont(const Truba& t, bool param)
{
	return t.remont == param;
}

bool CheckByName(const CKS& c, string param)
{
	return c.name == param;
}

bool CheckByProcent(const CKS& c, double param)
{
	return ((c.kolvo_workshops - c.kolvo_workshops_in_work) / c.kolvo_workshops_in_work * 100) > param;
}

template<typename T>
vector<int> FindTrubaByFilter(const vector<Truba>& pipes, FilterTR<T> f, T param)
{
	vector <int> rest;
	int i = 0;
	for (auto& t : pipes)
	{
		if (f(t, param))
			rest.push_back(i);
		i++;
	}
	return rest;
}

template<typename T>
vector<int> FindCKSByFilter(const vector<CKS>& ks, FilterСKS<T> f, T param)
{
	vector <int> resc;
	int i = 0;
	for (auto& c : ks)
	{
		if (f(c, param))
			resc.push_back(i);
		i++;
	}

	return resc;
}

void deleteTR(vector <Truba>& pipes)
{
	cout << endl << "Type pipe's ID KS delite: " << endl;
	int i = GetCorrectNumber(pipes.size());
	pipes.erase(pipes.begin() + i);   //https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/ и https://www.cplusplus.com/reference/vector/vector/erase/
}                                     //через указатель слишком сложно делать

void deleteCKS(vector <CKS>& ks)
{
	cout << endl << "Type KS's ID to delite: " << endl;
	int i = GetCorrectNumber(ks.size());
	ks.erase(ks.begin() + i);
}

//vector <Truba> EditTr(vector<Truba>& pipes, double x)
//{
//
//	int i = 0;
//	for (auto& tr : pipes)
//	{
//		
//		if (tr.length > x)
//		{
//			tr.EditTruba();
//		}
//		i++;
//	}
//	return pipes;
//}

int main()
{
	vector <Truba> pipes;
	vector <CKS> ks;
	
	vector <int> res;
	int i;
	double param;
	string name;

	while (1)
	{
		cout << "Select action:" << endl;
		PrintMenu();
		
		switch (GetCorrectNumber(16))
		{
		case 1:
		{
			Truba tr;
			cin >> tr;
			pipes.push_back(tr);
			break;
		}
		case 2:
		{
			CKS compr;
			cin >> compr;
			ks.push_back(compr);
			break;
		}
		case 3:
		{
			change_status(SelectTruba(pipes));
			break;
		}
		case 4:
		{
			for (auto& tr : pipes)
				cout << tr << endl;
			break;
		}
		case 5:
		{
			for (auto& compr : ks)
				cout << compr << endl;
			break;
		}
		case 6:
		{
			Truba tr;
			ofstream fout;
			fout.open("Truba.txt", ios::out);
			if (fout.is_open()) 
			{
				fout << pipes.size() << endl;
				for (Truba tr : pipes)
					fout << tr;
				fout.close();
			}
			break;
		}
		case 7:
		{
			CKS compr;
			ofstream fout;
			fout.open("CS.txt", ios::out);
			if (fout.is_open())
			{
				fout << ks.size() << endl;
				for (CKS compr : ks)
					fout << compr;
				fout.close();
			}
			break;
		}
		case 8:
		{	
			Truba tr;
			ifstream fin;
			fin.open("Truba.txt", ios::in);
			if (fin.is_open()) 
			{
				int count;
				fin >> count;
				while (count--)
				{
					fin >> tr;
					pipes.push_back(tr);
				}
				fin.close();
			}
			break;
		}
		case 9:
		{	
			CKS compr;
			ifstream fin;
			fin.open("CS.txt", ios::in);
			if (fin.is_open()) 
			{
				int count;
				fin >> count;
				while (count--)
				{
					fin >> compr;
					ks.push_back(compr);
				}
				fin.close();
			}
			break;
		}
		case 10:
		{ 
			deleteTR(pipes);
			break;
		}
		case 11:
		{
			deleteCKS(ks);
			break; 
		}
		case 12:
		{
			cout << "Search for pipe by length ";
			cin >> param;
			for (int i : FindTrubaByFilter<double>(pipes, CheckByLength, param))
				cout << pipes[i];
			break;
		}
		case 13:
		{
			for (int i : FindTrubaByFilter(pipes, CheckByRemont, false))
				cout << pipes[i];
			break;
		}
		case 14:
		{
			cout << "Search for compressor by name  ";
			cin >> name;
			for (int i : FindCKSByFilter<string>(ks, CheckByName, name))
				cout << ks[i];
			break; }
		case 15:
		{
			cout << "Percentage of non-working workshops ";
			param = GetCorrectNumber(100.0);
			for (int i : FindCKSByFilter<double>(ks, CheckByProcent, param))
				cout << ks[i];
			break;
		}
		/*case 16:
		{	double d;
		cout << "Edit pipe";
		d = GetCorrectNumber(2000.0);
		for (int i : FindTrubaByFilter<double>(pipes, CheckByLength, d))
		{
			Edit(pipe, d);
		}
		break;
		}*/
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Wrong action" << endl;
		}
		}
	}
	return 0;
}
