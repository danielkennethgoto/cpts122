#pragma once
#include "GameObject.h"

class Character : public GameObject {
public:
	Character();
	~Character() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects);

private:
	//float timeSinceJumpStart;
	bool jump;
	//bool isJumping;
	//float velocityY;
	//float deltaY;
	//const float jumpVelocity = -20;
	//const float acceleration = 50;

	float velocityX;
	const float maxVelocityX = 300;

	//new system
	const float g = 50; //acceleration due to gravity
	float vy0; //vertical velocity before free fall
	float vy;
	float deltaY;
	float freeFallTime;

	const float jumpVelocity = -20;
};