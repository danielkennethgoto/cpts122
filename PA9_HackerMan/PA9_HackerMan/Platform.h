#pragma once
#include "GameObject.h"

class Platform : public GameObject {
public:
	Platform();
	~Platform();

	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);

private:


};