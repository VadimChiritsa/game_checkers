#include "TextureAndBoard.h"

TextureAndBoard::TextureAndBoard() {
	boardT.loadFromFile("brown.bmp");
	boardS.setTexture(boardT);
	//int board[8][8]	
}

void TextureAndBoard::draw(RenderWindow &window)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {

			boardS.setTextureRect(sf::IntRect(0, ((i + j) % 2 == 0) ? 1 * size : 2 * size, size, size));
			boardS.setPosition(i * size, j * size);
			window.draw(boardS);
		}
}
