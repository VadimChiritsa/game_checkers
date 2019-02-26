#include "Person.h"

Person::Person(char* name)
{
	strcpy_s(this->name, name);
	win = 0;
	standoff = 0;
	defeat = 0;
}

Person::Person(char* name, int win , int standoff, int defeat)
{
	strcpy_s(this->name, name);
	this->win = win;
	this->standoff = standoff;
	this->defeat = defeat;
}

void Person::increaseWin()
{
	win++;
}

void Person::increaseStandoff()
{
	standoff++;
}

void Person::increaseDefeat()
{
	defeat++;
}

char* Person::getName()
{
	return name;
}

int Person::getWin()
{
	return win;
}

int Person::getStandoff()
{
	return standoff;
}

int Person::getDefeat()
{
	return defeat;
}

void Person::writeBIN(char* fileName)
{
		ofstream file(fileName, ios::app | ios::binary);
		
		file.write(reinterpret_cast<char*>(this->name), 20 * sizeof(char));
		file.write(reinterpret_cast<char*>(&this->win), sizeof(int));
		file.write(reinterpret_cast<char*>(&this->standoff), sizeof(int));
		file.write(reinterpret_cast<char*>(&this->defeat), sizeof(int));
		file.close();
	
}

Person Person::readBIN(char* fileName, int line)
{
	ifstream file(fileName, ios::binary | ios::in);
	
	int Win;
	int Standoff;
	int Defeat;
	int currentLine = 0;
	while (currentLine < line && !file.eof())
	{
		char* s = new char[20];		
		file.read(reinterpret_cast<char*>(s), 20 * sizeof(char));
		delete s;
		file.read(reinterpret_cast<char*>(&Win), sizeof(int));
		file.read(reinterpret_cast<char*>(&Standoff), sizeof(int));
		file.read(reinterpret_cast<char*>(&Defeat), sizeof(int));
		currentLine++;
	}
	if (!file.eof())
	{
		char *s = new char[20];
		
		file.read(reinterpret_cast<char*>(s), 20 * sizeof(char));
		file.read(reinterpret_cast<char*>(&Win), sizeof(int));
		file.read(reinterpret_cast<char*>(&Standoff), sizeof(int));
		file.read(reinterpret_cast<char*>(&Defeat), sizeof(int));
		file.close();
		
			return Person(s,Win,Standoff,Defeat);
	
	}
}