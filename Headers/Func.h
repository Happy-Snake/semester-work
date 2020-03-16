#pragma once
#include <iostream>
#include <string>

//#include "../Headers/Menu.h"

class point
{
public:
	int x, y, prev_y, new_y;
	bool move;

	point(int x, int y, int prev_y, int new_y, bool direct);

	void draw_point();

	void draw_new_point(int prev_y, int next_y);
};

int lim(int syst);		//Определение верхнего возможного кода символа для данной с.сч.

int delt(int var);		//Определение величины, которую небходимо вычесть из кода символа, чтобы получить число, которе он обозначает

std::string swap_bits(int size, int first, int second, std::string new_str);		//Ф-я, меняющая указанные группы бит местами

void draw_available_symbols(int syst);

void draw_graphp(std::string str, std::string new_str);

template <class T>		//Объединение для нахождения побитового представления переменной
union un
{
	T value;

	char bytes[sizeof(T)];
};

template <typename T>		//Побитовый вывод 
std::string make_str(T &var)
{
	un<T> v;
	v.value = var;
	std::string str;
	for (int i = sizeof(var) - 1; i >= 0; i--)
	{
		for (int j = 7; j >= 0; j--)
		{
			if ((v.bytes[i] >> j) & 1)
				str += '1';
			else
				str += '0';
		}
	}
	return str;
};

template <typename T>
void make_num(std::string arr, T &var, int syst)		//По строке делаем число
{
	double r = 1.0 / syst;
	bool integ = true;
	for (int i = 0; arr[i] != '\0'; i++)
	{
		if (((arr[i] >= 48 and arr[i] <= 57) or (arr[i] >= 65 and arr[i] <= 90) or (arr[i] >= 97 and arr[i] <= 122)) and integ)

			var = var * syst + arr[i] - delt(arr[i]);
		else
			if (((arr[i] >= 48 and arr[i] <= 57) or (arr[i] >= 65 and arr[i] <= 90) or (arr[i] >= 97 and arr[i] <= 122)) and !integ and (typeid(T) == typeid(double) or typeid(T) == typeid(float) or typeid(T) == typeid(long double)))
			{
				var = var + (arr[i] - delt(arr[i])) * r;
				r /= syst;
			}
			else
				if ((arr[i] == 44 or arr[i] == 46) and integ and (typeid(T) == typeid(double) or typeid(T) == typeid(float) or typeid(T) == typeid(long double)))
					integ = false;
	}
	if (arr[0] == '-')
		var = var * (-1);
}

template <typename T>
void input_char(T &var)		//Ввод символьных переменных
{
	std::cout << "Введите символ: ";
	var = _getch();
	std::cout << var << std::endl;
};

template <typename T>
std::string input_num(T &var, int syst, bool us = false)		//Ввод числовых переменных
{
	std::string arr;
	std::cout << "Вы можете ипользовать следующие символы: ";
	draw_available_symbols(syst);
	std::cout << std::endl << "Введите число: ";
	unsigned char code = _getch();
	int limit = lim(syst);
	bool integ = true;
	while (code != 13)
	{
		if (((code >= 48 and code <= 57) or (code >= 65 and code <= 90) or (code >= 97 and code <= 122)) and code <= limit and integ)
		{
			std::cout << code;
			arr += code;
		}
		else
			if (((code >= 48 and code <= 57) or (code >= 65 and code <= 90) or (code >= 97 and code <= 122)) and code <= limit and !integ and (typeid(T) == typeid(double) or typeid(T) == typeid(float) or typeid(T) == typeid(long double)))
			{
				std::cout << code;
				arr += code;
			}
			else
				if ((code == 44 or code == 46) and integ and (typeid(T) == typeid(double) or typeid(T) == typeid(float) or typeid(T) == typeid(long double)))
				{
					std::cout << code;
					integ = false;
					arr += code;
				}
				else
					if (code == 8 and arr.length())
					{
						std::cout << "\b \b";
						if (arr[arr.size() - 1] == 44 or arr[arr.size() - 1] == 46)
							integ = true;
						arr.pop_back();
					}
					else
						if (code == 45 and !us and arr.length() == 0)
						{
							arr += code;
							std::cout << code;
						}
		code = _getch();
	}
	arr += '\0';
	make_num(arr, var, syst);
	std::cout << std::endl;
	return arr;
}


template <class T>
T rev_main_func(T var, std::string new_str)	
{
	un<T> v;
	v.value = 0;
	for (int i = sizeof(var) - 1; i >= 0; i--)
	{
		for (int j = 8; j > 0; j--)
		{
			if (new_str[(sizeof(var) - i) * 8 - j] == '1')
				v.bytes[i] |= (1 << j - 1);
			else
				v.bytes[i] &= ~(1 << j - 1);
		}
	}
	std::cout << std::endl;
	return v.value;
}