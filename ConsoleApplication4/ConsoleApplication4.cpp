#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>

using namespace std;


void filesize(string file_name) 
{
    int x;
    ifstream fin;
    fin.open(file_name, ios::binary | ios::ate);
    x = fin.tellg();
    fin.close();
}


void thread_f (string file_name, vector<int>& vec, mutex& m1, mutex& m2, mutex& m3) 
{
	ifstream fin;
	int x;
	auto start = chrono::system_clock::now();
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

	m2.lock();  //захватываем мьютекс на время поиска минимума
	int min = vec[0];
	for (int i = 1; i < vec.size(); i++)  //нахождение минимума 
	{
		if (vec[i] <= min) 
			min = vec[i];
		
	}
	m2.unlock(); // теперь другой поток может выполнять прошлую часть кода

	auto end = chrono:: system_clock::now();
	chrono::duration<double> sec = end - start;
	m3.lock(); // захват мьютекса перед выводом в консоль, чтобы информация не смешивалась
	cout << "Time for thread " + file_name + ": " << sec.count() << " sec " << endl;
	filesize(file_name);
	m3.unlock(); // теперь другой поток может записать в консоль
}

int main(int argc, char* argv[]) 
{
	vector<int> vec;
	mutex m1;
	mutex m2;
	mutex m3;
	if (argc == 2) 
	{
		thread ta(thread_f, argv[1], ref(vec), ref(m1), ref(m2), ref(m3));
		ta.join();
	}
	else if (argc == 3) 
	{
		thread ta(thread_f, argv[1], ref(vec), ref(m1), ref(m2), ref(m3));
		thread tb(thread_f, argv[2], ref(vec), ref(m1), ref(m2), ref(m3));
		ta.join();
		tb.join();
	}
	else if (argc == 4) 
	{
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


