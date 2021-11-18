// git : 18/11/2021  
#include "Game.h"
#include <cstdlib>

// **********  init Fonts  ************
void Game::initFonts() {
	if (this->font.loadFromFile("Dosis-Light.ttf") == false)
		std::cout << "Error font not found " << " \n";
}

// **********  init Variables ************
void Game::initVariables()   {
	this->window = nullptr;

	this->playerName = "";
	this->playerText1.setFont(font);
	this->playerText2.setFont(font);
	this->playerText1.setString("Please enter your name: ");
	this->playerText2.setString("");
	this->playerText1.setStyle(sf::Text::Bold);
	this->playerText2.setStyle(sf::Text::Bold);
	this->playerInput = "";
	this->screenNo = 1;
	this->points = 0;
	this->health = 10;
	this->endGame = false;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

// **********  init Window  ************
void Game::initWindow()   {
	//sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2 - 480));
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "GAME 1", sf::Style::Titlebar | sf::Style::Default);
	this->window->setFramerateLimit(60);
	//this->window->setPosition(centerWindow);
	this->window->setKeyRepeatEnabled(true);
}

// **********  init Enemies  ************
void Game::initEnemies()   {
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	//this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}



// **********  init Text  ************
void Game::initText()  {
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color(255, 255, 255, 255));
	this->uiText.setString("NONE");

	this->uiText2.setFont(this->font);
	this->uiText2.setCharacterSize(32);
	this->uiText2.setFillColor(sf::Color(255, 0, 0, 200));
	this->uiText2.setString("NONE");
}

// **********  Game Constructor ************
Game::Game() {
	this->initFonts();
	this->initVariables();
	this->initWindow();
	this->initText();
	this->initEnemies();
}
// **********  Game Destructor ************
Game::~Game() {
	delete this->window;
}
// **********  Game running ***********
const bool Game::running() const {
	return this->window->isOpen();
}
// **********  Game End  ************
const bool Game::getEndGame() const {
	return this->endGame;
}

bool Game::setEndgame(bool ToF)
{
	return ToF;
}

// **********  Spawning Enemy ************
void Game::spawnEnemy()
{
	// spawns enemies and sets their types and colors && apawn positions randomely
	// set random type (diff)
	// set a random positions
	// set a random color 
	// adds enemy to the vector
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

	// randomize enemy types
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case  4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;

	}

	//spawn enemy
	this->enemies.push_back(this->enemy);
}


// **********  Game:: mouse position **********
void Game::updateMousePositions()
{
	// update mouse position rel. to window  (vector2i)
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
// **********  Game:: update Enemies *********
void Game::updateEnemies()  {
	// updating spawn timer & spawn enemies 
	// when total time amount o fenemies is small than the max.
	// move the enemies downwards
	// removes the enemies at the edge of the screen
	if (static_cast<int>(this->enemies.size()) < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// moving and updating enemies and checking if they are below the screen
	for (int i = 0; i < static_cast<int>(this->enemies.size()); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.5f);
		//check if the enemies are below the screen (window bottom)
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << " \n";
		}
	}
	// check if clicked upon

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					// game points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;

					std::cout << "Points: " << this->points << " \n";
				}
			}

		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

// **********  update TEE Text ************
void Game::updateTeeText(int myScreenNo) {
	std::stringstream ss;

	switch (myScreenNo) {
	case 1:
		ss << "Welcome to Sorawit Easy Game ... \n" << "A programming C++ game\n\n"
			<< "tasks: \n"
			<< "1) keyboard & mouse controls \n"
			<< "2) using srand() Randomize on enemies, positions and color\n"
			<< "3) C++ on Visual Studio tool \n"
			<< "4) sfml framework / lib. \n"
			<< "5) version 1.0 \n\n"
			<< "this screen will delay for 5 seconds \n";
		break;
	case 2:
		ss << "TOP 5 player scores " << "\n\n"
			<< "Now you are ready to play... ";
		break;
	case 3:
		ss << "Points: " << this->points << "\n"
			<< "Life: " << this->health << "\n"
			<< "Player: " << playerName << "\n";
		break;
	case 4:
		ss << "Thank you for playing my game \n" << "A programming C++ game\n\n"
			<< "tasks: \n"
			<< "This program is part of Computer Engineering Class\n"
			<< "King Mongkut's Institute of Technology Ladkrabang\n\n"
			<< "Date: 25/11/2021 \n"
			<< "Class: ................... \n"
			<< "Instructor: ................... \n\n"
			<< "Written in C++ & SFML library Suite 2.5.1 (running x86 mode)\n"
			<< "SEE YOU ALL NEXT TIME  ;-)\n";
		break;
	}

	this->uiText.setString(ss.str());
}
int Game::getScreenNO()
{
	return screenNo;
}
void Game::setScreenNo(int screenno)
{
	this->screenNo = screenno;
}
// **********  Game update Text at the corner ************
void Game::updateText()  {
	std::stringstream ss;
	ss << "Points: " << this->points << "\n" << "Life: " << this->health << "\n";
	this->uiText.setString(ss.str());
}

// ---------- RENDERING PART FUNCTIONS ----
// **********  Game render Text ************
void Game::renderText(sf::RenderTarget& target, float x, float y, int size, sf::Color color)  {
	this->uiText.setCharacterSize(size);
	this->uiText.setFillColor(color);
	this->uiText.setPosition(sf::Vector2f(x, y));

	target.draw(this->uiText);
}

// **********  Game render enemies ************
void Game::renderEnemies(sf::RenderTarget& target)   {
	// rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

// **********  Game::Poll Event trap ************
void Game::pollEvents()  {
	//Event polling
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			//case sf::Event::KeyPressed:
			//	if (this->ev.key.code == sf::Keyboard::Escape)
			//		this->window->close();
		
		}
	}
}

int mycount = 0;
/* render game objects
	- clear old frames
	- render obj.
	- display frames in window
*/
// **********  Game renderPage1   ***********
void Game::renderPage1() {
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderText(*this->window, 100,100, 24, sf::Color::Yellow);
	this->window->display();
	std::cout << "SCREEN when exiting renderPage() " << screenNo << "\n\n";
}

// **********  Game renderPage2   ***********
void Game::renderPage2() {
	bool mouseClick = false;

	//playerText.setColor(sf::Color(219,0,0));
	playerText1.setPosition(100, 200);
	playerText2.setPosition(400, 200);

	//std::cout << "be while loop   \n"; 

	while (this->window->isOpen() && (ev.text.unicode != 13))  {
		while (this->window->pollEvent(this->ev) )  {
			if (ev.type == sf::Event::TextEntered)
			{
				playerName = "";
				if ((ev.text.unicode < 128) && (ev.text.unicode != 13))
				{
					playerInput += ev.text.unicode;
					playerText2.setString(playerInput);
					playerName = playerText2.getString();
					std::cout << "IF.key entered: " << ev.text.unicode << ", Text:" << playerName << "\n";
				}
				else if (ev.text.unicode == 13) {
					playerName = playerText2.getString();
					std::cout << "ELSE.key entered: " << ev.text.unicode << ", Text:" << playerName << "\n";
					//playerText2.setString(playerInput);
				}
			}

		}
		this->window->clear();
		this->renderText(*this->window, 50, 50, 25, sf::Color(255, 255, 255, 255));
		this->window->draw(playerText1);
		this->window->draw(playerText2);
		this->window->display();
	}

	std::cout << "SCREEN when exiting renderPage() " << screenNo 
		<< "\n\n  Player Name: " << playerName << "\n";

	this->uiText.setPosition(100, 500);
	this->uiText.setString("Click me to START GAME");
	this->window->draw(this->uiText);
	this->window->display();
	while (this->window->isOpen() && mouseClick == false) {
		while (this->window->pollEvent(this->ev)) {
			switch (this->ev.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "mouse click is pressed !!! \n\n\n";
				mouseClick = true;
				break;
			default:
				break;
			}
		}
	}
	std::cout << "goto PLAY GAME !!! \n"; 
}

// **********  Game renderPage3   ***********
void Game::renderPage3()  {
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderEnemies(*this->window);
	this->renderText(*this->window, 0, 0, 20, sf::Color(255, 255, 255, 255));
	this->window->display();
	std::cout << "SCREEN when exiting renderPage() " << screenNo << "\n\n";
}

// **********  Game renderPage4   ***********
void Game::renderPage4() {
	std::stringstream ss2;

	this->window->clear(sf::Color(0, 0, 0, 255));

	ss2 << "Player: " << playerName << " has score of: " << points;
	this->uiText2.setStyle(sf::Text::Bold);
	this->uiText2.setString(ss2.str());
	this->uiText2.setPosition(400, 20);
	this->window->draw(this->uiText2);
	
	this->renderText(*this->window, 100, 100, 24, sf::Color::Cyan);

	this->window->display();
	
	std::cout << "SCREEN when exiting renderPage() " << screenNo << "\n\n";
}
