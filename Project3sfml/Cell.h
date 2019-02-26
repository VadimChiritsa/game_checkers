#pragma once
#include "TextureAndBoard.h"

class Cell : public TextureAndBoard { 
private:

	bool clean;
	bool color;
	bool king;
	bool backlight;
	bool kill;

public:

	Cell();

	void setClean(bool);
	void setColor(bool);
	void setKing(bool);
	void setBacklight(bool);
	void setKill(bool);
	
	bool getClean() const;
	bool getColor() const;
	bool getKing() const;
	bool getBacklight() const;
	bool getKill() const;
};



