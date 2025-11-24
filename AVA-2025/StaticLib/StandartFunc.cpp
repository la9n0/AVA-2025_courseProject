#include <iostream>
#include <Windows.h>
#include <cstring>
#pragma warning(disable: 4996)


extern "C"
{
	int strcmp(char* str1, char* str2)
	{
		return ::strcmp(str1, str2);
	}

	int write_uint(unsigned int p)
	{
		std::cout << p << std::endl;
		return 0;
	}

	int write_short(short p)
	{
		std::cout << p << std::endl;
		return 0;
	}

	int write_char(char p)
	{
		std::cout << p << std::endl;
		return 0;
	}

	int write_bool(bool p)
	{
		std::cout << (p ? "true" : "false") << std::endl;
		return 0;
	}

	int write_str(char* str)
	{
		setlocale(LC_ALL, "rus");
		std::cout << str << std::endl;
		return 0;
	}
}
