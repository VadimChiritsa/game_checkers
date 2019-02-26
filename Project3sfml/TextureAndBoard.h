#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include "Windows.h"

class TextureAndBoard{
public:
	Texture boardT;
	int size=64;	
	int board[8][8]=
	{
		/*0, 0, 0, 0, 0, 0, 1, 0,
		0, 2, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0*/

		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 0, 2, 0, 2
	};
	
public:
	Sprite boardS;

	TextureAndBoard();

	void draw(RenderWindow& window);
};
