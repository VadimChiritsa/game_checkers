#pragma once
#include "Person.h"

class FileBIN{
public:
	FileBIN() {};
	~FileBIN() {};

	void writeInFile(Person, char*);// запись в файл результата игрока
	void overwriteInformation(Person&, char*, int); //перезапись информации об игроке после совершенной им игры
	static int getLines(char*); //определение количества зарегестрированных игроков
	Person readFile(char*, int); //чтение из файла информации об игроке

};
