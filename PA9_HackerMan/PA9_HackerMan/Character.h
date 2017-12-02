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
#pragma once
#include "GameObject.h"

class Character : public GameObject {
public:
	Character();
	~Character() = default;

	void update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects);

private:
	//kinematic variables
	bool jump;
	float freeFallTime;
	float velocityX;
	float velocityY;
	float velocityY0; //vertical velocity before free fall
	float deltaY;
	float deltaX;

	//kinematic constants
	const float maxVelocityX = 300;	
	const float acceleration = 50; //acceleration due to gravity
	const float jumpVelocity = -20;		
	
	//update functions
	void updateInput(sf::Event event);
	void updateFreeFallTime(float timeLastUpdate);
	void updateYKinematics(float timeLastUpdate);
	void updateXKinematics(float timeLastUpdate);

	//collision functions
	void checkCollisionGround();
	void checkCollisionPlatform(map<string, pair<string, GameObject*>>);
};