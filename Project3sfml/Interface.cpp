#include "Interface.h"

void Interface::vibor(int **ms, int k)
{
	int i, i1, j, m, t;
	for (i = 0; i < k - 1; i++)
	{
		i1 = i;
		t = ms[1][i];
		for (j = i + 1; j<k; j++)
		{
			if (ms[1][j]>t)
			{
				t = ms[1][j];
				i1 = j;
			}
		}
		if (i1 != i)
		{
			m = ms[1][i];
			ms[1][i] = t;
			ms[1][i1] = m;

			m = ms[0][i];
			ms[0][i] = ms[0][i1];
			ms[0][i1] = m;

		}
	}
}

char* Interface::itoa(int val)
{
	if (val == 0) {
		char* result = new char[2];
		result[0] = '0';
		result[1] = '\0';
		return result;
	}

	int i = 1, power = 1;
	while (val / power != 0)
	{
		i++;
		power *= 10;
	}
	char* result = new char[i + 1];
	i = 0;
	while (power >= 10)
	{
		power /= 10;
		result[i] = (val / power) % 10 + '0';
		i++;
	}
	result[i] = '\0';
	return result;
}

void Interface::ChoiceColor(RenderWindow& window, Person& person, int number)
{

	window.setFramerateLimit(10);

	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);

	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Text text("Выберите цвет:", font, 50);
	text.setStyle(sf::Text::Bold);
	text.setPosition(220, 50);

	Text text1("Белые", font, 50);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(270, 100);

	Text text2("Чёрные", font, 50);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(270, 150);
	FileBIN bin;
	bool isMenu = true;
	int menuNum = 0;
	Event event;
	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {

		menuNum = 0;

		text1.setFillColor(Color::White);
		text2.setFillColor(Color::White);


		if (IntRect(270, 100, 140, 50).contains(Mouse::getPosition(window))) { text1.setFillColor(Color::Blue); menuNum = 1; }
		if (IntRect(270, 150, 140, 50).contains(Mouse::getPosition(window))) { text2.setFillColor(Color::Blue); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (menuNum == 1) {

				Game(window, person, number, false);
				window.create(VideoMode(700, 400), "Menu");
				bin.overwriteInformation(person, "Stata", number);
			}
			if (menuNum == 2) {
				Game(window, person, number, true);
				window.create(VideoMode(700, 400), "Menu");
				bin.overwriteInformation(person, "Stata", number);
			}

		}

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
				exit(1);
			}
		}

		window.draw(fon1);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}

}

void Interface::inputName(RenderWindow& window)
{

	string str;
	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);

	Font font;
	font.loadFromFile("CyrilicOld.TTF");
	Text text("Введите имя игрока:", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setPosition(150, 100);

	Text txt;
	txt.setFont(font);
	txt.setCharacterSize(40);
	txt.setFillColor(Color::Green);
	txt.setPosition(150, 150);


	Event event;
	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {


		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				exit(1);
			}
		}

		if (event.type == sf::Event::TextEntered)
		{

			if ((event.text.unicode < 123 && event.text.unicode>96) || (event.text.unicode>47 && event.text.unicode<58) || (event.text.unicode>64 && event.text.unicode<91) || event.text.unicode == 8 || event.text.unicode == 13)
			{
				char c;
				c = static_cast<char>(event.text.unicode);

				if (event.text.unicode == 13) {
					FileBIN bin;
					char* s = new char[20];
					int i = 0;
					while (i<str.size())
						s[i++] = str[i];
					s[i] = '\0';
					Person person(s);
					bin.writeInFile(person, "Stata");
					delete s;
					ChoiceColor(window, person, FileBIN::getLines("Stata") - 1);
					
					break;
				}

				if (event.text.unicode == 8)
					str.erase(str.size() - 1, 1);

				if (event.text.unicode != 8 && str.size() < 19)
					str += c;
				txt.setString(str);
			}
		}


		window.draw(fon1);
		window.draw(text);
		window.draw(txt);
		window.display();
	}


}

void Interface::StatisticPlayer(RenderWindow& window)
{
	window.setFramerateLimit(10);
	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);
	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Person person;
	FileBIN bin;
	int size = bin.getLines("Stata");
	int** ms = new int*[2];
	for (int i = 0; i < 2; i++)
		ms[i] = new int[size];
	int k;
	for (int i = 0; i < size; i++) {
		ms[0][i] = i;
		person = bin.readFile("Stata", i);
		ms[1][i] = person.getWin() * 2 + person.getStandoff() - person.getDefeat() * 2;
		k = ms[1][i];

	}

	vibor(ms, size);

	Text* text = new Text[size];
	Text* textWin = new Text[size];
	Text* textStandoff = new Text[size];
	Text* textDefeat = new Text[size];

	Text txt;
	txt.setFont(font);
	txt.setCharacterSize(30);
	txt.setFillColor(Color::Blue);
	txt.setString("Имя:                       Победы:  Ничьи:  Поражения:");
	txt.setPosition(0, 0);

	for (int i = 0; i < size; i++) {

		person = bin.readFile("Stata", ms[0][i]);
		int vvv = ms[0][i];
		text[i].setFont(font);
		text[i].setCharacterSize(20);
		text[i].setFillColor(Color::Green);
		textWin[i].setFont(font);
		textWin[i].setCharacterSize(20);
		textStandoff[i].setFont(font);
		textStandoff[i].setCharacterSize(20);
		textDefeat[i].setFont(font);
		textDefeat[i].setCharacterSize(20);

		string s;
		string win;
		string standoff;
		string defeat;
		s = itoa(i + 1);
		s += ") ";
		s += person.getName();
		text[i].setString(s);
		text[i].setPosition(0, (i + 1) * 30);
		win += itoa(person.getWin());
		standoff += itoa(person.getStandoff());
		defeat += itoa(person.getDefeat());
		textWin[i].setString(win);
		textWin[i].setPosition(230, (i + 1) * 30);
		textStandoff[i].setString(standoff);
		textStandoff[i].setPosition(348, (i + 1) * 30);
		textDefeat[i].setString(defeat);
		textDefeat[i].setPosition(450, (i + 1) * 30);

	}
	Event event;

	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				exit(1);
			}
		}

		window.draw(fon1);
		window.draw(txt);
		for (int i = 0; i < size; i++) {
			window.draw(text[i]);
			window.draw(textWin[i]);
			window.draw(textStandoff[i]);
			window.draw(textDefeat[i]);
		}

		window.display();
	}

}

void Interface::Game(RenderWindow& window, Person& person, int number, bool color)
{
	window.create(VideoMode(64 * 8, 64 * 10 - 20), "Game", Style::Close);
	Texture t;
	Sprite s;
	Font font;
	font.loadFromFile("Quant Antiqua Bold Italic.Ttf");
	Text* text = new Text[5];
	for (int i = 0; i < 5; i++)
		text[i].setFont(font);
	text[0].setPosition(0, 520);
	text[0].setCharacterSize(40);
	text[0].setString("Белые:");
	text[0].setFillColor(Color::Black);

	text[1].setPosition(300, 520);
	text[1].setCharacterSize(40);
	text[1].setString("Чёрные:");
	text[1].setFillColor(Color::Black);

	text[2].setPosition(140, 520);
	text[2].setCharacterSize(40);
	text[2].setString("12");
	text[2].setFillColor(Color::Black);

	text[3].setPosition(467, 520);
	text[3].setCharacterSize(40);
	text[3].setString("12");
	text[3].setFillColor(Color::Black);

	text[4].setPosition(40, 570);
	text[4].setCharacterSize(35);
	text[4].setString("Согласиться на ничью");
	text[4].setFillColor(Color::Black);



	t.loadFromFile("50.jpg");
	s.setTexture(t);
	s.setPosition(0, 64 * 8);
	window.setFramerateLimit(10);
	int step, numLink = -1, WRITE = 12, BLACK = 12;
	ArtificialIntelligence AI;
	Checker _checker(color);
	Logic _logic;
	int coordinate = 0, choice = 0;
	int ms[2] = { 0, -1 };
	bool isMove = false, isMoveKing = false, checkMove = false, checkKingMove = false;
	Move move;
	FileBIN bin;
	if (color == false) step = 1;
	else step = 0;

	while (window.isOpen()) {
		text[4].setFillColor(Color::Black);
		numLink = -1;
		bool flag = false;
		Vector2i pos = sf::Mouse::getPosition(window);
		Event event;

		if (IntRect(40, 570, 410, 35).contains(Mouse::getPosition(window))) { text[4].setFillColor(Color::Green); numLink = 1; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (numLink == 1) {
				person.increaseStandoff();
				bin.overwriteInformation(person, "Stata", number);
				return;
			}
		}



		if (step % 2 == 0) {
			Sleep(1500);

			int z = AI.searchAlfaBeta(_checker, !color, 3, 0, move);
			int i = move.getOldPoz() / 8, j = move.getOldPoz() % 8, i1 = move.getNewPoz() / 8, j1 = move.getNewPoz() % 8;

			if (move.getNewPoz() == 0 && move.getOldPoz() == 0) {
				person.increaseWin();
				return;
			}

			if (move.getNewPoz() == move.getOldPoz()) {
				cout << "Oshibka" << endl;
				continue;
			}
			if (move.getFlag() == true) {
				AI.makeMoveKill(_checker, move, 0);
				if (!color)
					text[2].setString(itoa((color == true) ? --BLACK : --WRITE));
				else
					text[3].setString(itoa((color == true) ? --BLACK : --WRITE));
				if (!ArtificialIntelligence::needKill(_checker, move)) {
					move.null();
					step++;
				}
			}

			else {
				AI.makeMove(_checker, move, 0);
				move.null();
				step++;
			}

		}

		if (step % 2 == 1) {
			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) window.close();

				if (event.type == Event::MouseButtonPressed)

					if (_logic.needKill(_checker, color, ms)) {

						if (choice == 1) {
							if (_logic.moveKillKing(_checker, pos, color, ms)) {
								if (!color)
									text[3].setString(itoa((color == true) ? --WRITE : --BLACK));
								else
									text[2].setString(itoa((color == true) ? --WRITE : --BLACK));
							}
							choice = 0;
						}

						if (choice == 2) {
							if (_logic.moveKill(_checker, pos, ms, color)) {
								if (!color)
									text[3].setString(itoa((color == true) ? --WRITE : --BLACK));
								else
									text[2].setString(itoa((color == true) ? --WRITE : --BLACK));
							}
							choice = 0;
						}

						if (choice == 0)
							choice = _logic.choiceKill(_checker, pos, color);

						if (!_logic.needKill(_checker, color, ms)) {
							ms[0] = 0;
							ms[1] = -1;
							step++;
							break;
						}

					}

					else
					{

						for (int i = 0; i < 8; i++)
							for (int j = 0; j < 8; j++) {
								if (_checker.cell[i][j].getClean() && _checker.cell[i][j].getColor() == color) {
									if (_checker.cell[i][j].getKing()) {
										if (Logic::checkingBounds(i - 1, j - 1) && _checker.cell[i - 1][j - 1].getClean() == false)
											flag = true;
										if (Logic::checkingBounds(i - 1, j + 1) && _checker.cell[i - 1][j + 1].getClean() == false)
											flag = true;
										if (Logic::checkingBounds(i + 1, j - 1) && _checker.cell[i + 1][j - 1].getClean() == false)
											flag = true;
										if (Logic::checkingBounds(i + 1, j + 1) && _checker.cell[i + 1][j + 1].getClean() == false)
											flag = true;
										continue;

									}

									if (Logic::checkingBounds(i - 1, j - 1) && _checker.cell[i - 1][j - 1].getClean() == false)
										flag = true;
									if (Logic::checkingBounds(i - 1, j + 1) && _checker.cell[i - 1][j + 1].getClean() == false)
										flag = true;
								}

							}

						if (!flag) {
							person.increaseDefeat();
							return;

						}

						if (isMove) {
							checkMove = _logic.move(_checker, pos, color);
							isMove = false;
							_logic.resetBacklight(_checker);
							if (checkMove)
								step++;
							break;
						}
						if (isMoveKing) {
							checkKingMove = _logic.moveKing(_checker, pos, coordinate, color);
							isMoveKing = false;
							_logic.resetBacklight(_checker);
							if (checkKingMove)
								step++;
							break;
						}

						if (_checker.cell[pos.y / 64][pos.x / 64].getKing() && _checker.cell[pos.y / 64][pos.x / 64].getColor() == color) {
							coordinate = _logic.choiceKing(_checker, pos);
							isMoveKing = true;

						}
						if (_checker.cell[pos.y / 64][pos.x / 64].getClean() && _checker.cell[pos.y / 64][pos.x / 64].getColor() == color && !_checker.cell[pos.y / 64][pos.x / 64].getKing()) {
							_logic.choice(_checker, pos);
							isMove = true;
						}

					}
			}
		}

		window.clear();
		_checker.draw(window);
		window.draw(s);
		for (int i = 0; i < 5; i++)
			window.draw(text[i]);
		window.display();
	}

}

void Interface::choicePlayer(RenderWindow& window)
{
	window.setFramerateLimit(10);
	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);
	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Person person;
	FileBIN bin;
	int size = bin.getLines("Stata");

	Text text1("Игроков не найдено:", font, 40);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(150, 100);

	Text* text = new Text[size];

	for (int i = 0; i < size; i++) {
		person = bin.readFile("Stata", i);
		text[i].setFont(font);
		text[i].setCharacterSize(40);

		char* s = new char[25];
		strcpy(s, itoa(i + 1));
		strcat(s, ") ");
		strcat(s, person.getName());
		text[i].setString(s);
		text[i].setFillColor(Color::Green);
		text[i].setPosition(10, (i)* 40);

	}
	Event event;
	bool isMenu = true;
	int menuNum = -1;

	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {
		menuNum = -1;

		for (int i = 0; i < size; i++) {
			text[i].setFillColor(Color::White);
		}

		for (int i = 0; i < size; i++) {
			if (IntRect(10, (i)* 40, 200, 50).contains(Mouse::getPosition(window))) { text[i].setFillColor(Color::Green); menuNum = i; }
		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			for (int i = 0; i < size; i++) {
				if (menuNum == i) {
					person = bin.readFile("Stata", i);
					ChoiceColor(window, person, i);

				}
			}

		}

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
				exit(1);
			}
		}
		window.draw(fon1);
		if (size == 0)
			window.draw(text1);

		else {
			for (int i = 0; i < size; i++) {
				window.draw(text[i]);
			}
		}
		window.display();
	}

}

void Interface::menuGame(RenderWindow & window) {
	window.setFramerateLimit(10);
	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);

	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Text text("Новый игрок", font, 50);
	text.setStyle(sf::Text::Bold);
	text.setPosition(210, 100);

	Text text1("Выбрать игрока", font, 50);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(210, 150);

	int menuNum = 0;
	Event event;


	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {

		menuNum = 0;
		text.setFillColor(Color::White);
		text1.setFillColor(Color::White);


		if (IntRect(210, 100, 280, 50).contains(Mouse::getPosition(window))) { text.setFillColor(Color::Blue); menuNum = 1; }
		if (IntRect(210, 150, 350, 50).contains(Mouse::getPosition(window))) { text1.setFillColor(Color::Blue); menuNum = 2; }


		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (menuNum == 1) { inputName(window); }
			if (menuNum == 2) { choicePlayer(window); }

		}

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
				exit(1);
			}
		}

		window.draw(fon1);
		window.draw(text);
		window.draw(text1);
		window.display();
	}
}

void Interface::menu(RenderWindow & window) {
	window.setFramerateLimit(10);
	
	// Load a music to play
	sf::Music music;
	music.openFromFile("1234.ogg");
	// Play the music
	music.play();
	music.setLoop(true);
	Texture fon;
	Sprite fon1;
	fon.loadFromFile("190701.jpg");
	fon1.setTexture(fon);

	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Text text("Играть", font, 50);
	text.setStyle(sf::Text::Bold);
	text.setPosition(270, 50);

	Text text1("Статистика игроков", font, 50);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(110, 100);

	Text text2("Выход", font, 50);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(270, 200);

	Text text3("Вкл./Откл. музыку", font, 50);
	text3.setStyle(sf::Text::Bold);
	text3.setPosition(123, 150);

	bool isMenu = true;
	int menuNum = 0;
	Event event;
	while (window.isOpen())
	{

		menuNum = 0;
		text.setFillColor(Color::White);
		text1.setFillColor(Color::White);
		text2.setFillColor(Color::White);
		text3.setFillColor(Color::White);

		if (IntRect(270, 50, 165, 50).contains(Mouse::getPosition(window))) { text.setFillColor(Color::Blue); menuNum = 1; }
		if (IntRect(110, 100, 460, 50).contains(Mouse::getPosition(window))) { text1.setFillColor(Color::Blue); menuNum = 2; }
		if (IntRect(270, 200, 140, 50).contains(Mouse::getPosition(window))) { text2.setFillColor(Color::Blue); menuNum = 3; }
		if (IntRect(123, 150, 440, 50).contains(Mouse::getPosition(window))) { text3.setFillColor(Color::Blue); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (menuNum == 1) { menuGame(window); }
			if (menuNum == 2) { StatisticPlayer(window); }
			if (menuNum == 3)
				exit(1);
			if (menuNum == 4) {
				if (music.getStatus())
					music.stop();
				else music.play();
			}
		}

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) window.close();

		}
		window.draw(fon1);
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}

}