#pragma once
#include "Checker.h"

class Light{
public:	

	/*
	Необходимая проверка для дамок после рубки на то,
	должна ли она еще бить, и если должна, подстветить варианты только тех клеток,
	становление в которые позволит ей совершить еще одну рубку
	*/
	 bool checkUR(Checker&, int, int, bool);
	 bool checkUL(Checker&, int, int, bool); 
	 bool checkDR(Checker&, int, int, bool); 
	 bool checkDL(Checker&, int, int, bool); 

	/*
	В том случае, если дамка не должна бить, то мы должны подсветить все возможные варианты клеток,
	находящиеся за побитой шашкой
	*/

	 void lightUR(Checker&, int, int);
	 void lightUL(Checker&, int, int);
	 void lightDR(Checker&, int, int);
	 void lightDL(Checker&, int, int);
};

