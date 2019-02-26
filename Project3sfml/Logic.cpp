#include "Logic.h"
#include <wingdi.h>

bool Logic::needKill(Checker& _checker, bool color, int* ms)
{
	bool flag = false;
	bool flag2 = false;

	if(ms[1]!=-1){
		int i = ms[1] / 8, j = ms[1] % 8;
		if (_checker.cell[i][j].getKing() && _checker.cell[i][j].getColor()==color)
			(needKillKing(_checker, i, j, color, ms[0]) == true) ? flag2 = true : flag2 = false;
		else {
			
			if (checkingBounds(i - 1, j + 1, i - 2, j + 2) && _checker.cell[i - 1][j + 1].getClean() && _checker.cell[i - 1][j + 1].getColor() == (!color) && !_checker.cell[i - 2][j + 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (checkingBounds(i - 1, j - 1, i - 2, j - 2) && _checker.cell[i - 1][j - 1].getClean() && _checker.cell[i - 1][j - 1].getColor() == (!color) && !_checker.cell[i - 2][j - 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (checkingBounds(i + 1, j + 1, i + 2, j + 2) && _checker.cell[i + 1][j + 1].getClean() && _checker.cell[i + 1][j + 1].getColor() == (!color) && !_checker.cell[i + 2][j + 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (checkingBounds(i + 1, j - 1, i + 2, j - 2) && _checker.cell[i + 1][j - 1].getClean() && _checker.cell[i + 1][j - 1].getColor() == (!color) && !_checker.cell[i + 2][j - 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			
		}
		if (flag || flag2) return true;
		else return false;
	}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++){
			if (_checker.cell[i][j].getKing() && _checker.cell[i][j].getColor() == color) (needKillKing(_checker, i, j, color, ms[0]) == true) ? flag2 = true : flag2 = false;
			if (_checker.cell[i][j].getClean() == false || _checker.cell[i][j].getColor() != color) continue;
			else{
				//if (!color){
					if (checkingBounds(i - 1, j + 1, i - 2, j + 2)  && _checker.cell[i - 1][j + 1].getClean() && _checker.cell[i - 1][j + 1].getColor() == (!color) && !_checker.cell[i - 2][j + 2].getClean()){
						_checker.cell[i][j].setKill(true);
						flag = true;
					}
					if (checkingBounds(i - 1, j - 1, i - 2, j - 2)  && _checker.cell[i - 1][j - 1].getClean() && _checker.cell[i - 1][j - 1].getColor() == (!color) && !_checker.cell[i - 2][j - 2].getClean()){
						_checker.cell[i][j].setKill(true);
						flag = true;
					}
					if (checkingBounds(i + 1, j + 1, i + 2, j + 2) && _checker.cell[i + 1][j + 1].getClean() && _checker.cell[i + 1][j + 1].getColor() == (!color) && !_checker.cell[i + 2][j + 2].getClean()){
						_checker.cell[i][j].setKill(true);
						flag = true;
					}
					if (checkingBounds(i + 1, j - 1, i + 2, j - 2) && _checker.cell[i + 1][j - 1].getClean() && _checker.cell[i + 1][j - 1].getColor() == (!color) && !_checker.cell[i + 2][j - 2].getClean()){
						_checker.cell[i][j].setKill(true);
						flag = true;
					}
				//}
			}
		}
	if (flag || flag2) return true;
	else return false;
}

bool Logic::needKillKing(Checker& _checker, int i, int j, bool color, int napr)
{
	int tempI = i, tempJ = j;
	if (napr != 1) {
		while (true) {
			if (checkingBounds(++tempI, ++tempJ, tempI + 1, tempJ + 1))
			{
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() && _checker.cell[tempI + 1][tempJ + 1].getColor() != color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() == false) {
					_checker.cell[i][j].setKill(true); return true;
				}
			}
			else break;
		}
	}

	 tempI = i, tempJ = j;
	 if (napr != 2) {
		 while (true) {
			 if (checkingBounds(++tempI, --tempJ, tempI + 1, tempJ - 1)) {
				 if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() && _checker.cell[tempI + 1][tempJ - 1].getColor() != color)
					 break;
				 if (_checker.cell[tempI][tempJ].getClean() == true && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() == false) {
					 _checker.cell[i][j].setKill(true); return true;
				 }
			 }
			 else break;
		 }
	 }

	 tempI = i, tempJ = j;
	 if (napr != 4) {
		 while (true) {
			 if (checkingBounds(--tempI, ++tempJ, tempI - 1, tempJ + 1)) {
				 if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() && _checker.cell[tempI - 1][tempJ + 1].getColor() != color)
					 break;
				 if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() == false) {
					 _checker.cell[i][j].setKill(true); return true;
				 }
			 }
			 else break;
		 }
	 }
	 tempI = i, tempJ = j;
	 if (napr != 3) {
		 while (true) {
			 if (checkingBounds(--tempI, --tempJ, tempI - 1, tempJ - 1)) {
				 if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() && _checker.cell[tempI - 1][tempJ - 1].getColor() != color)
					 break;
				 if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() == false) {
					 _checker.cell[i][j].setKill(true); return true;
				 }
			 }
			 else break;
		 }
	 }

	 return false;
}
		
int Logic::choiceKill( Checker& _checker, Vector2i& pos, bool color)
{
	resetBacklight(_checker);
	int choice = 0;
	if (_checker.cell[pos.y / 64][pos.x / 64].getKill() && _checker.cell[pos.y / 64][pos.x / 64].getKing()) {
		choiceKillKing(_checker,pos,color);
		return 1;
	}
	   	if (_checker.cell[pos.y / 64][pos.x / 64].getKill()){
				resetBacklight(_checker);
				if (_checker.cell[pos.y / 64 - 1][pos.x / 64 + 1].getColor() == (!color) && _checker.cell[pos.y / 64 - 1][pos.x / 64 + 1].getClean() && !_checker.cell[pos.y / 64 - 2][pos.x / 64 + 2].getClean() && checkingBounds(pos.y/64-2,pos.x/64+2)) {
					_checker.cell[pos.y / 64 - 2][pos.x / 64 + 2].setBacklight(true);
					_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true); choice = 2;
				}
				if (_checker.cell[pos.y / 64 - 1][pos.x / 64 - 1].getColor() == (!color) && _checker.cell[pos.y / 64 - 1][pos.x / 64 - 1].getClean() && !_checker.cell[pos.y / 64 - 2][pos.x / 64 - 2].getClean() && checkingBounds(pos.y / 64 - 2, pos.x / 64 - 2)) {
					_checker.cell[pos.y / 64 - 2][pos.x / 64 - 2].setBacklight(true);
					_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true); choice = 2;
				}
				if (_checker.cell[pos.y / 64 + 1][pos.x / 64 + 1].getColor() == (!color) && _checker.cell[pos.y / 64 + 1][pos.x / 64 + 1].getClean() && !_checker.cell[pos.y / 64 + 2][pos.x / 64 + 2].getClean() && checkingBounds(pos.y / 64 + 2, pos.x / 64 + 2)) {
					_checker.cell[pos.y / 64 + 2][pos.x / 64 + 2].setBacklight(true);
					_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true); choice = 2;
				}
				if (_checker.cell[pos.y / 64 + 1][pos.x / 64 - 1].getColor() == (!color) && _checker.cell[pos.y / 64 + 1][pos.x / 64 - 1].getClean() && !_checker.cell[pos.y / 64 + 2][pos.x / 64 - 2].getClean() && checkingBounds(pos.y / 64 + 2, pos.x / 64 - 2)) {
					_checker.cell[pos.y / 64 + 2][pos.x / 64 - 2].setBacklight(true);
					_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true); choice = 2;
				}
				
			}
		return choice;
}

void Logic::choiceKillKing(Checker& _checker, Vector2i& pos, bool color)
{
	_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true);
	int tempI = pos.y / 64, tempJ = pos.x / 64;
	while (1){
		if (checkingBounds(--tempI, ++tempJ, tempI - 1, tempJ + 1)){
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() && _checker.cell[tempI - 1][tempJ + 1].getColor() != color) break;
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() == false){
				goCheckUR(_checker, tempI - 1, tempJ + 1, color);
				break;
			}
		}
		else break;
	}

	tempI = pos.y / 64;
	tempJ = pos.x / 64;
	while (1){
		if (checkingBounds(--tempI, --tempJ, tempI - 1, tempJ - 1)){
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() && _checker.cell[tempI - 1][tempJ - 1].getColor() != color) break;
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() == false){
				goCheckUL(_checker, tempI - 1, tempJ - 1, color);
				break;
			}
		}
		else break;
	}

	tempI = pos.y / 64;
	tempJ = pos.x / 64;
	while (1){
		if (checkingBounds(++tempI, ++tempJ, tempI + 1, tempJ + 1)){
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() && _checker.cell[tempI + 1][tempJ + 1].getColor() != color) break;
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() == false){
				goCheckDR(_checker, tempI + 1, tempJ + 1, color);
				break;
			}
		}
		else break;
	}

	tempI = pos.y / 64;
	tempJ = pos.x / 64;
	while (1){
		if (checkingBounds(++tempI, --tempJ, tempI + 1, tempJ - 1)){
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() && _checker.cell[tempI + 1][tempJ - 1].getColor() != color) break;
			if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() == false){
				goCheckDL(_checker, tempI + 1, tempJ - 1, color);
				break;
			}
		}
		else break;
	}
}

void Logic::goCheckUR(Checker& _checker, int i, int j, bool color)
{
	int tempI = i, tempJ = j;
	bool flag = false;

	while (true){
		if (checkingBounds(tempI - 1, tempJ + 1, tempI - 2, tempJ + 2)){
			if (_checker.cell[tempI-1][tempJ+1].getClean() && _checker.cell[tempI-1][tempJ+1].getColor() != color && _checker.cell[tempI - 2][tempJ + 2].getClean() && _checker.cell[tempI - 2][tempJ + 2].getColor() != color) break;
			if (_checker.cell[tempI - 1][tempJ + 1].getClean() && _checker.cell[tempI - 1][tempJ + 1].getColor() == (!color) && !_checker.cell[tempI - 2][tempJ + 2].getClean()){
				_checker.cell[tempI][tempJ].setBacklight(true);
			}
		}
		else if (!checkingBounds(tempI - 1, tempJ + 1)){
			break;
		}

		if (checkDR(_checker, tempI, tempJ, color) || checkUL(_checker, tempI, tempJ, color))
			flag = true;

		tempI--;
		tempJ++;
	}

	if (!flag) lightUR(_checker, i, j);
}

void Logic::goCheckUL(Checker& _checker, int i, int j, bool color)
{
	int tempI = i, tempJ = j;
	bool flag = false;

	while (true){
		if (checkingBounds(tempI - 1, tempJ - 1, tempI - 2, tempJ - 2)){
			if (_checker.cell[tempI-1][tempJ-1].getClean() && _checker.cell[tempI-1][tempJ-1].getColor() != color && _checker.cell[tempI - 2][tempJ - 2].getClean() && _checker.cell[tempI - 2][tempJ - 2].getColor() != color) break;
			if (_checker.cell[tempI - 1][tempJ - 1].getClean() && _checker.cell[tempI - 1][tempJ - 1].getColor() == (!color) && !_checker.cell[tempI - 2][tempJ - 2].getClean()){
				_checker.cell[tempI][tempJ].setBacklight(true);
			}
		}
		else if (!checkingBounds(tempI - 1, tempJ - 1)){
			//if (!flag) _checker.cell[tempI][tempJ].setBacklight(true);
			break;
		}

		if (checkDL(_checker, tempI, tempJ, color) || checkUR(_checker, tempI, tempJ, color)) flag = true;

		tempI--;
		tempJ--;
	}

	if (!flag) lightUL(_checker, i, j);
}

void Logic::goCheckDR(Checker& _checker, int i, int j, bool color)
{
	int tempI = i, tempJ = j;
	bool flag = false;

	while (true){
		if (checkingBounds(tempI + 1, tempJ + 1, tempI + 2, tempJ + 2)){
			if (_checker.cell[tempI+1][tempJ+1].getClean() && _checker.cell[tempI+1][tempJ+1].getColor() != color && _checker.cell[tempI + 2][tempJ + 2].getClean() && _checker.cell[tempI + 2][tempJ + 2].getColor() != color) break;
			if (_checker.cell[tempI + 1][tempJ + 1].getClean() && _checker.cell[tempI + 1][tempJ + 1].getColor() == (!color) && !_checker.cell[tempI + 2][tempJ + 2].getClean()){
				_checker.cell[tempI][tempJ].setBacklight(true);
			}
		}
		 if (!checkingBounds(tempI, tempJ)){
			break;
		}

		if (checkDL(_checker, tempI, tempJ, color) || checkUR(_checker, tempI, tempJ, color)) 
			flag = true;

		tempI++;
		tempJ++;
	}

	if (!flag)
		lightDR(_checker, i, j);
}

void Logic::goCheckDL(Checker& _checker, int i, int j, bool color)
{
	int tempI = i, tempJ = j;
	bool flag = false;

	while (true){
		if (checkingBounds(tempI + 1, tempJ - 1, tempI + 2, tempJ - 2)){
			if (_checker.cell[tempI+1][tempJ-1].getClean() && _checker.cell[tempI+1][tempJ-1].getColor() != color && _checker.cell[tempI + 2][tempJ - 2].getClean() && _checker.cell[tempI + 2][tempJ - 2].getColor() != color) break;
			if (_checker.cell[tempI + 1][tempJ - 1].getClean() && _checker.cell[tempI + 1][tempJ - 1].getColor() == (!color) && !_checker.cell[tempI + 2][tempJ - 2].getClean()){
				_checker.cell[tempI][tempJ].setBacklight(true);
			}
		}
		else if (!checkingBounds(tempI + 1, tempJ - 1)){
			break;
		}

		if (checkDR(_checker, tempI, tempJ, color) || checkUL(_checker, tempI, tempJ, color)) flag = true;

		tempI++;
		tempJ--;
	}

	if (!flag) lightDL(_checker, i, j);
}

bool Logic::moveKill(Checker& _checker, Vector2i& pos, int* ms, bool color)
{
	int i = getPositionKill(_checker);
	

	if (_checker.cell[pos.y / 64][pos.x / 64].getClean() == false && _checker.cell[pos.y / 64][pos.x / 64].getBacklight() == true){
		_checker.cell[pos.y / 64][pos.x / 64].setClean(true);
		_checker.cell[pos.y / 64][pos.x / 64].setColor(color);
		if (pos.y / 64 == 0) _checker.cell[pos.y / 64][pos.x / 64].setKing(true);
		cleanCell(_checker, i / 8, i % 8);
		cleanCell(_checker, (pos.y / 64 + i / 8) / 2, (pos.x / 64 + i % 8) / 2);
		resetBacklight(_checker);
		resetKill(_checker);
		ms[1] = pos.y / 64 * 8 + pos.x / 64;
		if (pos.y / 64 < i / 8 && pos.x / 64 - i % 8 > 0) { ms[0] = 2; }
		if (pos.y / 64 < i / 8 && pos.x / 64 - i % 8 < 0) { ms[0] = 1; }
		if (pos.y / 64 > i / 8 && pos.x / 64 - i % 8 > 0) { ms[0] = 3; }
		if (pos.y / 64 > i / 8 && pos.x / 64 - i % 8 < 0) { ms[0] = 4; }
		return true;
	}
	return false;
}

bool Logic::moveKillKing(Checker& _checker, Vector2i& pos, bool color, int* ms)
{
	
	int i = getPositionKill(_checker);
	int i1 = i / 8, j1 = i % 8;
	if (_checker.cell[pos.y / 64][pos.x / 64].getClean() == false && _checker.cell[pos.y / 64][pos.x / 64].getBacklight() == true){
		if((pos.y/64-i1<0) && (pos.x/64-j1>0)){
			while(i1!= pos.y / 64){
				cleanCell(_checker, i1, j1);
				i1--;
				j1++;
			}
			_checker.cell[i1][j1].setClean(true);
			_checker.cell[i1][j1].setColor(color);
			_checker.cell[i1][j1].setKing(true);
			resetBacklight(_checker);
			resetKill(_checker);
			ms[0] = 2;
			ms[1] = i1 * 8 + j1;
			return true;
		}

		if ((pos.y / 64 - i1<0) && (pos.x / 64 - j1<0)) {
			while (i1 != pos.y / 64) {
				cleanCell(_checker, i1, j1);
				i1--;
				j1--;
			}
			_checker.cell[i1][j1].setClean(true);
			_checker.cell[i1][j1].setColor(color);
			_checker.cell[i1][j1].setKing(true);
			resetBacklight(_checker);
			resetKill(_checker);
			ms[0] = 1;
			ms[1] = i1 * 8 + j1;
			return true;
		}

		if ((pos.y / 64 - i1>0) && (pos.x / 64 - j1>0)) {
			while (i1 != pos.y / 64) {
				cleanCell(_checker, i1, j1);
				i1++;
				j1++;
			}
			_checker.cell[i1][j1].setClean(true);
			_checker.cell[i1][j1].setColor(color);
			_checker.cell[i1][j1].setKing(true);
			resetBacklight(_checker);
			resetKill(_checker);
			ms[0] = 3;
			ms[1] = i1 * 8 + j1;
			return true;
		}

		if ((pos.y / 64 - i1>0) && (pos.x / 64 - j1<0)) {
			while (i1 != pos.y / 64) {
				cleanCell(_checker, i1, j1);
				i1++;
				j1--;
			}
			_checker.cell[i1][j1].setClean(true);
			_checker.cell[i1][j1].setColor(color);
			_checker.cell[i1][j1].setKing(true);
			resetBacklight(_checker);
			resetKill(_checker);
			ms[0] = 4;
			ms[1] = i1 * 8 + j1;
			return true;
		}

	}
	return false;
}

void Logic::choice (Checker& _checker, Vector2i& pos)
{
		resetBacklight(_checker);
		if (checkingBounds(pos.y / 64 - 1, pos.x / 64 + 1) && _checker.cell[pos.y / 64 - 1][pos.x / 64 + 1].getClean() == false) {
			_checker.cell[pos.y / 64 - 1][pos.x / 64 + 1].setBacklight(true);
			_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true);
		}
		if (checkingBounds(pos.y / 64 - 1, pos.x / 64 - 1) && _checker.cell[pos.y / 64 - 1][pos.x / 64 - 1].getClean() == false) {
			_checker.cell[pos.y / 64 - 1][pos.x / 64 - 1].setBacklight(true);
			_checker.cell[pos.y / 64][pos.x / 64].setBacklight(true);
		}
	}

int Logic::choiceKing(Checker& _checker, Vector2i& pos)
{
	resetBacklight(_checker);
	int i = pos.y/64, j = pos.x/64;
	while (checkingBounds(++i, ++j) && _checker.cell[i][j].getClean() == false)
		_checker.cell[i][j].setBacklight(true);

	i = pos.y/64; j = pos.x/64;
	while (checkingBounds(--i, ++j) && _checker.cell[i][j].getClean() == false)
		_checker.cell[i][j].setBacklight(true);
	
	i = pos.y/64; j = pos.x/64;
	while (checkingBounds(++i, --j) && _checker.cell[i][j].getClean() == false)
		_checker.cell[i][j].setBacklight(true);

	i = pos.y/64; j = pos.x/64;
	while(checkingBounds(--i, --j) && _checker.cell[i][j].getClean() == false)
		_checker.cell[i][j].setBacklight(true);

	return (pos.y / 64 * 8 + pos.x / 64);
}

bool Logic::moveKing(Checker& _checker, Vector2i& pos, int xy, bool color)
{
	if(_checker.cell[pos.y / 64][pos.x / 64].getClean() == false && _checker.cell[pos.y / 64][pos.x / 64].getBacklight() == true){
		_checker.cell[pos.y / 64][pos.x / 64].setClean(true);
		_checker.cell[pos.y / 64][pos.x / 64].setColor(color);
		_checker.cell[pos.y / 64][pos.x / 64].setKing(true);
		_checker.cell[xy / 8][xy % 8].setClean(false);
		_checker.cell[xy / 8][xy % 8].setKing(false);
		resetBacklight(_checker);
		return true;

	}
	return false;
}

bool Logic::move(Checker& _checker, Vector2i& pos,bool color)
{

			if (_checker.cell[pos.y / 64][pos.x / 64].getClean() == false && _checker.cell[pos.y / 64][pos.x / 64].getBacklight() == true){
				_checker.cell[pos.y / 64][pos.x / 64].setClean(true);
				_checker.cell[pos.y / 64][pos.x / 64].setColor(color);
				if (pos.y / 64 == 0)
					_checker.cell[pos.y / 64][pos.x / 64].setKing(true);
				if (_checker.cell[pos.y / 64 + 1][pos.x / 64 - 1].getBacklight()) _checker.cell[pos.y / 64 + 1][pos.x / 64 - 1].setClean(false);
				if (_checker.cell[pos.y / 64 + 1][pos.x / 64 + 1].getBacklight()) _checker.cell[pos.y / 64 + 1][pos.x / 64 + 1].setClean(false);
				resetBacklight(_checker);
				return true;
				
			}
			return false;
}

void Logic::resetBacklight(Checker& _checker)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_checker.cell[i][j].getBacklight())
				_checker.cell[i][j].setBacklight(false);
}

void Logic::resetKill(Checker& _checker)
{
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++)
		if (_checker.cell[i][j].getKill()) _checker.cell[i][j].setKill(false);
}

 bool Logic::checkingBounds(int i , int j)
{
	if (i > -1 && i<8 && j>-1 && j < 8) return true;
	else return false;
}

 bool Logic::checkingBounds(int i, int j, int i1, int j1)
 {
	 if (i > -1 && i<8 && j>-1 && j < 8 & i1 > -1 && i1<8 && j1>-1 && j1 < 8) return true;
	 else return false;
 }

int Logic::getPositionKill(Checker& _checker)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_checker.cell[i][j].getClean() && _checker.cell[i][j].getBacklight())
				return i * 8 + j;
	return 0;
}

void Logic::cleanCell(Checker& _checker, int i, int j)
{
	_checker.cell[i][j].setClean(false);
	_checker.cell[i][j].setColor(false);
	_checker.cell[i][j].setKing(false);
	_checker.cell[i][j].setBacklight(false);
}
