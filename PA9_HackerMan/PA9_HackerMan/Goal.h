#pragma once
#include "GameObject.h"

class Goal : public GameObject {

public:
	Goal();
	~Goal() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);

	bool checkGoalReached();

private:
	int heightScale = 1;
	int widthScale = 1;

	void Goal::checkCollisionCharacter(map<string, pair<string, GameObject*>> gameObjects);

	bool goalReached = false;
};

