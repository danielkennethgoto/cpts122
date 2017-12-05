/*******************************************************************************************
Programmer: Reid Reininger (charles.reininger@wsu.edu)
Class: CptS 122, Fall  2017; Lab Section 11
Programming Assignment: PA9_HackerMan
Date Started: November 29, 2017
Last Update: November 29, 2017

file: gameEngine.h

Description: Runs the game. Does not include a main menu.

status: coding
*******************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjectManager.h"
#include <cassert>
#include "Character.h"
#include "Platform.h"
#include "GUI.h"

#define	SET_SCREEN_WIDTH 1024
#define SET_SCREEN_HEIGHT 768
#define SET_GROUND 548

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void startGame();

	static const int SCREEN_WIDTH = SET_SCREEN_WIDTH;
	static const int SCREEN_HEIGHT = SET_SCREEN_HEIGHT;
	static const int GROUND = SET_GROUND;

private:
	void gameLoop();
	bool isExiting() const;

	//not fully commited to these functions yet, have to collaborate with menu designer
	void showSplash();
	void showMainMenu();
	void pause();

	enum class GameState {
		UNINITIALIZED, SPLASH, MAIN_MENU, PAUSE, PLAYING, PAUSED, RESUMING, EXITING
	};

	GameState gameState;
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	GameObjectManager gameObjectManager;
	//PauseMenu; once it's built
	GUI* newGUI;
	sf::Sprite backgroundSprite;
	sf::Texture image;
};