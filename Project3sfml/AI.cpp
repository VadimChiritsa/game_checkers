#include "AI.h"

int ArtificialIntelligence::searchAlfaBeta(Checker& _checker, bool color, int depth, int side, Move& mov)
{
	if (depth == 0)
		return evaluate(_checker,color);
	bool flag=false;
	int max = -999;
	vector <Move> list;
	
	if (generateAllKill(list, _checker, color, mov, depth)) {
		while (!list.empty()) {
			int tmp;
			flag=makeMoveKill(_checker, list[list.size() - 1], side);
			if (needKill(_checker, list[list.size() - 1]))
				tmp = searchAlfaBeta(_checker, color, depth - 1, side, mov);
			else 
				tmp = -searchAlfaBeta(_checker, !color, depth - 1, side + 1, mov);
			unMakeMoveKill(_checker, list[list.size() - 1],flag);

			if (tmp >= max) {
				max = tmp;
				if (depth == 3)
					mov = list[list.size() - 1];
			}

			list.pop_back();
		}
	}
	
	else {
		bool flag1=false;
		generateAllMoves(list, _checker, color, side);
		while (!list.empty()) {
			flag1=makeMove(_checker, list[list.size() - 1],side);
			int tmp = -searchAlfaBeta(_checker, !color, depth - 1, side+1, mov);
			unMakeMove(_checker, list[list.size() - 1],flag1);

			if (tmp >= max) {
				max = tmp;
				if(depth==3)
					mov = list[list.size() - 1];
			}

			list.pop_back();
		}
	}
	
		return max;
}

bool ArtificialIntelligence::needKill(Checker& _checker, Move& move)
{
	int i = move.getNewPoz()/8, j = move.getNewPoz() % 8;
	int i1 = move.getOldPoz() / 8, j1 = move.getOldPoz() % 8;
	bool flag = false;
	bool flag2 = false;
	bool color = _checker.cell[i][j].getColor();
	int napr=0;
	if (i - i1 < 0 && j - j1 < 0) napr = 1;
	if (i - i1 > 0 && j - j1 < 0) napr = 4;
	if (i - i1 > 0 && j - j1 > 0) napr = 3;
	if (i - i1 < 0 && j - j1 > 0) napr = 2;

		if (_checker.cell[i][j].getKing())
			(Logic::needKillKing(_checker, i, j, color, napr) == true) ? flag2 = true : flag2 = false;
		else {

			if ( Logic::checkingBounds(i - 1, j + 1, i - 2, j + 2) && _checker.cell[i - 1][j + 1].getClean() && _checker.cell[i - 1][j + 1].getColor() == (!color) && !_checker.cell[i - 2][j + 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (Logic::checkingBounds(i - 1, j - 1, i - 2, j - 2) && _checker.cell[i - 1][j - 1].getClean() && _checker.cell[i - 1][j - 1].getColor() == (!color) && !_checker.cell[i - 2][j - 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (Logic::checkingBounds(i + 1, j + 1, i + 2, j + 2) && _checker.cell[i + 1][j + 1].getClean() && _checker.cell[i + 1][j + 1].getColor() == (!color) && !_checker.cell[i + 2][j + 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}
			if (Logic::checkingBounds(i + 1, j - 1, i + 2, j - 2) && _checker.cell[i + 1][j - 1].getClean() && _checker.cell[i + 1][j - 1].getColor() == (!color) && !_checker.cell[i + 2][j - 2].getClean()) {
				_checker.cell[i][j].setKill(true);
				flag = true;
			}

		}
		if (flag || flag2) return true;
		else return false;
	


}

bool ArtificialIntelligence::generateAllKill(vector<Move>& list, Checker& _checker, bool color, Move& mov, int depth)
{
	bool flag = false;
	bool kill=false;
	if (!(mov.getNewPoz() == 0 && mov.getOldPoz() == 0) && depth == 5)
		kill = true;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8;j++){

			if(kill)
			if (i != mov.getNewPoz() / 8 && j != mov.getNewPoz() % 8)
				continue;

			if (!_checker.cell[i][j].getClean() || _checker.cell[i][j].getColor() != color)
				continue;

			if(_checker.cell[i][j].getKing()){
				if (generateAllKillKing(list, _checker, color, i * 8 + j))
					flag = true;
				continue;
			}

			if (Logic::checkingBounds(i - 1, j + 1, i - 2, j + 2) && _checker.cell[i - 1][j + 1].getClean() && _checker.cell[i - 1][j + 1].getColor() == (!color) && !_checker.cell[i - 2][j + 2].getClean()) {
				
				if (_checker.cell[i - 1][j + 1].getKing()) {
					Move element(i * 8 + j, (i - 2) * 8 + j + 2, true, (i - 1) * 8 + j + 1, true);
					list.push_back(element);
				}
				else {
					Move element(i * 8 + j, (i - 2) * 8 + j + 2, true, (i - 1) * 8 + j + 1, false);
					list.push_back(element);
				}
			
				flag = true;
			}
			if (Logic::checkingBounds(i - 1, j - 1, i - 2, j - 2) && _checker.cell[i - 1][j - 1].getClean() && _checker.cell[i - 1][j - 1].getColor() == (!color) && !_checker.cell[i - 2][j - 2].getClean()) {
				
				if (_checker.cell[i - 1][j - 1].getKing()) {
					Move element(i * 8 + j, (i - 2) * 8 + j - 2, true, (i - 1) * 8 + j - 1, true);
					list.push_back(element);
				}
				else {
					Move element(i * 8 + j, (i - 2) * 8 + j - 2, true, (i - 1) * 8 + j - 1, false);
					list.push_back(element);
				}

				flag = true;
			}
			if (Logic::checkingBounds(i + 1, j + 1, i + 2, j + 2) && _checker.cell[i + 1][j + 1].getClean() && _checker.cell[i + 1][j + 1].getColor() == (!color) && !_checker.cell[i + 2][j + 2].getClean()) {
				
				if (_checker.cell[i + 1][j + 1].getKing()) {
					Move element(i * 8 + j, (i + 2) * 8 + j + 2, true, (i + 1) * 8 + j + 1, true);
					list.push_back(element);
				}
				else {
					Move element(i * 8 + j, (i + 2) * 8 + j + 2, true, (i + 1) * 8 + j + 1, false);
					list.push_back(element);
				}

				flag = true;
			}

			if (Logic::checkingBounds(i + 1, j - 1, i + 2, j - 2) && _checker.cell[i + 1][j - 1].getClean() && _checker.cell[i + 1][j - 1].getColor() == (!color) && !_checker.cell[i + 2][j - 2].getClean()) {
				
				if (_checker.cell[i + 1][j - 1].getKing()) {
					Move element(i * 8 + j, (i + 2) * 8 + j - 2, true, (i + 1) * 8 + j - 1, true);
					list.push_back(element);
				}
				else {
					Move element(i * 8 + j, (i + 2) * 8 + j - 2, true, (i + 1) * 8 + j - 1, false);
					list.push_back(element);
				}

				flag = true;
			}


		}

	return flag;
}

bool ArtificialIntelligence::generateAllKillKing(vector<Move>& list, Checker& _checker, bool color, int temp)
{
	bool flag = false, needKill = false;

	int tempI = temp / 8, tempJ = temp % 8;
	int killI, killJ;
		while (true) {
			if (Logic::checkingBounds(++tempI, ++tempJ, tempI + 1, tempJ + 1))
			{
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() == color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() && _checker.cell[tempI + 1][tempJ + 1].getColor() != color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ + 1].getClean() == false) {
				
					killI = tempI;
					killJ = tempJ;
					flag = true;
					tempI += 1; tempJ += 1;
					while(true){

							if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {

								if (checkUR(_checker, tempI, tempJ, color) || checkDL(_checker, tempI, tempJ, color)) {
									needKill = true;
									if (_checker.cell[killI][killJ].getKing()) {
											Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, true);
											list.push_back(element);
										}
										else {
											Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, false);
											list.push_back(element);
										}

								}
								tempI++; tempJ++;
						
						}
						else break;
					}
					

					if (!needKill) {
						tempI = killI + 1;
						tempJ = killJ + 1;
						while (true) {
							if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI++ * 8 + tempJ++, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI++ * 8 + tempJ++, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							else break;
						}

					}

					break;
				}
			}
			else break;
		}
	


		tempI = temp / 8, tempJ = temp % 8;

		while (true) {
			if (Logic::checkingBounds(++tempI, --tempJ, tempI + 1, tempJ - 1))
			{
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() == color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() && _checker.cell[tempI + 1][tempJ - 1].getColor() != color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI + 1][tempJ - 1].getClean() == false) {
				
					killI = tempI;
					killJ = tempJ;

					
					flag = true;
					tempI += 1; tempJ -= 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							if (checkUL(_checker, tempI, tempJ, color) || checkDR(_checker, tempI, tempJ, color)) {
								needKill = true;

								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							tempI++; tempJ--;
						}
						else break;
					}
					if (!needKill) {
						tempI = killI + 1;
						tempJ = killJ - 1;
						while (true) {
							if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI++ * 8 + tempJ--, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI++ * 8 + tempJ--, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							else break;
						}

					}


					break;
				}
			}
			else break;
		}


		tempI = temp / 8, tempJ = temp % 8;

		while (true) {
			if (Logic::checkingBounds(--tempI, --tempJ, tempI - 1, tempJ - 1))
			{
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() == color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() && _checker.cell[tempI - 1][tempJ - 1].getColor() != color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ - 1].getClean() == false) {

					killI = tempI;
					killJ = tempJ;

					flag = true;
					tempI -= 1; tempJ -= 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							if (checkUR(_checker, tempI, tempJ, color) || checkDL(_checker, tempI, tempJ, color)) {
								needKill = true;
								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI-- * 8 + tempJ--, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI-- * 8 + tempJ--, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							tempI--; tempJ--;
						}
						else break;
					}
					if (!needKill) {
						tempI = killI - 1;
						tempJ = killJ - 1;
						while (true) {
							if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI-- * 8 + tempJ--, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI-- * 8 + tempJ--, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							else break;
						}

					}


					break;
				}
			}
			else break;
		}



		tempI = temp / 8, tempJ = temp % 8;

		while (true) {
			if (Logic::checkingBounds(--tempI, ++tempJ, tempI - 1, tempJ + 1))
			{
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() == color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() && _checker.cell[tempI - 1][tempJ + 1].getColor() != color)
					break;
				if (_checker.cell[tempI][tempJ].getClean() && _checker.cell[tempI][tempJ].getColor() != color && _checker.cell[tempI - 1][tempJ + 1].getClean() == false) {
					
					killI = tempI;
					killJ = tempJ;

					flag = true;
					tempI -= 1; tempJ += 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							if (checkUL(_checker, tempI, tempJ, color) || checkDR(_checker, tempI, tempJ, color)) {
								needKill = true;

								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI * 8 + tempJ, true, killI * 8 + killJ, false);
									list.push_back(element);
								}
							}
							tempI--; tempJ++;
						}
						else break;
					}
					if (!needKill) {
						tempI = killI - 1;
						tempJ = killJ + 1;
						while (true) {
							if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
								if (_checker.cell[killI][killJ].getKing()) {
									Move element(temp, tempI-- * 8 + tempJ++, true, killI * 8 + killJ, true);
									list.push_back(element);
								}
								else {
									Move element(temp, tempI-- * 8 + tempJ++, true, killI * 8 + killJ, false);
									list.push_back(element);
								}

							}
							else break;
						}

					}



					break;
				}
			}
			else break;
		}

		return flag;
}//Ï

void ArtificialIntelligence::generateAllMoves(vector<Move>& list, Checker& _checker, bool color, int side)
{

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {

			if (_checker.cell[i][j].getClean() && _checker.cell[i][j].getColor() == color) {

				if (_checker.cell[i][j].getKing()) {

					int tempI = i - 1, tempJ = j + 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							Move element(i * 8 + j, tempI-- * 8 + tempJ++, false, -1, false);
							list.push_back(element);
						}
						else break;
					}

					tempI = i - 1, tempJ = j - 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							Move element(i * 8 + j, tempI-- * 8 + tempJ--, false, -1, false);
							list.push_back(element);
						}
						else break;
					}

					tempI = i + 1, tempJ = j + 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							Move element(i * 8 + j, tempI++ * 8 + tempJ++, false, -1, false);
							list.push_back(element);
						}
						else break;
					}

					tempI = i + 1, tempJ = j - 1;
					while (true) {
						if (Logic::checkingBounds(tempI, tempJ) && _checker.cell[tempI][tempJ].getClean() == false) {
							Move element(i * 8 + j, tempI++ * 8 + tempJ--, false, -1, false);
							list.push_back(element);
						}
						else break;
					}

					continue;
				}
				else {
					if (side % 2 == 0) {
						if (Logic::checkingBounds(i + 1, j + 1))
							if (!_checker.cell[i + 1][j + 1].getClean()) {
								Move element(i * 8 + j, (i + 1) * 8 + j + 1, false, -1, false);
								list.push_back(element);
							}

						if (Logic::checkingBounds(i + 1, j - 1))
							if (!_checker.cell[i + 1][j - 1].getClean()) {
								Move element(i * 8 + j, (i + 1) * 8 + j - 1, false, -1, false);
								list.push_back(element);
							}
					}

					if (side % 2 == 1) {
						if (Logic::checkingBounds(i - 1, j + 1))
							if (!_checker.cell[i - 1][j + 1].getClean()) {
								Move element(i * 8 + j, (i - 1) * 8 + j + 1, false, -1, false);
								list.push_back(element);
							}

						if (Logic::checkingBounds(i - 1, j - 1))
							if (!_checker.cell[i - 1][j - 1].getClean()) {
								Move element(i * 8 + j, (i - 1) * 8 + j - 1, false, -1, false);
								list.push_back(element);
							}
					}
				}


			}
		}
}

bool ArtificialIntelligence::makeMove(Checker& _checker, Move move, int side)
{
	int i2 = move.getNewPoz(), i1 = move.getOldPoz();

		if (_checker.cell[i1 / 8][i1 % 8].getKing()) {
			_checker.cell[i2 / 8][i2 % 8].setClean(true);
			_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());
			_checker.cell[i2 / 8][i2 % 8].setKing(true);
			Logic::cleanCell(_checker, i1 / 8, i1 % 8);
		}

		else {
			_checker.cell[i2 / 8][i2 % 8].setClean(true);
			_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());
			Logic::cleanCell(_checker, i1 / 8, i1 % 8);
			
			if (side%2==0) {
				if (i2 / 8 == 7) {
					_checker.cell[i2 / 8][i2 % 8].setKing(true);
					return true;
				}
			}

			if (side % 2 == 1) {
				if (i2 / 8 == 0) {
					_checker.cell[i2 / 8][i2 % 8].setKing(true);
					return true;
				}
			}
		}

		return false;
}

bool ArtificialIntelligence::makeMoveKill(Checker& _checker, Move move, int side)
{

	int i2 = move.getNewPoz(), i1 = move.getOldPoz();
	bool flag = false;

	if (_checker.cell[i1 / 8][i1 % 8].getKing()) {
		flag = true;
		_checker.cell[i2 / 8][i2 % 8].setClean(true);
		_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());
		_checker.cell[i2 / 8][i2 % 8].setKing(true);
		
		if(i2/8>i1/8 && i2%8>i1%8)
		for (int i = i1 / 8, j = i1 % 8; i < i2 / 8; i++,j++) {
			
			Logic::cleanCell(_checker, i, j);
		}

		if (i2 / 8>i1 / 8 && i2 % 8<i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i < i2 / 8; i++, j--) {
			
				Logic::cleanCell(_checker, i, j);
			}

		if (i2 / 8<i1 / 8 && i2 % 8>i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i > i2 / 8; i--, j++) {
			
				Logic::cleanCell(_checker, i, j);
			}

		if (i2 / 8<i1 / 8 && i2 % 8<i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i > i2 / 8; i--, j--) {
				
				Logic::cleanCell(_checker, i, j);
			}
	}

	
	else {
		_checker.cell[i2 / 8][i2 % 8].setClean(true);
		
		_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());
		Logic::cleanCell(_checker, i1 / 8, i1 % 8);
		Logic::cleanCell(_checker, (i2 / 8 + i1 / 8) / 2, (i2 % 8 + i1 % 8) / 2);
		if (side % 2 == 0) {
			if (i2 / 8 == 7) {
				_checker.cell[i2 / 8][i2 % 8].setKing(true);
			}
		}

		if (side % 2 == 1) {
			if (i2 / 8 == 0) {
				_checker.cell[i2 / 8][i2 % 8].setKing(true);
			}
		}

	}

	return flag;
}

void ArtificialIntelligence::unMakeMove(Checker& _checker, Move move, bool flag)
{
	int i2 = move.getNewPoz(), i1 = move.getOldPoz();

	if (_checker.cell[i2 / 8][i2 % 8].getKing() && !flag) {

		_checker.cell[i1 / 8][i1 % 8].setClean(true);
		_checker.cell[i1 / 8][i1 % 8].setColor(_checker.cell[i2 / 8][i2 % 8].getColor());
		_checker.cell[i1 / 8][i1 % 8].setKing(true);
		Logic::cleanCell(_checker, i2 / 8, i2 % 8);
	}

	else {
		_checker.cell[i1 / 8][i1 % 8].setClean(true);
		_checker.cell[i1 / 8][i1 % 8].setColor(_checker.cell[i2 / 8][i2 % 8].getColor());
		Logic::cleanCell(_checker, i2 / 8, i2 % 8);
	}

}

void ArtificialIntelligence::unMakeMoveKill(Checker& _checker, Move move, bool flag)
{
	int i2 = move.getOldPoz(), i1 = move.getNewPoz();
	int tempI = move.getKillPoz() / 8, tempJ = move.getKillPoz() % 8;

	if (_checker.cell[i1 / 8][i1 % 8].getKing() && flag) {

		_checker.cell[i2 / 8][i2 % 8].setClean(true);
		_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());
		_checker.cell[i2 / 8][i2 % 8].setKing(true);

		if (i2 / 8>i1 / 8 && i2 % 8>i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i < i2 / 8; i++, j++) {
				if(tempI==i && tempJ==j && move.getKing()){
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					_checker.cell[i][j].setKing(true);
					break;
				}

				if (tempI == i && tempJ == j && !move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					break;
				}

				
			}

		if (i2 / 8>i1 / 8 && i2 % 8<i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i < i2 / 8; i++, j--) {
				if (tempI == i && tempJ == j && move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					_checker.cell[i][j].setKing(true);
					break;
				}

				if (tempI == i && tempJ == j && !move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					break;
				}
				
			}

		if (i2 / 8<i1 / 8 && i2 % 8>i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i > i2 / 8; i--, j++) {
				if (tempI == i && tempJ == j && move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					_checker.cell[i][j].setKing(true);
					break;
				}

				if (tempI == i && tempJ == j && !move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					break;
				}
			
			}

		if (i2 / 8<i1 / 8 && i2 % 8<i1 % 8)
			for (int i = i1 / 8, j = i1 % 8; i > i2 / 8; i--, j--) {
				if (tempI == i && tempJ == j && move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					_checker.cell[i][j].setKing(true);
					break;
				}

				if (tempI == i && tempJ == j && !move.getKing()) {
					_checker.cell[i][j].setClean(true);
					_checker.cell[i][j].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
					break;
				}
			
			}

		Logic::cleanCell(_checker, i1 / 8, i1 % 8);
		
		return;
	}

	else {
		_checker.cell[i2 / 8][i2 % 8].setClean(true);
		_checker.cell[i2 / 8][i2 % 8].setColor(_checker.cell[i1 / 8][i1 % 8].getColor());

		if (move.getKing())
			_checker.cell[(i2 / 8 + i1 / 8) / 2][(i2 % 8 + i1 % 8) / 2].setKing(true);

		_checker.cell[(i2 / 8 + i1 / 8) / 2][(i2 % 8 + i1 % 8) / 2].setClean(true);
		_checker.cell[(i2 / 8 + i1 / 8) / 2][(i2 % 8 + i1 % 8) / 2].setColor(!_checker.cell[i1 / 8][i1 % 8].getColor());
		Logic::cleanCell(_checker, i1 / 8, i1 % 8);
	}

}

int ArtificialIntelligence::evaluate(Checker& _checker, bool color)
{
	int temp = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++){
			if(_checker.cell[i][j].getClean()){

				if (_checker.cell[i][j].getColor() == color && _checker.cell[i][j].getKing()) {
					temp += 50;
					continue;
				}

				if(_checker.cell[i][j].getColor() == color){
					temp += 15;
					continue;
				}

				if (_checker.cell[i][j].getColor() != color && _checker.cell[i][j].getKing()) {
					temp -= 50;
					continue;
				}

				if (_checker.cell[i][j].getColor() != color)
					temp -= 15;
			}
		}
		
	return temp;
}
