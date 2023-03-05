// racesim.cpp

/*
Основной файл программы, содержит главную функцию main()
*/

// DEFINITIONS

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define _UNICODE

#ifdef _WIN32
#include <windows.h>
#include <string>
#endif // windows

#ifdef linux
#include <stdlib.h>
#include <string.h>
#endif // linux

// -----------

#include <iostream>
#include "utility.h"

// imports

import jinx_racegame;
import jinx_exceptions;

int main(int argc, char ** argv)
{
#ifdef _WIN32

	 SetConsoleCP(1251);
	 SetConsoleOutputCP(1251);

#define _WIN32_

#endif // _WIN32

#ifdef _WIN64
#undef _WIN32_
#define _AMD64_
#endif

#ifdef linux

#define _AMD64_
	setlocale(LC_ALL, "Russian");

#endif // linux
	
	std::string userName;

	std::cout << "Введите имя игрока (Максимум 10 символов)\n> ";

	do
	{
		getline(std::cin, userName);
	} while (userName.length() > 10);

	std::cout << "\nSTRLEN = " << userName.length();
	std::cout << "\nContent: \n";

	for (int i = 0; i < userName.length(); ++i)
	{
		std::cout << "[" << i << "]"; 
		std::cout << userName[i];
	}

	std::cout << "\nИмя игрока: ";
	std::cout << userName;

	jinx::GV_Humpback humpback(userName);

	jinx::GV_Humpback* gv_humpback_ptr;
	jinx::Vehicle* vehicle_ptr;

	std::cout << '\n';

	vehicle_ptr = &humpback;
	vehicle_ptr = vehicle_ptr;

	jinx::print_vehicle(humpback);

	std::cout << '\n';

	// clear and exit

	// ------------------
	std::cout << std::endl;
	std::cout << "Нажмите любую кнопку для завершения...\n";
	std::getchar();
	return EXIT_SUCCESS;
}
