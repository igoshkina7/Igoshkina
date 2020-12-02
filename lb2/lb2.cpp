﻿#include <iostream>
#include <vector>
#include <fstream>
#include "CTruba.h"
#include "CKS.h"
#include "Utils.h"
#include <unordered_map>

using namespace std;

void change_status(Truba& t)
{
	t.remont = !t.remont;
}

void change_workshops(CKS& ks)
{
	cout << "Kolvo workshops in work: " << endl;
	ks.kolvo_workshops_in_work = GetCorrectIndex(ks.kolvo_workshops);
}

void PrintMenu()
{
	cout << "1. Add pipe" << endl;
	cout << "2. Add compressor" << endl;
	cout << "3. Change pipe status" << endl;
	cout << "4. Change number workshops in work" << endl;
	cout << "5. Print pipe's info" << endl;
	cout << "6. Print compressor's info" << endl;
	cout << "7. Save pipe to file" << endl;
	cout << "8. Save compressor to file" << endl;
	cout << "9. Load pipe's info" << endl;
	cout << "10. Load compressor's info" << endl;
	cout << "11. Delete pipe" << endl;
	cout << "12. Delete compressor" << endl;
	cout << "13. Search for pipe by length" << endl;
	cout << "14. Search for pipe by characteristic: v remonte or not" << endl;
	cout << "15. Search for compressor by name" << endl;
	cout << "16. Search for compressor by percentage of non-working workshops" << endl;
	cout << "17. Edit pipe" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose action: ";
}
template<typename T> //для ввода любого типа данных
using FilterTR = bool(*)(const Truba& t, T param);

template<typename T>
using FilterСKS = bool(*)(const CKS& c, T param);

bool CheckByLength(const Truba& t, double param)
{
	return t.set_length() == param;
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
	double k;
	k = 100 * (c.kolvo_workshops - c.kolvo_workshops_in_work) / c.kolvo_workshops;
	return  (k) == param;
}

template<typename T>
vector<int> FindTrubaByFilter(const unordered_map<int, Truba>& pipes, FilterTR<T> f, T param)
{
	vector <int> res_t;
	res_t.reserve(pipes.size()); //изменение емкости
	for (const auto& t : pipes)
	{
		if (f(t.second, param))
			res_t.push_back(t.first);
	}
	return res_t;
}

template<typename T>
vector<int> FindCKSByFilter(const unordered_map<int, CKS>& ks, FilterСKS<T> f, T param)
{
	vector <int> res_c;
	for (const auto& c : ks)
	{
		if (f(c.second, param))
			res_c.push_back(c.first);
	
	}

	return res_c;
}

	int main()
{
	
	unordered_map <int, Truba> mapTruba;
	unordered_map <int, CKS> mapCKS;
	

	while (1)
	{
		cout << "Select action:" << endl;
		PrintMenu();
		
		switch (GetCorrectIndex(17))
		{
		case 1:
		{

			mapTruba.insert(pair<int, Truba>(Truba::IDT, Truba()));
			break;
		}
		case 2:
		{
			mapCKS.insert(pair<int, CKS>(CKS::IDC, CKS()));
			break;
		}
		case 3:
		{
			cout << "Enter index(1-" << mapTruba.size() << "): ";
			unsigned int index = GetCorrectIndex(mapTruba.size());
			change_status(mapTruba[index]);
			break;
		}
		case 4:
		{
			cout << "Enter index(1-" << mapCKS.size() << "): ";
			unsigned int index = GetCorrectIndex(mapCKS.size());
			change_workshops(mapCKS[index]);
			break;
		}
		case 5:
		{
			for (auto& tr : mapTruba)
				cout << tr.second << endl;
			break;
		}
		case 6:
		{
			for (auto& compr : mapCKS)
				cout << compr.second << endl;
			break;
		}

		case 7:
		{
			ofstream fout;
			fout.open("Truba.txt", ios::out);
			if (fout.is_open())
			{
				for (auto it = mapTruba.begin(); it != mapTruba.end(); ++it)
				{
					fout << it->second << endl;
				}
				fout.close();
			}
			break;
		}
		case 8:
		{
			ofstream fout;
			fout.open("CS.txt", ios::out);
			if (fout.is_open())
			{
				for (auto ic = mapCKS.begin(); ic != mapCKS.end(); ++ic)
				{
					fout << ic->second << endl;
				}
				fout.close();
			}
			break;
		}
		
		case 9:
		{	
			fstream fin;
			unordered_map<int, Truba> pipe2;
			fin.open("Truba.txt", fstream::in);
			if (fin.is_open()) {
				while (!fin.eof())
				{
					Truba p(fin);
					pipe2.insert(pair<int, Truba>(p.set_id(), p));
				}
				fin.close();
				mapTruba = pipe2;
				Truba::IDT = FindMaxID(mapTruba);
			}
			break;
		}

		case 10:
		{
			fstream fin;
			unordered_map<int, CKS> ks2;
			fin.open("CKS.txt", fstream::in);
			if (fin.is_open()) {
				while (!fin.eof())
				{
					CKS k(fin);
					ks2.insert(pair<int, CKS>(k.set_id(), k));
				}
				fin.close();
				mapCKS = ks2;
				CKS::IDC = FindMaxID(mapCKS);
			}
			break;
		}
		case 11:
		{
			unordered_map <int, Truba>::iterator iter ;
			cout << endl << "ID Pipe to delite: (1-" << mapTruba.size() <<")";
			int id = GetCorrectNumber(1000);
			iter=mapTruba.find(id);
			mapTruba.erase(iter);
			break;
		}
		case 12:
		{
			unordered_map <int, CKS>::iterator iter;
			cout << endl << "ID KS to delite: (1-" << mapCKS.size() << ")";
			int id = GetCorrectNumber(1000);
			iter = mapCKS.find(id);
			mapCKS.erase(iter);
			break;
		}
		case 13:
		{
			double param;
			cout << "Search for pipe by length ";
			cin >> param;
			for (int i : FindTrubaByFilter<double>(mapTruba, CheckByLength, param))
				cout << mapTruba[i];
			break;
		}
		case 14:
		{
			cout << "Type status: ";
			for (int i : FindTrubaByFilter(mapTruba, CheckByRemont, true))
				cout << mapTruba[i];
			break;
		}
		case 15:
		{
			string name;
			cout << "Search for compressor by name  ";
			cin >> name;
			for (int i : FindCKSByFilter<string>(mapCKS, CheckByName, name))
				cout << mapCKS[i];
			break; 
		}
		case 16:
		{
			double param;
			cout << "Percentage of non-working workshops ";
			param = GetCorrectNumber(100.0);
			for (int i : FindCKSByFilter<double>(mapCKS, CheckByProcent, param))
				cout << mapCKS[i];
			break;
		}
		case 17:
		{
			double x, y;
			cout << "Edit pipe's lenght :";
			x = GetCorrectNumber(2000.0);
			cout << "Edit pipe's diametr: ";
			y = GetCorrectNumber(2000.0);
			for (int i : FindTrubaByFilter<double>(mapTruba, CheckByLength, x))
			{
				if (mapTruba[i].length == x && mapTruba[i].diametr == y);
				            mapTruba[i].EditTrubaTrue();
			}
		break;
		}
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
