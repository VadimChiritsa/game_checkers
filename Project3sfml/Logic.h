#pragma once
#include "Checker.h"
#include "Light.h"

class Logic : public Light {
	/*
	проверка дамки во всех направлениях
	*/
	

public:
	void goCheckUR(Checker&, int, int, bool);
	void goCheckUL(Checker&, int, int, bool);
	void goCheckDR(Checker&, int, int, bool);
	void goCheckDL(Checker&, int, int, bool);
	int getPositionKill(Checker&);

	bool needKill(Checker&, bool, int*);//проверка на то, должна ли бить обычная шашка
	static bool needKillKing(Checker&, int, int, bool, int);//проверка на то, должна ли бить дамка
	int choiceKill(Checker&, Vector2i& , bool);// выбор только той шашки, которая должна бить
	void choiceKillKing(Checker&, Vector2i&, bool);//выбор только той дамки, котороя должна бить

	bool moveKill( Checker&, Vector2i&, int*, bool);
	bool moveKillKing(Checker&, Vector2i&, bool, int*);
	
	void choice(Checker&, Vector2i& );
	int choiceKing(Checker&, Vector2i&);
	bool move( Checker& , Vector2i&, bool);
	bool moveKing(Checker&, Vector2i&, int, bool);
	
	void resetBacklight(Checker&);//отменить выделение всех клеток
	static bool checkingBounds(int, int);
	static bool checkingBounds(int, int, int, int);
	void resetKill(Checker&);
	static void cleanCell(Checker&, int, int);
};
