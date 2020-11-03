#include <iostream>
#include <vector>
#include <fstream>
//#include "Student.h"
//#include "utils.h"

using namespace std;

struct Truba   //создание нового класса
{
	string name;
	double diametr;
	double length;
	bool remont;
};

struct Compressor   //создание нового класса
{
	string name;
	int kolvo_workshops;
	int kolvo_workshops_in_work;
	double efficiency;
};



Truba LoadTruba (ifstream& fin)
{
	Truba t;
	fin >> t.name;
	fin >> t.length;
	fin >> t.diametr;
	return t;
}

Compressor LoadCompressor(ifstream& fin)
{
	Compressor c;
	fin >> c.name;
	fin >> c.kolvo_workshops;
	fin >> c.kolvo_workshops_in_work;
	fin >> c.efficiency;
	return c;
}

ostream& operator << (ostream& out, const Truba& t)
{
	out << " Name: " << t.name
		<< "Length: " << t.length
		<< "Diametr: " << t.diametr << endl;
	return out;
}

istream& operator >> (istream& in, Truba& t)
{
	cout << "Type name: ";
	in >> t.name;
	cout << "Type length: ";
	t.length = CheckNumber(t.length);
	cout << "Type diametr: ";
	t.diametr = CheckNumber(t.diametr);
	return in;
}

ostream& operator << (ostream& out, const Compressor& c)
{
	out << " Name: " << c.name
		<< "Number of workshops: " << c.kolvo_workshops
		<< "Number of workshops in work: " << c.kolvo_workshops_in_work
		<< "Efficiency: " << c.efficiency << endl;
	return out;
}

istream& operator >> (istream& in, Compressor& c)
{
	cout << "Type name: ";
	in >> c.name;
	cout << "Type number of workshops: ";
	c.kolvo_workshops = CheckNumber(c.kolvo_workshops);
	cout << "Type number of workshops in work: ";
	c.kolvo_workshops_in_work = CheckNumber(c.kolvo_workshops_in_work);
	cout << "Type efficiency: ";
	//if (c.efficiency>0 && c.efficiency<1)
	c.efficiency = CheckNumber(c.efficiency);
	return in;
}

double CheckNumber(double x)
{
	
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> x;
	} while (cin.fail() || x < 0);
	return x;
}

int CheckNumber(int x)
{
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> x;
	} while (cin.fail() || x < 0);
	return x;
}

int GetCorrectNumber(int min, int max)
{
	int x;
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type number (" << min << "-" << max << ") :";
		cin >> x;
	} while (cin.fail() || x < min || x > max);
}

void SaveCompressor(ofstream& fout, const Compressor& c)
{
	fout << c.name << endl << c.kolvo_workshops << endl << c.kolvo_workshops_in_work << endl << c.efficiency << endl;
}

void SaveTruba(ofstream& fout, const Truba& t)
{
	fout << t.length << endl << t.diametr << endl;
}

//void EditStudent(Student& s)
//{
//	s.PassExam();
//	/*s.score -= 0.2;
//	s.score = IsScoreCorrect(s.score) ? s.score : 2;*/
//
//}

void change_status(Truba& t) 
{
	t.Edit_pipe();
}

void PrintMenu()
{
	cout << "1. Create pipe" << endl;
	cout << "2. Create compressor" << endl;
	cout << "3. Change pipe status" << endl;
	cout << "4. Print pipe's info" << endl;
	cout << "5. Print compressor's info" << endl;
	cout << "6. Save pipe to file" << endl;
	cout << "7. Save compressor to file" << endl;
	cout << "8. Load pipe's info" << endl;
	cout << "9. Load compressor's info" << endl;
	cout << "10. Add pipe" << endl;
	cout << "11. Add compressor" << endl;
	cout << "13. Search for pipe by name" << endl;
	cout << "14. Search for pipe by " << "v remonte" << " characteristic" << endl;
	cout << "15. Search for compressor by name" << endl;
	cout << "16. Search for compressor by percentage of non-working workshops" << endl;
	cout << "17. Batch editing" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose action: ";
}


Truba& SelectTruba(vector<Truba>& p)
{
	cout << "Enter pipe's index: ";
	unsigned int index = GetCorrectNumber(1u, p.size());
	return p[index - 1];
}

Compressor& SelectCompressor(vector<Compressor>& cs)
{
	cout << "Enter compressor's index: ";
	unsigned int index = GetCorrectNumber(1u, cs.size());
	return cs[index - 1];
}

//
//vector<int> FindPipeByName(const vector<Truba>& pipes, string name = "Unknown")
//{
//	vector <int> res;
//	int i = 0;
//	for (auto& t : pipes)
//	{
//		if (t.name == name)
//			res.push_back(i);
//		i++;
//	}
//
//	return res;
//}
//
//vector<int> FindCompressorByName(const vector<Compressor>& compressors, string name = "Unknown")
//{
//	vector <int> res;
//	int i = 0;
//	for (auto& c : compressors)
//	{
//		if (c.name == name)
//			res.push_back(i);
//		i++;
//	}
//
//	return res;
//}


//
//template<typename T>
//using Filter = bool(*)(const Student& s, T param);
//
//bool CheckByName(const Student& s, string param)
//{
//	return s.name == param;
//}
//bool CheckByScore(const Student& s, double param)
//{
//	return s.score >= param;
//}
//
//template<typename T>
//vector<int> FindStudentsByFilter(const vector<Student>& group, Filter<T> f, T param)
//{
//	vector <int> res;
//	int i = 0;
//	for (auto& s : group)
//	{
//		if (f(s, param))
//			res.push_back(i);
//		i++;
//	}
//
//	return res;
//}


int main()
{
	vector <Truba> pipes;
	vector <Compressor> ks;
	
	//vector <int> res;
	int i;
	/*double param;
	string name;*/

	while (1)
	{
		cout << "Select action:" << endl;
		PrintMenu();
		
		switch (GetCorrectNumber(17))
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
			Compressor compr;
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
			Compressor comprk;
			ofstream fout;
			fout.open("CS.txt", ios::out);
			if (fout.is_open())
			{
				fout << ks.size() << endl;
				for (Compressor compr : ks)
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
		case 10:
		{	
			Compressor compr;
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
