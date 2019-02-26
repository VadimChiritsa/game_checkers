#include "Checker.h"


Checker::Checker(bool color) : Cell() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++){
			if (board[i][j] == 0){
				cell[i][j].setClean(false);
				continue;
			}
			cell[i][j].setClean(true);
			if (color == false) {
				if (board[i][j] == 1) cell[i][j].setColor(true);

				if (board[i][j] == 2) cell[i][j].setColor(false);
			}
			if(color==true){
				if (board[i][j] == 2) cell[i][j].setColor(true);

				if (board[i][j] == 1) cell[i][j].setColor(false);
			}
		}
}

void Checker:: draw(RenderWindow &window) {
	TextureAndBoard::draw(window);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++){
			if (cell[i][j].getClean() == false && cell[i][j].getBacklight() == false) continue;
				
			if (cell[i][j].getColor() == true && cell[i][j].getKing() == false){
				cell[i][j].boardS.setTextureRect(IntRect(size * 3, size, size, size));
				cell[i][j].boardS.setPosition(j * size , i * size );
			}

			if (cell[i][j].getColor() == true && cell[i][j].getKing() == true) {
				cell[i][j].boardS.setTextureRect(IntRect(size * 4, size, size, size));
				cell[i][j].boardS.setPosition(j * size, i * size);
			}

			if (cell[i][j].getColor() == false && cell[i][j].getBacklight() == false){
				cell[i][j].boardS.setTextureRect(IntRect(size, size, size, size));
				cell[i][j].boardS.setPosition(j * size , i * size );
			}

			if(cell[i][j].getKing() && !cell[i][j].getColor()){
				cell[i][j].boardS.setTextureRect(IntRect(2*size, size, size, size));
				cell[i][j].boardS.setPosition(j * size, i * size);
			}

			if(cell[i][j].getClean()==false && cell[i][j].getBacklight() ){
				cell[i][j].boardS.setTextureRect(IntRect(size, 0, size, size));
				cell[i][j].boardS.setPosition(j * size, i * size);
			}

			window.draw(cell[i][j].boardS);

		}
}
