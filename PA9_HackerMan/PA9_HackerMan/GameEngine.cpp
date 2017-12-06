#include "GameEngine.h"
#include "NewCharacter.h"

/*************************************************************
Function: GameEngine() <<constructor>>
Date Created: November 29, 2017
Date Last Modified: Novemver 29, 2017

Description: sets gameState to UNINITIALIZED

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
GameEngine::GameEngine()
	: gameState{ GameState::UNINITIALIZED }
{

}

/*************************************************************
Function: ~GameEngine() <<destructor>>
Date Created: November 29, 2017
Date Last Modified: Novemver 29, 2017

Description: default

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
GameEngine::~GameEngine() {
	//do nothing
}

/*************************************************************
Function: ~GameEngine() <<destructor>>
Date Created: November 29, 2017
Date Last Modified: Novemver 29, 2017

Description: -public function that coordinates GameEngines
private functions to make the game run

-throws exeption if called more than once

status: coding

Input parameters:
Returns:
Preconditions: this function may only be called once
Postconditions:
*************************************************************/
void GameEngine::startGame() {
	if (GameState::UNINITIALIZED != gameState)
	{
		throw("startGame called more than once!");
	}

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Hacker Man!");
	//allocate objects
	NewCharacter* character = new NewCharacter;
	//NewCharacter* character2 = new NewCharacter;
	newGUI = new GUI;
	character->setPosition(character->getWidth() * 2, SCREEN_HEIGHT / 2);
	//character2->setPosition(character2->getWidth() * 2, SCREEN_HEIGHT / 2);
	gameObjectManager.add("player1", "character", character);
	//gameObjectManager.add("player2", "character", character2);
	Platform* platform = new Platform;
	platform->setPosition(SCREEN_WIDTH / 2, GROUND - 50);
	gameObjectManager.add("platform1", "platform", platform);

	platform = new Platform;
	platform->setPosition(gameObjectManager.get("platform1")->getPosition().x + 150, GROUND - 100);
	gameObjectManager.add("platform2", "platform", platform);
	image.loadFromFile("electronicBackground.png");
	backgroundSprite.setTexture(image);

	showMainMenu();

	gameState = GameState::PLAYING;

	while (!isExiting())
	{
		gameLoop();
	}
}

/*************************************************************
Function: gameLoop()
Date Created: November 29, 2017
Date Last Modified: Novemver 29, 2017

Description: main game loop

status: coding

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameEngine::gameLoop() {
	window.pollEvent(event);

	switch (gameState) {
	case GameState::PLAYING:
		window.clear();
		window.draw(backgroundSprite);
		gameObjectManager.updateAll(event);
		//set camera positions to main character
		if (gameObjectManager.get("player1") != nullptr)
		{
			if (gameObjectManager.get("player1")->getPosition().x > 175)
			{
				window.setView(sf::View(sf::Vector2f(gameObjectManager.get("player1")->getPosition().x + 350, window.getSize().y / 2), sf::Vector2f(window.getSize())));
			}
		}
		gameObjectManager.drawAll(window);
		newGUI->update(100, window, gameObjectManager.get("player1")->getPosition().x,0);
		window.display();
		break;
	}

	//if the close button is pushed
	if (sf::Event::Closed == event.type)
	{
		gameState = GameState::EXITING;
	}
}

/*************************************************************
Function: isExiting()
Date Created: November 29, 2017
Date Last Modified: Novemver 29, 2017

Description: returns true if gameState is EXITING

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
bool GameEngine::isExiting() const {
	return (GameState::EXITING == gameState) ? true : false;
}

/*************************************************************
Function: pause()
Date Created: December 5, 2017
Date Last Modified: December 5, 2017

Description: Displays the pauseMenu

status: INCOMPLETE!! DOES NOT PAUSE THE GAME YET

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameEngine::pause()
{
	PauseMenu pauseMenu(window);
	pauseMenu.selectOption(window);

}

/*************************************************************
Function: showMainMenu()
Date Created: December 5, 2017
Date Last Modified: December 5, 2017

Description: Displays the Main Menu

status: Complete

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameEngine::showMainMenu()
{
	Menu menu(window);
	menu.selectOption(window);
}