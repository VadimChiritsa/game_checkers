#pragma once
#include "Checker.h"
#include <vector>
#include "Move.h"
#include "Logic.h"
using namespace std;

class ArtificialIntelligence: public Light{
public:

	int searchAlfaBeta(Checker& ,bool, int, int, Move&); //����������� ������� ���� ��������� ��������� ���� � ����� ������ ������� �� ���
	int evaluate(Checker&, bool); //��������� �������, ��������������������� �������� ��������� ���� �� �����
	bool generateAllKill(vector<Move>&, Checker&, bool, Move&,int); //������ � ���� ���� ��������� ��������� ���� ������� �����, � ��� ������, ���� ������ ����
	bool generateAllKillKing(vector<Move>&, Checker&, bool, int); //������ � ���� ���� ��������� ��������� ���� �����, � ��� ������ ���� ������ ����
	void generateAllMoves(vector<Move>&, Checker&, bool, int); //������ � ���� ���� ��������� ����� ����� ��� �����, ���� ����������� �����
	bool makeMove(Checker&, Move,int); //��� ����� ��� �����, ���� ��� ������������� ����
	bool makeMoveKill(Checker&, Move, int); //���������� �����
	void unMakeMove(Checker&, Move,bool); //������ ����
	void unMakeMoveKill(Checker&, Move, bool); //������ ���� ����� �����
	static bool needKill(Checker&, Move&); //����������� ����, ����� �� �����
};



