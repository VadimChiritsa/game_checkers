#pragma once
#include "Person.h"

class FileBIN{
public:
	FileBIN() {};
	~FileBIN() {};

	void writeInFile(Person, char*);// ������ � ���� ���������� ������
	void overwriteInformation(Person&, char*, int); //���������� ���������� �� ������ ����� ����������� �� ����
	static int getLines(char*); //����������� ���������� ������������������ �������
	Person readFile(char*, int); //������ �� ����� ���������� �� ������

};
