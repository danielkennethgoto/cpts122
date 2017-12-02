#pragma once
#include "GameObject.h"

class Character : public GameObject {
public:
	Character();
	~Character() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects);

private:
	bool jump;

	float velocityX;
	float velocityY;
	float velocityY0; //vertical velocity before free fall
	float deltaY;
	float deltaX;

	const float maxVelocityX = 300;	
	const float acceleration = 50; //acceleration due to gravity
	const float jumpVelocity = -20;	
	
	float freeFallTime;
	
};