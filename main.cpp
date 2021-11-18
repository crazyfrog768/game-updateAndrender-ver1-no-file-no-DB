#include "Game.h"	
#include <windows.h>

//using namespace sf;
int pageUpdate = 3, pageRender = 3;
int ii = 0;

int main()
{
	int sleepTime = 3000;

	//init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// init game objects
	Game game;

	pageUpdate = game.getScreenNO();
	pageRender = game.getScreenNO();

	//Game loop
	while (game.running() && !game.getEndGame())
	{
		// Update
		switch (pageUpdate) {
		case 1:
			game.updatePage1();			// welcome
			break;
		case 2:
			game.updatePage2();         // enter player name
			break;
		case 3:
			game.updatePage3();         // play the game 
			break;
		}
		std::cout << "EXIT updatePage: " << pageUpdate 
			<< " >>> ii: " << ii++ <<  "\n";

		// Render
		switch (pageUpdate) {
		case 1:
			game.renderPage1();
			Sleep(sleepTime);
			break;
		case 2:
			game.renderPage2();
			//Sleep(sleepTime);
			break;
		case 3:
			game.renderPage3();
			break;
		}
		std::cout << "Exit renderPage: " << pageUpdate
			<< " >>> ii: " << ii++ << "\n" << "*************************************\n";
		if (!game.getEndGame() && pageUpdate != 3 ) {
			pageUpdate++;
			game.setScreenNo(pageUpdate);
		}
		std::cout << "setScrrenNo  is => " <<  pageUpdate << "\n" << "--------------------\n";
	}

	pageUpdate = 4;;
	game.setScreenNo(pageUpdate);
	game.updatePage4();         // say good bye and thanks 
	game.renderPage4();
	Sleep(sleepTime);

	// end of app
	std::cout << "END ....      app \n";
	system("pause > NULL");

	return 0;
}
