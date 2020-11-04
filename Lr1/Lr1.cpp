// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct truba //структура
{
	double length;
	int diametr;
	bool remont;  //на ремонте или нет
};

struct compressor
{
	string name;
	int kolvo_workshops;  //количество цехов
	int kolvo_workshops_in_work;  //количество цехов в работе
	double effciency;  // эффективность
};

template <typename T>
T check(T x)
{
	return x > 0 ? true : false;  //тернарная операция для проверки
}

template <typename T>
T GetCorrectNumber(T max)
{
	T x;
	while ((cin >> x).fail() || x <= 0 || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type again (" << 0 << "-" << max << "):";
	}
	return x;
}

template <typename T>
T GetCorrectIndex(T max)
{
	T x;
	while ((cin >> x).fail() || x < 0 || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type again (" << 0 << "-" << max << "):";
	}
	return x;
}


truba create_pipe()
{
	truba new_p;
	cout << "Type length: " << endl;
	new_p.length = GetCorrectNumber(1000.0); //òèï double çà ñ÷åò òî÷êè
	cout << " Type diametr: " << endl;
	new_p.diametr = GetCorrectNumber(2000.0);
	new_p.remont = false;
	return new_p;
}

compressor create_compressor()
{
	compressor new_c;
	cout << "Type name: " << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, new_c.name);
	cout << "Type number of workshops: " << endl;
	new_c.kolvo_workshops = GetCorrectNumber(100);
	cout << "Type number of workshops in work: " << endl;
	new_c.kolvo_workshops_in_work = GetCorrectNumber(new_c.kolvo_workshops);
	cout << "Type effciency: " << endl;
	new_c.effciency = GetCorrectNumber(10.0);
	return new_c;
}

void change_status(bool& status) //меняем статус трубы
{
	status = !status;
}

void write_dataT(const truba& t) //ввод данных
{
	cout << "Diameter: " << t.diametr << endl;
	cout << "Length: " << t.length << endl;
	cout << (t.remont ? "V remonte" : "Ne v remonte") << endl;
}

void write_dataC(const compressor& comp)
{
	cout << "Name: " << comp.name << endl
		<< "Number of workshops: " << comp.kolvo_workshops << endl
		<< "Number of workshops in work: " << comp.kolvo_workshops_in_work << endl
		<< "Effiency: " << comp.effciency << endl;
}

void save_to_fileT(const truba& t) //сохранение в файл
{
	ofstream fout;
	fout.open("dataTruba.txt", ios::out);
	if (fout.is_open())
	{
		fout << "Diametr " << t.diametr << endl << "Length " << t.length << endl << (t.remont ? "V remonte" : "Ne v remonte");
	}
	else cout << "Error";
}
void save_to_fileC(const compressor& comp)
{
	ofstream fout;
	fout.open("dataCompr.txt", ios::out);
	if (fout.is_open())
	{
		fout << "Name:  " << comp.name << endl << "Number of workshops: " << comp.kolvo_workshops << endl << "Number of workshops in work: " << comp.kolvo_workshops_in_work << endl << "Effiency: " << comp.effciency;
		fout.close();
	}
	else cout << "Error";
}

truba load_from_fileT()
{
	ifstream fin;
	fin.open("dataTruba.txt", ios::in);
	truba t;
	if (fin.is_open())
	{
		fin >> t.diametr;
		fin >> t.length;
		fin >> t.remont;
		fin.close();
		return t;
	}
	else cout << "Error";
}

compressor load_from_fileC()
{
	ifstream fin;
	fin.open("dataCompr.txt", ios::in);
	compressor comp;
	if (fin.is_open())
	{
		fin >> comp.name;
		fin >> comp.kolvo_workshops;
		fin >> comp.kolvo_workshops_in_work;
		fin >> comp.effciency;
		fin.close();
		return comp;

	}
	else cout << "Error";
}


void PrintMenu()
{
	cout << "1. Create pipe" << endl;
	cout << "2. Create compressor" << endl;
	cout << "3. Change pipe status" << endl;
	cout << "4. Print pipe info" << endl;
	cout << "5. Print compressor info" << endl;
	cout << "6. Save pipe to file" << endl;
	cout << "7. Save compressor to file" << endl;
	cout << "8. Load pipe's info" << endl;
	cout << "9. Load compressor's info" << endl;
	cout << "0. Exit" << endl;
}

int main()
{
	compressor comp;
	truba t;
	int i;
	while (1)
	{
		PrintMenu();
		cout << "Select action:" << endl;

		switch (GetCorrectIndex(10))
		{
		case 1:
			t = create_pipe();
			break;
		case 2:
			comp = create_compressor();
			break;
		case 3:
			change_status(t.remont);
			break;
		case 4:
			write_dataT(t);
			break;
		case 5:
			write_dataC(comp);
			break;
		case 6:
			save_to_fileT(t);
			break;
		case 7:
			save_to_fileC(comp);
			break;
		case 8:
			load_from_fileT();
			break;
		case 9:
			load_from_fileC();
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "Select valid action: " << endl;
			break;
		}

	}

}