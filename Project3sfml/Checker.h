#pragma once
#include "Cell.h"



class Checker : public Cell{
public:
	Cell cell[8][8];

	Checker(){};
	Checker(bool);
	
	void draw(RenderWindow& window);
};
