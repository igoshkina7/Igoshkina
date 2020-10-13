// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct truba //структура
{
	int id;   //идентификатор
	double length;  
	int diameter;
	bool remont;  //на ремонте или нет
};

struct compressor 
{
	int id;
	string name;
	int kolvo_workshops;  //количество цехов
	int kolvo_in_work;  //количество цехов в работе
	double effect;  // эффективность
};

bool check (int x)
{
	return x > 0 ? true : false;  //тернарная операция для проверки
}
bool check (double x) 
{
	return x > 0 ? true : false;
}

truba create_pipe() 
{
	truba new_pipe;
	do 
	{
		cin.clear();  //возвращает cin в обычное состояние
		cin.ignore(99999, '\n'); //удаляем значения предыдущего входа
		cout << "Vvedite diameter: " << endl;
		cin >> new_pipe.diameter;
		cout << "Vvedite dliny: " << endl;
		cin >> new_pipe.length;
	} 
	while (cin.fail() || !check (new_pipe.diameter) || !check(new_pipe.length)); //пока не выйдет некорректное значение либо с помощью функции check лиюо cin

	new_pipe.id = 1;
	new_pipe.remont = false;
	return new_pipe;
}

compressor create_compressor() 
{
	compressor new_compressor;
	cout << "Vvedite naimenovanie: " << endl;
	cin >> new_compressor.name;
	do 
	{
		cin.clear();
		cin.ignore(99999, '\n');
		cout << "Vvedite kol-vo cehov: " << endl;
		cin >> new_compressor.kolvo_workshops;
		cout << "Vvedite kol-vo raboch cehov: " << endl;
		cin >> new_compressor.kolvo_in_work;
		cout << "Vvedite effect: " << endl;
		cin >> new_compressor.effect;
	} 
	while (cin.fail() || !check (new_compressor.kolvo_workshops) || !(check(new_compressor.kolvo_in_work) && (new_compressor.kolvo_in_work <= new_compressor.kolvo_workshops)) || !check(new_compressor.effect));

	new_compressor.id = 1;
	return new_compressor;
}

void change_status(bool& status) //меняем статус трубы
{
	status = !status;
}

void write_dataT(const truba& t) //ввод данных
{
	cout << "Diameter: " << t.diameter << endl;
	cout << "Dlina: " << t.length << endl;
	cout << "id: " << t.id << endl;
	cout << (t.remont ? "V remonte" : "Ne v remonte") << endl;
}

void write_dataC(const compressor& comp) 
{
	cout << "Naimenovanie: " << comp.name << endl;
	cout << "Kol-vo cehov: " << comp.kolvo_workshops << endl;
	cout << "Kol-vo raboch cehov: " << comp.kolvo_in_work << endl;
	cout << "Effectivnost: " << comp.effect << endl;
}

void save_to_fileT(const truba& t) //сохранение в файл
{
	ofstream fout;
	fout.open("dataTruba.txt", ios_base::out);
	if (fout.is_open())
	{
		fout << "Identificator " << t.id << endl << "Diametr " << t.diameter << endl << "Dlina " << t.length << endl << (t.remont ? "V remonte" : "Ne v remonte");
	}
	else cout << "Error";
}
void save_to_fileC(const compressor& comp) 
{
	ofstream fout;
	fout.open("dataCompr.txt", ios_base::out);
	if (fout.is_open())
	{
		fout << "Identificator " << comp.id << endl << "Naimenovanie " << comp.name << endl << "Kol-vo cehov " << comp.kolvo_workshops << endl << "Kol-vo rabochix cehov " << comp.kolvo_in_work << endl << "Effectivnost " << comp.effect;
		fout.close();
	}
	else cout << "Error";
}

truba load_from_fileT() 
{
	ifstream fin;
	fin.open("dataTruba.txt", ios_base::in);
	truba t;
	if (fin.is_open()) 
	{
		fin >> t.id;
		fin >> t.diameter;
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
	fin.open("dataCompr.txt", ios_base::in);
	compressor comp;
	if (fin.is_open()) 
	{
		fin >> comp.id;
		fin >> comp.name;
		fin >> comp.kolvo_workshops;
		fin >> comp.kolvo_in_work;
		fin >> comp.effect;
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
		cout << "Select action:" << endl;
		PrintMenu();
		cin >> i;
		switch (i)
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

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
