#include "Cell.h"

Cell::Cell()
{
	
	clean = false;
	color = false;
	king = false;
	backlight = false;
	kill = false;
	
}

void Cell::setClean(bool type)
{
	clean = type;
}

void Cell::setColor(bool type)
{
	color = type;
}

void Cell::setKing(bool type)
{
	king = type;
}

void Cell::setBacklight(bool type)
{
	backlight = type;
}

void Cell::setKill(bool type)
{
	kill = type;
}



bool Cell::getClean()const
{
	return clean;
}

bool Cell::getColor()const
{
	return color;
}

bool Cell::getKing()const
{
	return king;
}

bool Cell::getBacklight()const
{
	return backlight;
}

bool Cell::getKill()const
{
	return kill;
}

