// utility.cpp

// INCLUDES

#include "utility.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

#ifdef _WIN32       // Windows
#include <cstdlib>
#include <string>
#else               // POSIX
#include <stdlib.h>
#include <string.h>
#endif

// IMPORTS

import jinx_racegame;

/*
Очистка экрана консоли
*/
void jinx::clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
} // END OF clear_screen()

/*
Вывод плашки меню
*/
void jinx::print_menu_header(std::string userName)
{
    std::cout << "---------------------------------------------------------------\n";
    std::cout << "\t\t>>> ИГРА СИМУЛЯТОР ГОНОК! <<<\n";
    std::cout << "\t\tИгрок: " << userName << "\n";
    std::cout << "---------------------------------------------------------------\n\n";
}

/*
Отрисовка меню
*/
void jinx::draw_menu_selector(bool repeatKey, short * playerMenuInput, std::string userName)
{
	if (!repeatKey)
	{
		std::cout << "Меню (выберите действие):	\n" <<
					"1. Начать игру\n" <<
					"0. Выход\n";
	}
	else
	{
		std::cout << "Меню (выберите действие):	\n" <<
			"1. Повторить игру?\n" <<
			"0. Выход\n";
	}
	// Ввод игрока в меню

	do // while (playerMenuInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> *playerMenuInput;

	} while (*playerMenuInput == -1);
}

// -----------------------------------------------------------------------------------
/* ДОП ФУНКЦИИ ---------------------------------------------------------------------- */

// ПРИНТЕРЫ

/*
Распечатать массив с простым списком участников
*/
void jinx::print_race_roster(std::vector<jinx::Vehicle*> raceRoster)
{	
	int size = static_cast<int>(raceRoster.size());
	
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Пилот: " << raceRoster[i]->get_pilot_name() << "\tТС: " << raceRoster[i]->get_vehicle_name() << "\tСкорость: " << raceRoster[i]->get_vehicle_speed();
		std::cout << '\n';
	} // END OF for (int i = 0; i < size; ++i)
} // END OF print_race_roster(std::vector<jinx::Vehicle*>* raceRoster)

/*
Распечатать массив с списком участников и временем заезда
*/
void jinx::print_race_results(std::vector<jinx::Vehicle*> raceRoster)
{
	int size = static_cast<int>(raceRoster.size());
	
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Поизция: " << i + 1 << "\tПилот: " << raceRoster[i]->get_pilot_name() << "\tТС: " << raceRoster[i]->get_vehicle_name() << "\t Результат заезда: " << raceRoster[i]->get_race_result();
		std::cout << '\n';
	} // END OF for (int i = 0; i < size; ++i)
} // END OF print_race_results(std::vector<jinx::Vehicle*> * raceRoster)

// СОРТИРОВКА МАССИВА РЕЗУЛЬТАОВ

/*
Сортировка результатов гонки
*/
void jinx::sort_result_roster(std::vector<jinx::Vehicle*> raceRoster)
{
	// VARIABLES -----------------
	bool madeChange = false;
	int vectorSize = raceRoster.size();
	// ---------------------------

	do {
		madeChange = false;

		for (int i = 0; i < vectorSize - 1; ++i) 
		{
			if (raceRoster[i + 1]->get_race_result() < raceRoster[i]->get_race_result())
			{
				jinx::Vehicle * temp;

				temp = raceRoster[i + 1];

				raceRoster[i + 1] = raceRoster[i];
				raceRoster[i] = temp;
				madeChange = true;
			}
			
		}
	} while (madeChange);

} // END OF jinx::sort_result_roster(std::vector<jinx::Vehicle*> raceRoster)

// НАСТРОЙКА БОТОВ --------

bool jinx::get_bot_names(std::vector<std::string>* nameVector)
{
	std::ifstream file_botnames;

	file_botnames.open("botnames.txt", std::ios::in);

	if (file_botnames.is_open())
	{
		std::string reader;

		while (!file_botnames.eof())
		{
			getline(file_botnames, reader, '\n');
			nameVector->push_back(reader);
			reader.clear();
		}

		return EXIT_SUCCESS;
	}
	else
	{		
		return EXIT_FAILURE;
	}
}

bool jinx::get_bot_callsigns(std::vector<std::string>* nameVector)
{
	std::ifstream file_botcallsigns;

	file_botcallsigns.open("botcallsigns.txt", std::ios::in);

	if (file_botcallsigns.is_open())
	{
		std::string reader;

		while (!file_botcallsigns.eof())
		{
			getline(file_botcallsigns, reader);
			nameVector->push_back(reader);
			reader.clear();
		}

		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}

void jinx::get_bots(std::vector<std::string>* list, int botCount)
{
	std::vector<std::string> botNames;
	std::vector<std::string> botCallsigns;

	jinx::get_bot_names(&botNames);
	jinx::get_bot_callsigns(&botCallsigns);

	int namePoolSize = 0;
	int callsignPoolSize = 0;
	int nameIndexRng = 0;
	int callsignIndexRng = 0;

	namePoolSize = static_cast<int>(botNames.size());
	callsignPoolSize = static_cast<int>(botCallsigns.size());

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------


	for (int i = 1; i <= botCount; ++i)
	{
		std::uniform_int_distribution<> dis1(1, namePoolSize - 1);
		nameIndexRng = dis1(gen);
		std::uniform_int_distribution<> dis2(1, callsignPoolSize - 1);
		callsignIndexRng = dis2(gen);

		std::string rngNameGen = botNames[nameIndexRng] + " " + botCallsigns[callsignIndexRng];

		list->push_back(rngNameGen);
	}

}

// -------------------------------------------------------
// НАЗЕМНАЯ ГОНКА

void jinx::run_ground_race(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;
	jinx::Vehicle * vehicle_ptr;
	std::vector<std::string> botList;
	int botNumber = 0;
	int seed = 0;
	std::vector<jinx::Vehicle*> raceList;	// список участников гонки
	int raceDistance = 0;

	std::vector < jinx::GV_Humpback> bot_humpback_list;
	std::vector < jinx::GV_Humpback_Fast> bot_humpback_fast_list;
	std::vector < jinx::GV_Centaur> bot_centaur_list;
	std::vector < jinx::GV_AllTBoots> bot_boots_list;

	jinx::GV_Humpback temp_vehicle_1(userName);
	jinx::GV_Humpback_Fast temp_vehicle_2(userName);
	jinx::GV_Centaur temp_vehicle_3(userName);
	jinx::GV_AllTBoots temp_vehicle_4(userName);

	// -----------------------------

	// RNG GENERATION

	// Random seed
	std::random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	// std::uniform_int_distribution<> dis(1, 100);
	// int ... = dis(gen);

	// --------------

	// -----------------------------

	jinx::clear_screen();

	jinx::print_menu_header(userName);
	
	std::cout << "Выберите ТС для игрока: \n"
		<< "1. Верблюд\n"
		<< "2. Верблюд-быстроход\n"
		<< "3. Кентавр\n"
		<< "4. Ботинки-вездеходы\n";

	do // while (localPlayerInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while (localPlayerInput == -1);	

	switch (localPlayerInput)
	{
	case 1:
	{
		vehicle_ptr = &temp_vehicle_1;
	} // end case 1
	case 2:
	{
		vehicle_ptr = &temp_vehicle_2;
		break;
	} // end case 2
	case 3:
	{
		vehicle_ptr = &temp_vehicle_3;
		break;
	} // end case 3
	case 4:
	{
		vehicle_ptr = &temp_vehicle_4;
		break;
	} // end case 4	
	default:
	{
		break;
	} // end default
	} // end switch (localPlayerInput)

	raceList.push_back(vehicle_ptr);
	vehicle_ptr = nullptr;

	std::cout << "Введите количество других участников: ";
	std::cin >> botNumber;

	jinx::get_bots(&botList, botNumber);

	// DEBUG --------------------------

	std::cout << std::endl << std::endl;
	std::cout << "BOTLIST SIZE = " << botList.size() << "\n";
	std::cout << "BotNumber = " << botNumber << "\n";
	std::cout << "LIST:\n";

	for (int i = 0; i < botNumber; ++i)
	{
		std::cout << botList[i] << '\n';
	}
	std::cout << std::endl << std::endl;

	// END DEBUG -----------------------

	for (int i = 0; i < botNumber; ++i)
	{
		std::uniform_int_distribution<> dis(1, 4);
		seed = dis(gen);
		
		// DEBUG ----------------------------

		// std::cout << "i = " << i << ", seed = " << seed << '\n';

		// END DEBUG ------------------------

		switch (seed)
		{
		case 1:
		{	
			// DEBUG -------------------------
			// std::cout << "\nEntered case 1\n";
			// END DEBUG ---------------------

			jinx::GV_Humpback bot_temp_vehicle_1(botList[i]);

			// DEBUG -------------------------
			// std::cout << "\nHumpback:\n"; 
			// bot_temp_vehicle_1.print_vehicle_info();
			// std::cout << std::endl;
			// END DEBUG ---------------------

			bot_humpback_list.push_back(bot_temp_vehicle_1);
			break;
		} // end case 1
		case 2:
		{
			// DEBUG -------------------------
			// std::cout << "\nEntered case 2\n";
			// END DEBUG ---------------------

			jinx::GV_Humpback_Fast bot_temp_vehicle_2(botList[i]);

			// DEBUG -------------------------
			// std::cout << "\nHumpback fast:\n";
			// bot_temp_vehicle_2.print_vehicle_info();
			// std::cout << std::endl;
			// END DEBUG ---------------------

			bot_humpback_fast_list.push_back(bot_temp_vehicle_2);
			break;
		} // end case 2
		case 3:
		{
			// DEBUG -------------------------
			// std::cout << "\nEntered case 3\n";
			// END DEBUG ---------------------

			jinx::GV_Centaur bot_temp_vehicle_3(botList[i]);

			// DEBUG -------------------------
			// std::cout << "\nCentaur:\n";
			// bot_temp_vehicle_3.print_vehicle_info();
			// std::cout << std::endl;
			// END DEBUG ---------------------

			bot_centaur_list.push_back(bot_temp_vehicle_3);
			break;
		} // end case 3
		case 4:
		{
			// DEBUG -------------------------
			// std::cout << "\nEntered case 4\n";
			// END DEBUG ---------------------

			jinx::GV_AllTBoots bot_temp_vehicle_4(botList[i]);

			// DEBUG -------------------------
			// std::cout << "\nBoots:\n";
			// .print_vehicle_info();
			// std::cout << std::endl;
			// END DEBUG ---------------------

			bot_boots_list.push_back(bot_temp_vehicle_4);
			break;
		} // end case 4	
		default:
		{

			// DEBUG -------------------------
			// std::cout << "\nEntered default switch\n";
			// END DEBUG ---------------------

			break;
		} // end default
		} // end switch (seed)		

	} // END for (int i = 0; i < playerNumber; ++i)

	if (bot_humpback_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_humpback_fast_list.size() > 0)
	{
		for (int i = 0; i < bot_humpback_fast_list.size(); ++i)
		{
			vehicle_ptr = &bot_humpback_fast_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_centaur_list.size() > 0)
	{
		for (int i = 0; i < bot_centaur_list.size(); ++i)
		{
			vehicle_ptr = &bot_centaur_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	if (bot_boots_list.size() > 0)
	{
		for (int i = 0; i < bot_boots_list.size(); ++i)
		{
			vehicle_ptr = &bot_boots_list[i];
			raceList.push_back(vehicle_ptr);
		}
	}

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "\nСПИСОК УЧАСТНИКОВ:\n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_roster(raceList);
	}
	else
	{
		std::cout << "-- ПУСТО --";
	}

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << "Введите любую кнопку для продолжения...\n";
	std::cin.get();
#endif 

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	// ПРОЦЕСС ФОРМИРОВАНИЯ ГОНКИ -------------------------------

	std::cout << "Введите дистанцию гонки: \n";
	std::cout << userName << "> ";
	std::cin >> raceDistance;

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "Параметры гонки \n\n";
	std::cout << "Тип гонки: наземная гонка\n";
	std::cout << "Дистанция гонки: " << raceDistance << '\n';
	std::cout << "Количество участников: " << raceList.size() << '\n';
	std::cout << "Ростер участников старта: \n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_roster(raceList);
	}
	else
	{
		std::cout << "-- ПУСТО --";
	}

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << "Введите любую кнопку для продолжения...\n";
	std::cin.get();
#endif 

	// Генерация результатов гонки

	for (int i = 0; i < raceList.size(); ++i)
	{
		raceList[i]->calculate_time_result(raceDistance);
	}	

	// Сортировка результатов гонки

	// std::sort(raceList.begin(), raceList.end());

	jinx::sort_result_roster(raceList);

	// Вывод результатов гонки

	// RESET SCREEN -----------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	// -------------------------------

	std::cout << "Параметры гонки \n\n";
	std::cout << "Тип гонки: наземная гонка\n";
	std::cout << "Дистанция гонки: " << raceDistance << '\n';
	std::cout << "Количество участников: " << raceList.size() << '\n';
	std::cout << "Результаты участников старта: \n\n";

	if (raceList.size() != 0)
	{
		jinx::print_race_results(raceList);
	}
	else
	{
		std::cout << "-- ПУСТО --";
	}

	// Завершение и выход

#ifdef _WIN32			// windows
	system("pause");
#else					// POSIX
	std::cout << "Введите любую кнопку для продолжения...\n";
	std::cin.get();
#endif 
}


// -------------------------------------------------------
// ВРЗДУШНАЯ ГОНКА

void jinx::run_air_race(std::string userName)
{
	// TODO
}


// -------------------------------------------------------
// СМЕШАННАЯ ГОНКА

void jinx::run_mixed_race(std::string userName)
{
	// TODO
}

/*
крутим игру
*/
void jinx::start_game(std::string userName)
{
	// VARIABLES

	short localPlayerInput = -1;

	// ------------------------------

	jinx::clear_screen();
	jinx::print_menu_header(userName);

	std::cout << "Меню (выберите действие), выберите тип гонки:	\n"
		<< "1. Наземная гонка\n"
		<< "2. Воздушная гонка\n"
		<< "3. Смешанная гонка\n";

	do // while (playerMenuInput == -1);
	{
		std::cout << "\n" << userName << "> ";
		std::cin >> localPlayerInput;

	} while (localPlayerInput == -1);

	switch (localPlayerInput)
	{
	case 1:
	{
		// Наземная гонка
		jinx::run_ground_race(userName);
		break;
	}
	case 2:
	{
		// Воздушная гонка
		jinx::run_air_race(userName);
		break;
	}
	case 3:
	{
		// Смешанная гонка
		jinx::run_mixed_race(userName);
		break;
	}
	default:
	{
		std::cout << "Выбор не распознан... попробуйте снова\n";
		std::cin.get();
		break;
	}
	} // switch (localPlayerInput)
}