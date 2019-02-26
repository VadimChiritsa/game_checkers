#include "Move.h"

Move::Move()
{
	oldPoz = 0;
	newPoz = 0;
	flag = false;
	killPoz = -1;
	king = false;
}

Move::Move(int oldP, int newP, bool f,int k, bool d)
{
	oldPoz = oldP;
	newPoz = newP;
	flag = f;
	killPoz = k;
	king = d;
}

void Move::setOldPoz(int oldP)
{
	oldPoz = oldP;
}

void Move::setNewPoz(int newP)
{
	newPoz = newP;
}

void Move::setKillPoz(int k)
{
	killPoz = k;
}

void Move::setKing(bool k)
{
	king = k;
}



int Move::getOldPoz()
{
	return oldPoz;
}

int Move::getNewPoz()
{
	return newPoz;
}

bool Move::getFlag()
{
	return flag;
}

int Move::getKillPoz()
{
	return killPoz;
}

bool Move::getKing()
{
	return king;
}

void Move::null()
{

	oldPoz = 0;
	newPoz = 0;
	flag = false;
	killPoz = -1;
	king = false;
}
