#pragma once
#include "Checker.h"
#include "Light.h"

class Logic : public Light {
	/*
	�������� ����� �� ���� ������������
	*/
	

public:
	void goCheckUR(Checker&, int, int, bool);
	void goCheckUL(Checker&, int, int, bool);
	void goCheckDR(Checker&, int, int, bool);
	void goCheckDL(Checker&, int, int, bool);
	int getPositionKill(Checker&);

	bool needKill(Checker&, bool, int*);//�������� �� ��, ������ �� ���� ������� �����
	static bool needKillKing(Checker&, int, int, bool, int);//�������� �� ��, ������ �� ���� �����
	int choiceKill(Checker&, Vector2i& , bool);// ����� ������ ��� �����, ������� ������ ����
	void choiceKillKing(Checker&, Vector2i&, bool);//����� ������ ��� �����, ������� ������ ����

	bool moveKill( Checker&, Vector2i&, int*, bool);
	bool moveKillKing(Checker&, Vector2i&, bool, int*);
	
	void choice(Checker&, Vector2i& );
	int choiceKing(Checker&, Vector2i&);
	bool move( Checker& , Vector2i&, bool);
	bool moveKing(Checker&, Vector2i&, int, bool);
	
	void resetBacklight(Checker&);//�������� ��������� ���� ������
	static bool checkingBounds(int, int);
	static bool checkingBounds(int, int, int, int);
	void resetKill(Checker&);
	static void cleanCell(Checker&, int, int);
};
