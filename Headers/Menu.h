#pragma once
#include <stdio.h>
#include <windows.h>


#include "../Headers/Func.h"


extern int color1;		//Цвет первой группы битов
extern int color2;		//Цвет второй группы битов
extern int color_of_text;		//Цвет остального текста
extern int color_of_background;		//Цвет фона

template <class T>		//Объединение для нахождения байтового представления переменной
union un1
{
	T value;
	char bytes[sizeof(T)];
};


void Control_keys(int &code, int &key);		//Считывание управляющих символов для основных пунктов меню

void draw_menu(const char **menuItems, int sz, int current);	//Вывод позиций меню

int main_menu();			//Главное меню с выбором типа данных для работы

int num_syst();			//Ввод системы счисления - ограничение до 62х

int size_of_bits(int bytes);		//Ввод кол-ва бит для работы. Ограницено половиной общего количества битов 

void new_control_keys(int& code, int& pos1, int& pos2, int lim, int num);		//Считывание управляющих символов для выбора позиций битов

int color_menu();		//Меню с выбора цвета

int which_color_to_choose();		//Меню с выбора, какой цвет менять

void draw_bits(std::string str, int num, int pos1, int pos2);

template <typename T>
void draw_new_menu(int syst, T var, std::string bits_str, std::string str_var)
{
	int num = size_of_bits(sizeof(var));
	int code = 0;
	int pos1 = 0;
	int pos2 = sizeof(var) * 8 / 2;
	do
	{
		system("cls");
		std::cout << "Вы ввели число " << str_var << " в " << syst << "чной системе счисления" << std::endl <<
			"Это число в 10чной системе счисления: " << var << std::endl <<
			"Выделите " << num << " битов, которые хотите поменять. Для смещения левой группы битов, спользуйте A и D, для смещения правой группы битов используйте <- и -> :";
		std::cout << std::endl;
		draw_bits(bits_str, num, pos1, pos2);//09918C5h
		new_control_keys(code, pos1, pos2, sizeof(var) * 8 - 1, num);//09918EDh
	} while (code != 13);
	std::string new_bits_str = swap_bits(num, pos1, pos2, bits_str);//0991703h
	T new_var = rev_main_func(var, new_bits_str);
	std::string new_str = make_str(new_var);
	draw_bits(new_str, num, pos2, pos1);
	std::cout << "Получилось число: " << new_var << std::endl;
	draw_graphp(bits_str, new_bits_str);
}

template <typename T>
void draw_new_menu_for_char(T var, std::string bits_str)
{
	int num = size_of_bits(sizeof(var));
	int code = 0;
	int pos1 = 0;
	int* pcode = &code;
	int* pnum = &num;
	int* ppos1 = &pos1;

	int pos2 = sizeof(var) * 8 / 2;
	do
	{
		system("cls");
		std::cout << "Вы ввели символ " << var << std::endl <<
			"Выделите " << num << " битов, которые хотите поменять. Для смещения правой группы битов, спользуйте A и D, для смещения левой группы битов используйте <- и -> :";
		std::cout << std::endl;
		draw_bits(bits_str, num, pos1, pos2);
		new_control_keys(code, pos1, pos2, sizeof(var) * 8 - 1, num);
	} while (code != 13);
	std::string new_bits_str = swap_bits(num, pos1, pos2, bits_str);
	T new_var = rev_main_func(var, new_bits_str);
	std::string new_str = make_str(new_var);
	draw_bits(new_bits_str, num, pos2, pos1);
	std::cout << "Получился символ: " << new_var << std::endl;
	draw_graphp(bits_str, new_bits_str);
}