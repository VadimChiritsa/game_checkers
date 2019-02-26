#pragma once
#include "Checker.h"

class Light{
public:	

	/*
	����������� �������� ��� ����� ����� ����� �� ��,
	������ �� ��� ��� ����, � ���� ������, ����������� �������� ������ ��� ������,
	����������� � ������� �������� �� ��������� ��� ���� �����
	*/
	 bool checkUR(Checker&, int, int, bool);
	 bool checkUL(Checker&, int, int, bool); 
	 bool checkDR(Checker&, int, int, bool); 
	 bool checkDL(Checker&, int, int, bool); 

	/*
	� ��� ������, ���� ����� �� ������ ����, �� �� ������ ���������� ��� ��������� �������� ������,
	����������� �� ������� ������
	*/

	 void lightUR(Checker&, int, int);
	 void lightUL(Checker&, int, int);
	 void lightDR(Checker&, int, int);
	 void lightDL(Checker&, int, int);
};

