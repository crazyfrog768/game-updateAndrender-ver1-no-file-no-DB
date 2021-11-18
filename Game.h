#pragma once

//declare ------------------
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
	// files var.
	std::ofstream scoreFile;

	// Variaables / windows
	sf::RenderWindow* window;
	sf::Event ev;

	// mouse positioins to window
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text uiText2;
	sf::String playerInput;
	sf::Text playerText1;
	sf::Text playerText2;
    std::string playerName;

	// screens type/number
	int screenNo;

	// game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// game obj
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// functions 
	void initTextbox();
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();

public:
	//constructors / destructors
	Game();
	virtual ~Game();

	// accessors
	const bool running() const;
	const bool getEndGame() const;
	bool setEndgame(bool);

	//functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateText();
	void updateTeeText(int screenNo);
	int getScreenNO();
	void setScreenNo(int screenno);

	// **********  Game updatePage1 ************
	void updatePage1() 	{
		this->updateMousePositions();
		this->updateTeeText(1);
	}
	// **********  Game updatePage2 ************
	void updatePage2() {
		this->pollEvents();
		this->updateMousePositions();
		this->updateTeeText(2);
	}
		// **********  Game updatePage3 ************
	void updatePage3() 	{
		this->pollEvents();

		if (this->endGame == false && screenNo == 3) {
			this->updateMousePositions();
			this->updateTeeText(screenNo);
			this->updateEnemies();
		}
 
		// end frame condition  **-
		if (this->health <= -1) {
			this->endGame = true;

		}
	}

	// **********  Game updatePage4 ************
	void updatePage4() {
		//	this->pollEvents();
		// this->updateMousePositions();
		this->updateTeeText(4);
	}


	// **********  Game render  screen **********
	void renderText(sf::RenderTarget& target, float x, float y, int size, sf::Color color);
	void renderEnemies(sf::RenderTarget& target);
	void renderPage1();
	void renderPage2();
	void renderPage3();
	void renderPage4();

};

