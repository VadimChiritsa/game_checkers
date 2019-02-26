#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Checker.h"
#include "Logic.h"
#include <windows.h>
#include "AI.h"
#include <math.h>
#include "FileBIN.h"
#include <SFML/Audio.hpp>


class Interface{
public:
	void vibor(int **, int );
	void menu(RenderWindow& window);
	void Game(RenderWindow&, Person&, int, bool);
	char* itoa(int val);
	void ChoiceColor(RenderWindow& window, Person& person, int number);
	void inputName(RenderWindow& window);
	void StatisticPlayer(RenderWindow& window);
	void menuGame(RenderWindow & window);
	void choicePlayer(RenderWindow& window);
};
