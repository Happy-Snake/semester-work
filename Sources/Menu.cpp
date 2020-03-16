#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <iostream>

#include "../Headers/Menu.h"


extern int color_of_background;
extern int color_of_text;
extern int color_of_bits;

using namespace std;



void Control_keys(int &code, int &key)		//Считывание управляющих символов для основных пунктов меню
{
	code = _getch();
	if (code == 224)
	{
		code = _getch();
		if (code == 80) key++;
		if (code == 72) key--;
	}
};

void draw_menu(const char **menuItems, int sz, int current)		//Вывод позиций меню
{
	for (int i = 0; i < sz; ++i)
		cout << setw(3) << (current == i ? "->" : "") << menuItems[i] << endl;
};

int main_menu()			//Главное меню с выбором типа данных для работы
{
	SetConsoleOutputCP(1251);
	int key = 0;
	int *keyptr = &key;
	int code;
	const char *items[] = { "unsigned char", "char", "short int", "unsigned short int", "int", "unsigned int",
	"long", "unsigned long", "long long", "unsigned long long", "float", "double", "long double", "Выбрать цвет", "Выход" };
	do
	{
		system("cls");
		cout << "Выберите тип данных:" << endl;
		key = (key + 15) % 15;
		draw_menu(items, 15, key);
		Control_keys(code, key);
	} while (code != 13);
	system("cls");
	return key;
};

int num_syst()			//Ввод системы счисления - ограничение до 62х
{
	cout << "Введите систему счисления от 2 до 62: ";
	int syst = 0;
	int code = 0;
	do
		code = _getch();
	while (code <= 48 or code >= 58);
	syst = code - 48;
	cout << syst;
	if (syst == 6)
		do
			code = _getch();
	while ((code <= 47 or code >= 51) and code != 13);
	else
		if (syst == 1)
			do 
				code = _getch();
		while (code == 13);
		else
			if (syst < 6)
				do
					code = _getch();
				while ((code <= 47 or code >= 58) and code != 13);
			else
				do
					code = _getch();
				while (code != 13);
	if (code != 13)
	{
		syst = syst * 10 + code - 48;
		cout << code - 48;
	}
	cout << endl;
	return syst;
};


int size_of_bits(int bytes)			//Ввод кол-ва бит для работы. Ограницено половиной общего количества битов 
{
	cout << "Введите количество битов, с которым хотите работать: ";
	int lim = bytes * 8 / 2;
	int size = 0;
	int code = 0;
	do
		code = _getch();
	while (code <= 48 or code >= 58 or code >= lim + 49);
	cout << code - 48;
	size = code - 48;
	if (lim >= 10)
	{
		lim = lim - (code - 48) * 10;
		do
			code = _getch();
		while ((code < 48 or code >= 58 or code >= lim + 49) and code != 13);
		if (code != 13)
		{
			cout << code - 48;
			size = size * 10 + code - 48;
		}
	}
	return size;
}

void new_control_keys(int& code, int& pos1, int& pos2, int lim, int num)	//Считывание управляющих символов для выбора позиций битов
{
	code = _getch();
	if ((code == 65 or code == 97 or code == 228 or code == 148) and pos1 > 0) pos1--;
	if ((code == 68 or code == 100 or code == 130 or code == 162) and pos1 < pos2 - num) pos1++;
	if (code == 75 and pos1 < pos2 - num) pos2--;
	if (code == 77 and pos2 <= lim - num) pos2++;
};

void draw_menu_for_colors(const char** menuItems, int sz, int current)		//Вывод позиций меню
{
	for (int i = 0; i < sz - 1; ++i)
	{
		if (i == color_of_background)
		{
			//++current;
			//++i;
			__asm {
				mov         eax, current		//Копируем current в eax
				inc			eax					//Добавляем 1 в eax
				mov         current, eax		//Записываем eax обратно в current

				mov         eax, i
				inc         eax
				mov         i, eax
			}
		}
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(i));
		cout << setw(3) << (current == i ? "->" : "");
		cout << menuItems[i] << endl;
	}
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(color_of_text));
	cout << setw(3) << (current == sz-1 ? "->" : "");
	cout << menuItems[sz - 1] << endl;
};

int color_menu()		//Меню с выбора цвета
{
	SetConsoleOutputCP(1251);
	int key = 0;
	int code;
	const char *items[] = { "Черный", "Синий", "Зеленый", "Голубой", "Красный", "Фиолетовый",
	"Коричневый", "Светло - серый", "Темно - серый", "Свело - синий", "Светло - зеленый", "Светло - голубой",
	"Cветло - красный", "Светло-фиолетовый", "Желтый", "Выход" };
	do
	{
		system("cls");
		cout << "Выберите цвет:" << endl;
		key = (key + 15) % 15;
		draw_menu_for_colors(items, 16, key);
		Control_keys(code, key);
	} while (code != 13);
	system("cls");
	if (color_of_background > key or key == 14)
		return key;
	else
		return key+1;
};

int which_color_to_choose()		//Меню с выбора, какой цвет менять
{
	SetConsoleOutputCP(1251);
	int key = 0;
	int code;
	const char *items[] = { "Первая группа битов", "Вторая группа битов", "Остальной текст", "Основные биты", "Фон", "Выход" };
	do
	{
		system("cls");
		cout << "Выберите элемент консоли для изменения цвета:" << endl;
		key = (key + 6) % 6;
		draw_menu(items, 6, key);
		Control_keys(code, key);
	} while (code != 13);
	system("cls");
	return key;
}

void draw_bits(std::string str, int num, int pos1, int pos2)		//Вывод битов по строке
{
	for (int i = 0; i < str.length(); i++)
	{
		if (i >= pos1 and i < pos1 + num)
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(color1));
			cout << str[i];
		}
		else
			if (i >= pos2 and i < pos2 + num)
			{
				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(color2));
				cout << str[i];
			}
			else
			{
				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(color_of_bits));
				cout << str[i];
			}
		if ((i + 1) % 8 == 0 and i != 0)
			cout << ' ';
	}
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (short)(color_of_background << 4) | (short)(color_of_text));
	std::cout << std::endl;
}