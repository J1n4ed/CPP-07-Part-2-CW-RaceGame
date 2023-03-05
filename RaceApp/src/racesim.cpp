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

#ifdef _WIN32			// windows
#include <windows.h>
#include <string>
#include <cstdlib>
#else					// POSIX
#include <stdlib.h>
#include <string.h>
#endif 

// -----------

#include <iostream>
#include "utility.h"
#include <vector>
#include <time.h>

// imports

import jinx_racegame;

int main(int argc, char ** argv)
{

#ifdef _WIN32					// Windows
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#else							// POSIX
	setlocale(LC_ALL, "Russian");
#endif
	
	// ПЕРЕМЕННЫЕ --------------------------------------------

	std::string userName;					// ммя игрока
	bool flagExit = false;					// флаг выхода
	short playerMenuInput = -1;				// ввод игрока в меню игры	
	short raceType = -1;					// Тип выбранной гонки
	bool repeatKey = false;					// ключ отрисовки меню

	// -------------------------------------------------------

	// SETUP

	jinx::clear_screen();

	std::cout << "---------------------------------------------------------------\n";
	std::cout << "                  >>> ИГРА СИМУЛЯТОР ГОНОК! <<<\n";	
	std::cout << "---------------------------------------------------------------\n\n";

	std::cout << "Введите имя игрока\n> ";

	getline(std::cin, userName);	


	// ------------------------------------------------------
	// ------- MAIN GAMEPLAY LOOP ---------------------------

	do // while (!flagExit);
	{
		jinx::clear_screen();
		playerMenuInput = -1;		// drop to default
		raceType = -1;				// drop to default

		// плашка меню
		jinx::print_menu_header(userName);

		// крутилка главного меню

		jinx::draw_menu_selector(repeatKey, &playerMenuInput, userName);		

		switch (playerMenuInput)
		{
		case 0:
		{
			flagExit = true;
			break;
		}
		case 1:
		{
			// - GAME ENTREE -
			jinx::start_game(userName);

			if (!repeatKey) repeatKey = true;
			break;
		}
		default:
		{
			std::cout << "Выбор не распознан... попробуйте снова\n";
			std::cin.get();
			break;
		}
		}
		// END OF ввод игрока в меню

		std::cout << std::endl << std::endl;

	} while (!flagExit);

	// ------ END GAME PLAY LOOP ----------------------------

	std::cin.clear();
	std::cout << "\n\t\t-- ИГРА ОКОНЧЕНА --\n";

	// clear and exit

	// ------------------

	std::cout << std::endl;

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << "Введите любую кнопку для завершения...\n";
	std::cin.get();
#endif 
	
	return EXIT_SUCCESS;
}