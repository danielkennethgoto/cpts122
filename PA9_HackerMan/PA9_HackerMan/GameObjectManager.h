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
using std::string;
using std::map;
using std::pair;

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();

	void add(string name, string type, GameObject* gameObject);
	void remove(string name);
	GameObject* get(string name) const;
	int getObjectCount() const;

	void drawAll(sf::RenderWindow &window);
	void updateAll(sf::Event &event);
private:
	std::map<string, pair<string, GameObject*>> gameObjects;
	sf::Clock mTimeSinceLastUpdate;

	struct GameObjectDeallocator //helper functor for destructor
	{
		void operator()(const pair<string, pair<string, GameObject*>> &pair) const
		{
			delete pair.second.second;
		}
	};
};