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
	������� ������ �������
	*/
	void clear_screen();

	/*
	����� ������ ����
	*/
	void print_menu_header(std::string);

	/*
	��������� ����
	*/
	void draw_menu_selector(bool, short *, std::string);

	// -------------------------------------------------------
	// ��� �������

	// ��������

	/*
	����������� ������ � ������� ������� ����������
	*/
	void print_race_roster(std::vector<jinx::Vehicle*>);

	/*
	����������� ������ � ������� ���������� � �������� ������
	*/
	void print_race_results(std::vector<jinx::Vehicle*>);

	// ���������� ������� ����������

	/*
	���������� ����������� �����
	*/
	void sort_result_roster(std::vector<jinx::Vehicle*> & raceRoster);

	// ��������� �����

	bool get_bot_names(std::vector<std::string>*);

	bool get_bot_callsigns(std::vector<std::string>*);

	void get_bots(std::vector<std::string>*, int);

	// -------------------------------------------------------
	// �������� �����

	void run_ground_race(std::string);

	// -------------------------------------------------------
	// ��������� �����

	void run_air_race(std::string);


	// -------------------------------------------------------
	// ��������� �����

	void run_mixed_race(std::string);

	/*
	������ ����
	*/
	void start_game(std::string);
}