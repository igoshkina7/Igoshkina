#pragma once
#include <iostream>
#include <unordered_map>

template <typename T> //для ввода переменой любого типа после 
T GetCorrectIndex(T max)
{
	T x;
	while ((std::cin >> x).fail() || x < 0 || x > max)
	{
		std:: cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type again (" << 0 << "-" << max << "):";
	}
	return x;
}

template <typename T> //для ввода переменой любого типа после 
T GetCorrectNumber(T max)
{
	T x;
	while ((std::cin >> x).fail() || x <= 0 || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type again (" << 0 << "-" << max << "):";
	}
	return x;
}


template <typename T>
int FindMaxID(const unordered_map<int, T>& t)
{
	int MaxID = -100;
	for (const auto& i : t)
		if (i.second.get_id() > MaxID)
			MaxID = i.second.get_id();
	return MaxID;
}

template <typename T, typename K>
void SaveData(const unordered_map<int, T>& mapt, const unordered_map<int, K>& mapk)
{
	fstream fout;
	string filename;
	cout << "Filename: ";
	cin >> filename;
	fout.open(filename + ".txt", fstream::out);
	if (fout.is_open()) {
		fout << mapt.size() << endl << mapk.size() << endl;
		for (const auto& it : mapt)
		{
			fout << it.second << endl;
		}
		for (const auto& itk : mapk)
		{
			fout << itk.second << endl;
		}
		fout.close();
	}
}

template <typename T, typename K>
void LoadData(unordered_map<int, T>& mapt, unordered_map<int, K>& mapk)
{
	fstream fin;
	int countt;
	int countk;
	unordered_map<int, T> mapt2;
	unordered_map<int, K> mapk2;
	string filename;
	cout << "Filename: ";
	cin >> filename;
	fin.open(filename + ".txt", fstream::in);
	if (fin.is_open()) {
		fin >> countt >> countk;
		while (countt--)
		{
			T p(fin);
			mapt2.insert(pair<int, T>(p.get_id(), p));
		}
		while (countk--)
		{
			K p(fin);
			mapk2.insert(pair<int, K>(p.get_id(), p));
		}

		fin.close();
		mapt = mapt2;
		mapk = mapk2;
	}
}

