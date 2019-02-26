#include "Interface.h"


int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	RenderWindow window(VideoMode(700, 400), "Menu", Style::Close);
	Interface interFace;
	interFace.menu(window);
	return 0;
}
