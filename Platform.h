#pragma once
#include "GameObject.h"

class Platform : public GameObject {
public:
	Platform();
	~Platform();

	void update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects);

private:


};