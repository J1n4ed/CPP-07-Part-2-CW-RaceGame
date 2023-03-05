// utility.h

#pragma once

// INCLUDES

#ifdef _WIN32
#include <string>
#else // POSIX
#include <string.h>
#endif

#include <vector>

// IMPORTS

import jinx_racegame;

namespace jinx
{
	/*
	Очистка экрана консоли
	*/
	void clear_screen();

	/*
	Вывод плашки меню
	*/
	void print_menu_header(std::string);

	/*
	Отрисовка меню
	*/
	void draw_menu_selector(bool, short *, std::string);

	// -------------------------------------------------------
	// ДОП ФУНКЦИИ

	// Принтеры

	/*
	Распечатать массив с простым списком участников
	*/
	void print_race_roster(std::vector<jinx::Vehicle*>);

	/*
	Распечатать массив с списком участников и временем заезда
	*/
	void print_race_results(std::vector<jinx::Vehicle*>);

	// СОРТИРОВКА МАССИВА РЕЗУЛЬТАОВ

	/*
	Сортировка результатов гонки
	*/
	void sort_result_roster(std::vector<jinx::Vehicle*> & raceRoster);

	// Настройка ботов

	bool get_bot_names(std::vector<std::string>*);

	bool get_bot_callsigns(std::vector<std::string>*);

	void get_bots(std::vector<std::string>*, int);

	// -------------------------------------------------------
	// НАЗЕМНАЯ ГОНКА

	void run_ground_race(std::string);

	// -------------------------------------------------------
	// ВРЗДУШНАЯ ГОНКА

	void run_air_race(std::string);


	// -------------------------------------------------------
	// СМЕШАННАЯ ГОНКА

	void run_mixed_race(std::string);

	/*
	крутим игру
	*/
	void start_game(std::string);
}