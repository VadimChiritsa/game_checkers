#pragma once
#include <string.h>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Person{
	char name[20];
	int win;
	int standoff;
	int defeat;

public:
	Person(){};
	Person(char*);
	Person(char*, int, int, int);
	~Person(){};

	void increaseWin();
	void increaseStandoff();
	void increaseDefeat();

	char* getName();
	int getWin();
	int getStandoff();
	int getDefeat();

	void writeBIN(char*);
	static Person readBIN(char*, int);
};


