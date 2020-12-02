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
		if (i.second.set_id() > MaxID)
			MaxID = i.second.set_id();
	return MaxID;
}



