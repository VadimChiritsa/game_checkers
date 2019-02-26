#pragma once

class Move{
	int oldPoz;
	int newPoz;
	bool flag;
	int killPoz;
	bool king;

public:
	Move();
	Move(int, int, bool, int, bool);

	void setOldPoz(int);
	void setNewPoz(int);
	void setKillPoz(int);
	void setKing(bool);

	void null();
	int getOldPoz();
	int getNewPoz();
	bool getFlag();
	int getKillPoz();
	bool getKing();
};