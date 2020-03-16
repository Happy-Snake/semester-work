#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <cmath>

#include "../Headers/Menu.h"
#include "../Headers/Func.h"
#include "../Headers/Scan.h"

using namespace std;

int color1 = 2;
int color2 = 6;
int color_of_text = 7;
int color_of_bits = 7;
int color_of_background;

int main()
{
	if (Scan())
	{
		short answer;
		do
		{
			answer = main_menu();
			switch (answer)
			{
			case 0:			//unsigned char
			{
				unsigned char var;
				input_char(var);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu_for_char(var, bits_str);
				break;
			}
			case 1:			//char
			{
				signed char var;
				input_char(var);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu_for_char(var, bits_str);
				break;
			}
			case 2:			//short int
			{
				int syst = num_syst();
				short int var = 0;
				int* systptr = &syst;
				short int* varptr = &var;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 3:			//unsigned short int
			{
				int syst = num_syst();
				unsigned short int var = 0;
				string str_var = input_num(var, syst, true);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 4:			//int
			{
				int syst = num_syst();
				int var = 0;
				string str_var = input_num(var, syst, true);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 5:			//unsigned int
			{
				int syst = num_syst();
				unsigned int var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 6:			//long
			{
				int syst = num_syst();
				long var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 7:			//unsigned long
			{
				int syst = num_syst();
				unsigned long var = 0;
				string str_var = input_num(var, syst, true);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 8:			//long long
			{
				int syst = num_syst();
				long long var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 9:			//unsigned long long
			{
				int syst = num_syst();
				unsigned long long var = 0;
				string str_var = input_num(var, syst, true);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 10:		//float
			{
				int syst = num_syst();
				float var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 11:		//double
			{
				int syst = num_syst();
				double var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 12:		//long double
			{
				int syst = num_syst();
				long double var = 0;
				string str_var = input_num(var, syst);
				string bits_str = make_str(var);
				draw_bits(bits_str, 0, 0, 0);
				draw_new_menu(syst, var, bits_str, str_var);
				break;
			}
			case 13:
			{
				short color_to_choose;
				do
				{
					color_to_choose = which_color_to_choose();
					switch (color_to_choose)
					{
					case 0:
					{
						int answer = color_menu();
						if (answer != 15)
							//if (Scan())
								color1 = answer;
						break;
					}
					case 1:
					{
						int answer = color_menu();
						if (answer != 15)
							//if (Scan())
								color2 = answer;
						break;
					}
					case 2:
					{
						int answer = color_menu();
						if (answer != 15)
							//if (Scan())
								color_of_text = answer;
						HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(handle, (WORD)(color_of_background << 4) | (short)(color_of_text));
						break;
					}
					case 3:
					{
						int answer = color_menu();
						if (answer != 15)
							//if (Scan())
								color_of_bits = answer;
						break;
					}
					case 4:
					{
						int answer = color_menu();
						if (answer != 15)
							//if (Scan())
								color_of_background = answer;
						HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(handle, (WORD)(color_of_background << 4) | (short)(color_of_text));
						break;
					}
					}
				} while (color_to_choose != 5);
			}
			}
		} while (answer != 14);
		system("pause");
	}
};