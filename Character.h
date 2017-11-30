#pragma once
#include "GameObject.h"

class Character : public GameObject {
public:
	Character();
	~Character() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects);

private:
	float timeSinceJumpStart;
	bool isJumping;
	float velocityY;
	const float jumpVelocity = -20;
	const float acceleration = 50;

	float velocityX;
	const float maxVelocityX = 300;
};