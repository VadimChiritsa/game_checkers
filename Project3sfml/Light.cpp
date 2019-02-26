#include "Light.h"
#include "Logic.h"

void Light::lightUR(Checker& _checker, int i, int j)
{
	while(true){
		if (Logic::checkingBounds(i, j) && _checker.cell[i][j].getClean() == false)
			_checker.cell[i--][j++].setBacklight(true);
		else return;
	}
}

void Light::lightUL(Checker& _checker, int i, int j)
{
	while (true) {
		if (Logic::checkingBounds(i, j) && _checker.cell[i][j].getClean() == false)
			_checker.cell[i--][j--].setBacklight(true);
		else return;
	}
}

void Light::lightDR(Checker& _checker, int i, int j)
{
	while (true) {
		if (Logic::checkingBounds(i, j) && _checker.cell[i][j].getClean() == false)
			_checker.cell[i++][j++].setBacklight(true);
		else return;
	}
}

void Light::lightDL(Checker& _checker, int i, int j)
{
	while (true) {
		if (Logic::checkingBounds(i, j) && _checker.cell[i][j].getClean() == false)
			_checker.cell[i++][j--].setBacklight(true);
		else return;
	}
}

bool Light::checkDR(Checker& _checker, int i, int j, bool color)
{
	int i1 = i, j1 = j;
	bool flag = false;
	while (true) {
		if (Logic::checkingBounds(i1 + 1, j1 + 1) && Logic::checkingBounds(i1 + 2, j1 + 2)) {
			if (_checker.cell[i1 + 1][j1 + 1].getClean() && _checker.cell[i1 + 1][j1 + 1].getColor() == color) break;
			if (_checker.cell[i1 + 1][j1 + 1].getClean() && _checker.cell[i1 + 1][j1 + 1].getColor() != color && _checker.cell[i1 + 2][j1 + 2].getClean() && _checker.cell[i1 + 2][j1 + 2].getColor() != color) break;
			if (_checker.cell[i1 + 1][j1 + 1].getClean() && _checker.cell[i1 + 1][j1 + 1].getColor() != color && _checker.cell[i1 + 2][j1 + 2].getClean() == false) {
				_checker.cell[i][j].setBacklight(true);
				flag = true;
				break;
			}
			else i1++; j1++;
		}
		else break;
	}
	return flag;
}

bool Light::checkDL(Checker& _checker, int i, int j, bool color)
{
	int i1 = i, j1 = j;
	bool flag = false;
	while (true) {
		if (Logic::checkingBounds(i1 + 1, j1 - 1) && Logic::checkingBounds(i1 + 2, j1 - 2)) {
			if (_checker.cell[i1 + 1][j1 - 1].getClean() && _checker.cell[i1 + 1][j1 - 1].getColor() == color) break;
			if (_checker.cell[i1 + 1][j1 - 1].getClean() && _checker.cell[i1 + 1][j1 - 1].getColor() != color && _checker.cell[i1 + 2][j1 - 2].getClean() && _checker.cell[i1 + 2][j1 - 2].getColor() != color) break;
			if (_checker.cell[i1 + 1][j1 - 1].getClean() && _checker.cell[i1 + 1][j1 - 1].getColor() != color && _checker.cell[i1 + 2][j1 - 2].getClean() == false) {
				_checker.cell[i][j].setBacklight(true);
				flag = true;
				break;
			}
			else i1++; j1--;
		}
		else break;
	}
	return flag;
}

bool Light::checkUR(Checker& _checker, int i, int j, bool color)
{
	int i1 = i, j1 = j;
	bool flag = false;
	while (true) {
		if (Logic::checkingBounds(i1 - 1, j1 + 1) && Logic::checkingBounds(i1 - 2, j1 + 2)) {
			if (_checker.cell[i1 - 1][j1 + 1].getClean() && _checker.cell[i1 - 1][j1 + 1].getColor() == color) break;
			if (_checker.cell[i1 - 1][j1 + 1].getClean() && _checker.cell[i1 - 1][j1 + 1].getColor() != color && _checker.cell[i1 - 2][j1 + 2].getClean() && _checker.cell[i1 - 2][j1 + 2].getColor() != color) break;
			if (_checker.cell[i1 - 1][j1 + 1].getClean() && _checker.cell[i1 - 1][j1 + 1].getColor() != color && _checker.cell[i1 - 2][j1 + 2].getClean() == false) {
				_checker.cell[i][j].setBacklight(true);
				flag = true;
				break;
			}
			else i1--; j1++;
		}
		else break;
	}
	return flag;
}

bool Light::checkUL(Checker& _checker, int i, int j, bool color)
{
	int i1 = i, j1 = j;
	bool flag = false;
	while (true) {
		if (Logic::checkingBounds(i1 - 1, j1 - 1) && Logic::checkingBounds(i1 - 2, j1 - 2)) {
			if (_checker.cell[i1 - 1][j1 - 1].getClean() && _checker.cell[i1 - 1][j1 - 1].getColor() == color) break;
			if (_checker.cell[i1 - 1][j1 - 1].getClean() && _checker.cell[i1 - 1][j1 - 1].getColor() != color && _checker.cell[i1 - 2][j1 - 2].getClean() && _checker.cell[i1 - 2][j1 - 2].getColor() != color) break;
			if (_checker.cell[i1 - 1][j1 - 1].getClean() && _checker.cell[i1 - 1][j1 - 1].getColor() != color && _checker.cell[i1 - 2][j1 - 2].getClean() == false) {
				_checker.cell[i][j].setBacklight(true);
				flag = true;
				break;
			}
			else i1--; j1--;
		}
		else break;
	}
	return flag;
}



