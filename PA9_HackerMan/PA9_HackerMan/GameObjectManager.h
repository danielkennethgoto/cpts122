/*******************************************************************************************
Programmer: Reid Reininger (charles.reininger@wsu.edu)
Class: CptS 122, Fall  2017; Lab Section 11
Programming Assignment: PA9_Hacker_Man
Date Started: November 27, 2017
Last Update: November 27, 2017

file: GameObjectManager.h

Description: container to manage all of the programs GameObjects; sends objects draw and
			 delete messages

			 inspired by "Game From Scratch C++ and SFML Edition!" tutorial at
			 http://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition.aspx

status: functional
*******************************************************************************************/
#pragma once
#include "GameObject.h"

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);
	GameObject* get(std::string name) const;
	int getObjectCount() const;

	void drawAll(sf::RenderWindow &window);
	void updateAll(sf::Event &event);
private:
	std::map<std::string, GameObject*> gameObjects;
	sf::Clock mTimeSinceLastUpdate;

	struct GameObjectDeallocator //helper functor for destructor
	{
		void operator()(const std::pair<std::string, GameObject*> &pair) const
		{
			delete pair.second;
		}
	};
};