#pragma once
#include "GameObject.h"

/*******************************************************************************************
Programmer: Reid Reininger (charles.reininger@wsu.edu)
Class: CptS 122, Fall  2017; Lab Section 11
Programming Assignment:
Date Started: November 1, 2017
Last Update: November 2, 2017
file: Character.h
Description: character class
status: functional
known bugs: checkCollisionPlatform(): presing space and move key when top of character same
height as a platform and right next to the platform
*******************************************************************************************/

class Character : public GameObject {
public:
	Character();
	~Character() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);
	bool checkHealth();
	void Character::drawMessage(sf::RenderWindow &window);

private:
	//Attributes
	int healthPoints = 2; //Number of times that can get hit

	//kinematic variables
	void updateSprite(void);
	bool jump;
	float freeFallTime;
	float velocityX;
	float velocityY;
	float velocityY0; //vertical velocity before free fall
	float deltaY;
	float deltaX;
	float lastdeltaX;

	//kinematic constants
	const float maxVelocityX = 300;
	const float acceleration = 50; //acceleration due to gravity
	const float jumpVelocity = -20;

	//update functions
	void updateInput(sf::Event event);
	void updateFreeFallTime(float timeLastUpdate);
	void updateYKinematics(float timeLastUpdate);
	void updateXKinematics(float timeLastUpdate);


	string currentSprite;
	bool ismoving;
	//collision functions
	void checkCollisionGround();
	void checkCollisionPlatform(map<string, pair<string, GameObject*>> gameObjects);
	void checkCollisionDanger(map<string, pair<string, GameObject*>> gameObjects);
	void checkCollisionWall(map<string, pair<string, GameObject*>> gameObjects);
	void checkCollisionGoal(map<string, pair<string, GameObject*>> gameObjects);

};


/////////////////////////////Notes//////////////////////////////
//The "Game Over" part is buggy