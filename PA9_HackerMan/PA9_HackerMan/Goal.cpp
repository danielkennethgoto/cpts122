#include "Goal.h"

/*************************************************************
Function: Wall() -> Constructor
Date Created: December 3, 2017
Date Last Modified:
Description: loads image file
status: untested
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
Goal::Goal() : GameObject::GameObject("goal.png")
{
	load("goal.png");
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	getSprite().setScale(1, 1);
}

/*************************************************************
Function: update()
Date Created: December 3, 2017
Date Last Modified:
Description:
status: untested
Input parameters:
Returns:
Preconditions: If it moves the wall should be tall
Postconditions:
*************************************************************/
void Goal::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects)
{
	checkCollisionCharacter(gameObjects);
}


//Return goalReached
bool Goal::checkGoalReached()
{
	return goalReached;
}


void Goal::checkCollisionCharacter(map<string, pair<string, GameObject*>> gameObjects)
{
	GameObject* Character = nullptr;
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if ("character" == itr->second.first)
		{
			Character = itr->second.second;

			if (getBoundingRect().intersects(Character->getBoundingRect())) //Wall and bug collide
			{
				goalReached = true;
			}
		}
		itr++;
	}
}

