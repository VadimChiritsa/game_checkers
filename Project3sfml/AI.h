#pragma once
#include "Checker.h"
#include <vector>
#include "Move.h"
#include "Logic.h"
using namespace std;

class ArtificialIntelligence: public Light{
public:

	int searchAlfaBeta(Checker& ,bool, int, int, Move&); //рекурсивный перебор всех возможный вариантов хода и выбор самого лучшего из них
	int evaluate(Checker&, bool); //оценочна€ функци€, возвращающа€численное значение положени€ игры на доске
	bool generateAllKill(vector<Move>&, Checker&, bool, Move&,int); //запись в стек всех возможных вариантов хода обычной шашки, в том случае, если должны бить
	bool generateAllKillKing(vector<Move>&, Checker&, bool, int); //запись в стек всех возможных вариантов хода дамки, в том случае если должны бить
	void generateAllMoves(vector<Move>&, Checker&, bool, int); //запись в стек всех возможных ходов шашки или дамки, если возможности рубки
	bool makeMove(Checker&, Move,int); //ход шашки или дамки, если нет необходимости бить
	bool makeMoveKill(Checker&, Move, int); //совершение рубки
	void unMakeMove(Checker&, Move,bool); //отмена хода
	void unMakeMoveKill(Checker&, Move, bool); //отмена хода после рубки
	static bool needKill(Checker&, Move&); //определение того, нужна ли рубка
};



