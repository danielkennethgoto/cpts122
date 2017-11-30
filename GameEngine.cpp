#include "GameEngine.h"

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
	: gameState {GameState::UNINITIALIZED}
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
	window.setFramerateLimit(60);
	//allocate objects


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
		gameObjectManager.updateAll(event);
		gameObjectManager.drawAll(window);
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



