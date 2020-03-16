#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
#include <new>

#include "../Headers/Func.h"
#include "../Headers/Func.h"

using namespace std;

//	Black =  {12,12,12},
//	Blue =  {0,55,218},
//	Green = {19,161,14}, 
//	Cyan = {58,150,221}, 
//	Red = {197,15,31}, 
//	Magenta = {136,23,152},
//	Brown = {193,156,0},
//	Light_grey = {204,204,204}, 
//	Dark_grey = {118,118,118}, 
//	Light_blue = {59,120,255}, 
//	Light_green = {22,198,12},
//	Light_cyan = {97,214,214},
//	Light_red = {231,72,86}, 
//	Light_magenta = {180,0,158}, 
//	Yellow = {249,241,165}, 

int colors[15][3] = { {12,12,12}, {0,55,218}, {19,161,14}, {58,150,221}, {197,15,31}, {136,23,152}, {193,156,0},
						{204,204,204}, {118,118,118}, {59,120,255}, {22,198,12}, {97,214,214}, {231,72,86}, {180,0,158}, {249,241,165} };

int sleep_time = 50;

extern int color_of_background;
extern int color_of_bits;


point::point(int x, int y, int prev_y, int new_y, bool move)
{
	this->x = x;
	this->y = y;
	this->prev_y = prev_y;
	this->new_y = new_y;
	this->move = move;
};


void point::draw_point()
{
	POINT op;
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(colors[color_of_bits][0], colors[color_of_bits][1], colors[color_of_bits][2]));
	SelectObject(hDC, hPen);
	MoveToEx(hDC, x, prev_y, &op);
	LineTo(hDC, x, y);
	LineTo(hDC, x + 20, y);
	Sleep(100);
	ReleaseDC(hWnd, hDC);
}

void point::draw_new_point(int prev_y, int next_y)
{
	POINT op;
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	if (move)
		if (y > new_y)
			for (int i = y; i != new_y; i--)			//Подъем
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(colors[color_of_background][0], colors[color_of_background][1], colors[color_of_background][2]));
				SelectObject(hDC, hPen);
				MoveToEx(hDC, x, i, &op);
				LineTo(hDC, x + 21, i); 
				hPen = CreatePen(PS_SOLID, 1, RGB(colors[color_of_bits][0], colors[color_of_bits][1], colors[color_of_bits][2]));
				SelectObject(hDC, hPen);
				MoveToEx(hDC, x, prev_y, &op);
				LineTo(hDC, x, i - 1);
				MoveToEx(hDC, x, i - 1, &op);
				LineTo(hDC, x + 20, i - 1);
				MoveToEx(hDC, x + 20, next_y, &op);
				LineTo(hDC, x + 20, i - 1);
				MoveToEx(hDC, x + 20, i - 1, &op);
				Sleep(sleep_time);
			}
		else
			for (int i = y; i != new_y; i++)
			{
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(colors[color_of_background][0], colors[color_of_background][1], colors[color_of_background][2]));
				SelectObject(hDC, hPen);
				MoveToEx(hDC, x, i, &op);
				LineTo(hDC, x + 21, i);
				hPen = CreatePen(PS_SOLID, 1, RGB(colors[color_of_bits][0], colors[color_of_bits][1], colors[color_of_bits][2]));
				SelectObject(hDC, hPen);
				MoveToEx(hDC, x, prev_y, &op);
				LineTo(hDC, x, i + 1);
				MoveToEx(hDC, x, i + 1, &op);
				LineTo(hDC, x + 20, i + 1);
				MoveToEx(hDC, x + 20, next_y, &op);
				LineTo(hDC, x + 20, i + 1);
				MoveToEx(hDC, x + 20, i + 1, &op);
				Sleep(sleep_time);
			}
	ReleaseDC(hWnd, hDC);
}

int lim(int syst)		//Определение верхнего возможного кода символа для данной с.сч.
{
	int limit;
	if (syst <= 10)
		limit = 47 + syst;
	else
		if (syst <= 36)
			limit = 64 + syst - 10;
		else
			limit = 96 + syst - 36;
	return limit;
}

int delt(int var)		//Определение величины, которую небходимо вычесть из кода символа, чтобы получить число, которе он обозначает
{
	int del = 0;
	if (var >= 48 and var <= 57)
		del = 48;
	else
		if (var >= 65 and var <= 90)
			del = 55;
		else
			del = 61;
	return del;
}

string swap_bits(int size, int first, int second, string str)		//Ф-я, меняющая указанные группы бит местами
{
	string new_str = str;
	int limit = first + size;
	for (int i = first; i < limit; i++)
	{
		int swap = new_str[i];
		new_str[i] = new_str[second];
		new_str[second++] = swap;
	}
	return new_str;
}

void draw_available_symbols(int syst)
{
	for (int i = 0; i < syst; i++)
	{
		if (i < 10)
			cout << char(i + 48) << ' ';
		else if (i < 36)
			cout << char(i + 55) << ' ';
		else
			cout << char(i + 61) << ' ';
	}
}

void draw_graphp(string str, string new_str)
{
	int y = 0, x = 0, new_y = 10;
	bool move;
	int prev_y;
	if (str[0] == '0')
		prev_y = 320;
	else
		prev_y = 300;
	point* p_arr = static_cast<point*>(operator new[](str.length() * sizeof(point)));
	for (int i = 0; i < str.length(); i++)
	{
		if (i != 0)
			prev_y = y;
		if (str[i] == '0')
			y = 320;
		else
			y = 300;
		if (str[i] != new_str[i])
			move = true;
		else
			move = false;
		if (new_str[i] == '0')
			new_y = 320;
		else
			new_y = 300;
		new (p_arr + i) point(x, y, prev_y, new_y, move);
		x += 20;
	}
	for (int i = 0; i < str.length(); i++)
	{
		p_arr[i].draw_point();
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (p_arr[i].move)
		{
			if (i == 0)
				p_arr[i].draw_new_point(p_arr[i].y, p_arr[i + 1].y);
			else
				if (i == str.length() - 1)
					p_arr[i].draw_new_point(p_arr[i - 1].y, p_arr[i].y);
				else
					p_arr[i].draw_new_point(p_arr[i - 1].y, p_arr[i + 1].y);
			if (p_arr[i].y == 300)
				p_arr[i].y = 320;
			else
				p_arr[i].y = 300;
		}
	}
	cin.get();
}