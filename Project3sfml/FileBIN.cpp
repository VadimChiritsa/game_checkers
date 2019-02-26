#include "FileBIN.h"

void FileBIN::writeInFile(Person person, char* fileName)
{
		person.writeBIN(fileName);	
}

int FileBIN::getLines(char* fileName) 
{
	ifstream file(fileName, ios::binary | ios::in);
	
	int size;
	int line = 0;
	while (!file.eof())
	{
		if (file.eof() && line == 0)
		{
			file.close();
			return -1;
		}
		char *s = new char[20];
		
		file.read(reinterpret_cast<char*>(s), 20 * sizeof(char));
		delete s;
		file.read(reinterpret_cast<char*>(&size), sizeof(int));
		file.read(reinterpret_cast<char*>(&size), sizeof(int));
		file.read(reinterpret_cast<char*>(&size), sizeof(int));
		line++;
	}
	file.close();
	line -= 1;
	return line;
}

Person FileBIN::readFile(char* fileName, int pos)
{
		return Person::readBIN(fileName, pos);	
}

void FileBIN::overwriteInformation(Person& person, char* fileName, int line)
{
	fstream file(fileName, ios::binary | ios::in | ios::out);
	file.seekp(line*sizeof(Person));

	if (!file.eof())
	{
		int i1 = person.getWin(),i2 = person.getStandoff(), i3=person.getDefeat();
		file.write(reinterpret_cast<char*>(person.getName()), 20 * sizeof(char));
		file.write(reinterpret_cast<char*>(&i1), sizeof(int));
		file.write(reinterpret_cast<char*>(&i2), sizeof(int));
		file.write(reinterpret_cast<char*>(&i3), sizeof(int));
		file.close();
	}
}



