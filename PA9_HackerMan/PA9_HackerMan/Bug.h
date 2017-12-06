#pragma once
#include "GameObject.h"

class Bug : public GameObject {

public:
	Bug();
	~Bug() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);


private:
	//Variable
	float velocityX;

	//Static
	const float maxVelocityX = 300;

	////////////////////Functions/////////////////////////

	//Movement
	void moveBug(float timeLastUpdate); //The bug moves back and forth on its own
	void updatePosition(float timeLastUpdate);

	//Collision
	void checkCollisionWall(map<string, pair<string, GameObject*>> gameObjects);

	//////////////////////////////////////////////////////
};

//Game Engine Code -
//Bug* bug = new Bug;
//bug->setPosition(SCREEN_WIDTH * 1.5, GROUND - 50);
//gameObjectManager.add("bug1", "bug", bug);



///////////////////////////////NOTES////////////////////////////////////////////
//checkCollisionWall is untested
//Will likely add more features (eg jumping bug?)



