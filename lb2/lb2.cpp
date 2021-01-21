#include <iostream>
#include <vector>
//#include<string>
//#include<iterator>
#include <fstream>
#include "CTruba.h"
#include "CKS.h"
#include "Utils.h"
#include <unordered_map>
#include <unordered_set>
#include"Graphwork.h"

using namespace std;

void change_workshops(CKS& ks)
{
	cout << "Kolvo workshops in work (0-"<< ks.kolvo_workshops<<"):" << endl;
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
	cout << "7. Save data to file" << endl;
	cout << "8. Load data" << endl;
	cout << "9. Delete pipe" << endl;
	cout << "10. Delete compressor" << endl;
	cout << "11. Search for pipe by length" << endl;
	cout << "12. Search for pipe by characteristic: v remonte or not" << endl;
	cout << "13. Search for compressor by name" << endl;
	cout << "14. Search for compressor by percentage of non-working workshops" << endl;
	cout << "15. Edit pipe" << endl;
	cout << "16. Create Graph" << endl;
	cout << "17. Print Graph" << endl;
	cout << "28. Topologicheskaya sortirovka" << endl;
	cout << "19. Maximal potok" << endl;
	cout << "20. Kratchayshiy puti" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose action: ";
}
template<typename T> //для ввода любого типа данных
using FilterTR = bool(*)(const Truba& t, T param);

template<typename T>
using FilterСKS = bool(*)(const CKS& c, T param);

bool CheckByLength(const Truba& t, double param)
{
	return t.get_length() == param;
}

bool CheckByRemont(const Truba& t, bool param)
{
	return t.get_remont() == param;
}

bool CheckByName(const CKS& c, string param)
{
	return c.name == param;
}

bool CheckByProcent(const CKS& c, double param)
{
	double k;
	k = 100 * (c.kolvo_workshops - c.kolvo_workshops_in_work) / c.kolvo_workshops;
	if (((c.kolvo_workshops - c.kolvo_workshops_in_work) % c.kolvo_workshops) > (c.kolvo_workshops / 2))
	     k++;
	return  (k) == param;
}

bool CheckByID_in(const Truba& t, int param)
{
	return t.get_id_in() == param;
}
bool CheckByID_out(const Truba& t, int param)
{
	return t.get_id_out() == param;
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

int GetIDKS(const unordered_map<int, CKS>& mapCKS)
{
	unordered_map <int, CKS> ::iterator id;
	int i;
	while ((cin >> i).fail() || (mapCKS.find(i) == mapCKS.end()))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "KS with this ID is not found. Type again: ";
	}
	return i;
}

	int main()
{
	
	unordered_map <int, Truba> mapTruba;
	unordered_map <int, CKS> mapCKS;
	unordered_map<int, vector<id_in_pipe>> graph;
	unordered_set<int> id_KS;

	while (1)
	{
		cout << "Select action:" << endl;
		PrintMenu();
		
		switch (GetCorrectIndex(22))
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
			unordered_map <int, Truba> ::iterator n;
			cout << "Enter index(1-" << mapTruba.size() << "): ";
			unsigned int index = GetCorrectIndex(FindMaxID(mapTruba));
			n = mapTruba.find(index);
			n->second.EditTruba();
			break;
		}
		case 4:
		{
			cout << "Enter index(1-" << mapCKS.size() << "): ";
			unsigned int index = GetCorrectIndex(FindMaxID(mapCKS));
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
			if (mapTruba.size() != 0 || mapCKS.size() != 0)
				SaveData(mapTruba, mapCKS);
		}
		case 8:
		{
			LoadData(mapTruba, mapCKS);
		}
		
		case 9:
		{
			unordered_map <int, Truba>::iterator iter ;
			cout << endl << "ID Pipe to delite: (1-" << mapTruba.size() <<")";
			int id = GetCorrectNumber(FindMaxID(mapTruba));
			iter=mapTruba.find(id);
			mapTruba.erase(iter);
			break;
		}
		case 10:
		{
			unordered_map <int, CKS>::iterator iter;
			cout << endl << "ID KS to delete: (1-" << mapCKS.size() << ")";
			int id = GetCorrectNumber(FindMaxID(mapCKS));
			iter = mapCKS.find(id);
			mapCKS.erase(iter);
			for (int& i : FindTrubaByFilter<int>(mapTruba, CheckByID_in, id))
					mapTruba.erase(i);
			for (int& i : FindTrubaByFilter<int>(mapTruba, CheckByID_out, id))
				mapTruba.erase(i);
			break;
		}
		case 11:
		{
			double param;
			cout << "Search for pipe by length ";
			cin >> param;
			for (int i : FindTrubaByFilter<double>(mapTruba, CheckByLength, param))
				cout << mapTruba[i];
			break;
		}
		case 12:
		{
			cout << "Type status: ";
			for (int i : FindTrubaByFilter(mapTruba, CheckByRemont, true))
				cout << mapTruba[i];
			break;
		}
		case 13:
		{
			string name;
			cout << "Search for compressor by name  ";
			cin >> name;
			for (int i : FindCKSByFilter<string>(mapCKS, CheckByName, name))
				cout << mapCKS[i];
			break; 
		}
		case 14:
		{
			double param;
			cout << "Percentage of non-working workshops ";
			param = GetCorrectNumber(100.0);
			for (int i : FindCKSByFilter<double>(mapCKS, CheckByProcent, param))
				cout << mapCKS[i];
			break;
		}
		case 15:
		{
			double x, y;
			cout << "Edit pipe's lenght :";
			x = GetCorrectNumber(2000.0);
			cout << "Edit pipe's diametr: ";
			y = GetCorrectNumber(2000.0);
			for (int i : FindTrubaByFilter<double>(mapTruba, CheckByLength, x))
			{
				if (mapTruba[i].get_length() == x && mapTruba[i].get_diameter() == y)
				            mapTruba[i].EditTruba();
			}
		break;
		}
		case 16:
		{

			unordered_map <int, Truba> ::iterator n;
			int id_out;
			int id_in;
			cout << "Truba ID, which connected KSs: ";
			int index = GetCorrectNumber(Truba::IDT);
			n = mapTruba.find(index);
			if (n == mapTruba.end() || (n->second.get_id_out() != 0))
				cout << "Truba with this ID is not found or used\n";
			else
			{
				cout << "Truba out (KS ID): ";
				id_out = GetIDKS(mapCKS);
				cout << "Truba in (KS ID): ";
				id_in = GetIDKS(mapCKS);
				n->second.Truba_in_out(id_out, id_in);
			}
			break;
		}
		case 17:
		{
			graph = Graph(graph, mapCKS, mapTruba, id_KS);
			PrintGraph(graph);
			break;
		}
		case 18:
		{
			graph = Graph(graph, mapCKS, mapTruba, id_KS);
			PrintGraph(graph);
			vector<int> ans;
			topol_sort(graph, ans);
			for (auto index = ans.begin(); index != ans.end(); index++)
			{
				cout << *index;
				if (index + 1 != ans.end()) cout << " > ";
			}
			break;
		}
		case 21:
		{
			graph = Graph(graph, mapCKS, mapTruba, id_KS);
			Potok(graph, mapCKS, mapTruba, id_KS);
			break;
		}
		case 22:
		{
			graph = Graph(graph, mapCKS, mapTruba, id_KS);
			Puti(graph, mapCKS, mapTruba, id_KS);
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
