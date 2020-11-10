// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

void filesize(string file_name) 
{
    int x;
    ifstream fin;
    fin.open(file_name, ios::binary | ios::ate);
    x = fin.tellg();
    fin.close();
    cout << "Razmer " << file_name << " : " << x << " byte" << endl;
}


void thread_f (string file_name, vector<int>& vec, mutex& m1, mutex& m2, mutex& m3) 
{
	ifstream fin;
	int x;
	auto start = system_clock::now();
	fin.open(file_name, ios::in);
	if (fin.is_open())  //считываем файл
	{   
		while (fin >> x)
		{
			m1.lock();   // захватываем мьютекс для вставки элемента в конец вектора
			vec.push_back(x); //добавление нового элемента
			m1.unlock();// теперь другой поток может добавить элемент в вектора
		}
		fin.close();
	}

	m2.lock();  //захватываем мьютекс на время поиска максимума
	int min = vec[0];
	for (int i = 1; i < vec.size(); i++)  //нахождение максимума 
	{
		if (vec[i] <= min) 
			min = vec[i];
		
	}
	m2.unlock(); // теперь другой поток может выполнять прошлую часть кода

	auto end = system_clock::now();
	duration<double> sec = end - start;
	m3.lock(); // захват мьютекса перед выводом в консоль, чтобы информация не смешивалась
	cout << "Work time: " << sec.count() << " sec " << endl;
	cout << "Min: " << min << endl;
	filesize(file_name);
	m3.unlock(); // теперь другой поток может записать в консоль
}

int main(int argc, char* argv[]) 
{
	vector<int> vec;
	mutex m1;
	mutex m2;
	mutex m3;
	if (argc == 2) {
		thread ta(thread_f, argv[1], ref(vec), ref(m1), ref(m2), ref(m3));
		ta.join();
	}
	else if (argc == 3) {
		thread ta(thread_f, argv[1], ref(vec), ref(m1), ref(m2), ref(m3));
		thread tb(thread_f, argv[2], ref(vec), ref(m1), ref(m2), ref(m3));
		ta.join();
		tb.join();
	}
	else if (argc == 4) {
		thread ta(thread_f, argv[1], ref(vec), ref(m1), ref(m2), ref(m3));
		thread tb(thread_f, argv[2], ref(vec), ref(m1), ref(m2), ref(m3));
		thread tc(thread_f, argv[3], ref(vec), ref(m1), ref(m2), ref(m3));
		ta.join();
		tb.join();
		tc.join();
	}
	else {
		cout << "too many arguments" << endl;
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
