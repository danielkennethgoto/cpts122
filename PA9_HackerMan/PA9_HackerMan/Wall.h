#pragma once
#include "GameObject.h"

class Wall : public GameObject {

public:
	Wall();
	~Wall() = default;

	void setAttributes(int newHeight, int newWidth, bool dangerous); //Configure the wall as needed, height and width are to scale
	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);

private:
	int heightScale = 1;
	int widthScale = 1;

	bool doesDamage; //if True touching the wall hurts

						   /////////////Private Functions//////////////
};

//////////////////////////////Notes////////////////////////////////
//Need a fireWall and a bitwall sprite 
//More features?