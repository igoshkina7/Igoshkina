#pragma once
#include <iostream>

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