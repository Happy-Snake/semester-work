#pragma once
#include <stdio.h>
#include <windows.h>


#include "../Headers/Func.h"


extern int color1;		//���� ������ ������ �����
extern int color2;		//���� ������ ������ �����
extern int color_of_text;		//���� ���������� ������
extern int color_of_background;		//���� ����

template <class T>		//����������� ��� ���������� ��������� ������������� ����������
union un1
{
	T value;
	char bytes[sizeof(T)];
};


void Control_keys(int &code, int &key);		//���������� ����������� �������� ��� �������� ������� ����

void draw_menu(const char **menuItems, int sz, int current);	//����� ������� ����

int main_menu();			//������� ���� � ������� ���� ������ ��� ������

int num_syst();			//���� ������� ��������� - ����������� �� 62�

int size_of_bits(int bytes);		//���� ���-�� ��� ��� ������. ���������� ��������� ������ ���������� ����� 

void new_control_keys(int& code, int& pos1, int& pos2, int lim, int num);		//���������� ����������� �������� ��� ������ ������� �����

int color_menu();		//���� � ������ �����

int which_color_to_choose();		//���� � ������, ����� ���� ������

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
		std::cout << "�� ����� ����� " << str_var << " � " << syst << "���� ������� ���������" << std::endl <<
			"��� ����� � 10���� ������� ���������: " << var << std::endl <<
			"�������� " << num << " �����, ������� ������ ��������. ��� �������� ����� ������ �����, ���������� A � D, ��� �������� ������ ������ ����� ����������� <- � -> :";
		std::cout << std::endl;
		draw_bits(bits_str, num, pos1, pos2);//09918C5h
		new_control_keys(code, pos1, pos2, sizeof(var) * 8 - 1, num);//09918EDh
	} while (code != 13);
	std::string new_bits_str = swap_bits(num, pos1, pos2, bits_str);//0991703h
	T new_var = rev_main_func(var, new_bits_str);
	std::string new_str = make_str(new_var);
	draw_bits(new_str, num, pos2, pos1);
	std::cout << "���������� �����: " << new_var << std::endl;
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
		std::cout << "�� ����� ������ " << var << std::endl <<
			"�������� " << num << " �����, ������� ������ ��������. ��� �������� ������ ������ �����, ���������� A � D, ��� �������� ����� ������ ����� ����������� <- � -> :";
		std::cout << std::endl;
		draw_bits(bits_str, num, pos1, pos2);
		new_control_keys(code, pos1, pos2, sizeof(var) * 8 - 1, num);
	} while (code != 13);
	std::string new_bits_str = swap_bits(num, pos1, pos2, bits_str);
	T new_var = rev_main_func(var, new_bits_str);
	std::string new_str = make_str(new_var);
	draw_bits(new_bits_str, num, pos2, pos1);
	std::cout << "��������� ������: " << new_var << std::endl;
	draw_graphp(bits_str, new_bits_str);
}