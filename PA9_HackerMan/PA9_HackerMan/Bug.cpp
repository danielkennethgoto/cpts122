#pragma once
#include "Bug.h"
#include "GameEngine.h"
#include <stdlib.h>
#include <time.h>

/*************************************************************
Function: Bug() -> Constructor
Date Created: December 2nd, 2017
Date Last Modified:
Description:
status: Untested
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
Bug::Bug() :
	GameObject::GameObject("Bug.png"),
	velocityX{ float(-1 * (rand() % 100 - 50)) }
{
	load("Bug.png");
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2); //May need to modify?
	getSprite().setScale(2, 2);

	getSprite().setScale(.5, .5);

}

/*************************************************************
Function: moveBug()
Date Created: December 2nd, 2017
Date Last Modified:
Description: Generates a speed and direction to move the bug in
status: Untested
Input parameters: Time since last updated
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Bug::moveBug(float timeLastUpdate)
{
	int tempSpeed = 0;
	int direction = -1; //0 for left, 1 for right
	srand(time(NULL)); //initialize random seed

	direction = rand() % 2;
	tempSpeed = rand() % 100 + 50; //Randomly sets the speed between 100 and 299;

	if (direction == 0)
	{
		tempSpeed = tempSpeed * (-1);
	}

	velocityX = tempSpeed;
}


/*************************************************************
Function: updatePosition()
Date Created: December 2nd, 2017
Date Last Modified:
Description: Moves the sprite based on velocity, will be called by update()
status: Untested
Input parameters: Time since last updated
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Bug::updatePosition(float timeLastUpdate)
{
	float deltaX;
	deltaX = velocityX * timeLastUpdate;
	getSprite().move(deltaX, 0);
}

void Bug::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects)
{
	
	moveBug(timeLastUpdate);
	updatePosition(timeLastUpdate); //Change the sprites position
	checkCollisionWall(gameObjects);
}



/*************************************************************
Function: check for collision with wall
Date Created: December 2nd, 2017
Date Last Modified:
Description: Checks whether the bug collided with the wall
status: Untested
Input parameters: Time since last updated
Returns: True if collided, false if not
Preconditions:
Postconditions:
*************************************************************/
void Bug::checkCollisionWall(map<string, pair<string, GameObject*>> gameObjects)
{
	GameObject* wall = nullptr;
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if ("wall" == itr->second.first)
		{
			wall = itr->second.second;

			if (getBoundingRect().intersects(wall->getBoundingRect())) //Wall and bug collide
			{

					if (velocityX > 0 && getPosition().x < wall->getPosition().x)
					{
						setPosition(wall->getPosition().x - wall->getWidth() / 2 - getWidth() / 2, getPosition().y);
					}
					if (velocityX < 0 && getPosition().x > wall->getPosition().x)
					{
						setPosition(wall->getPosition().x + wall->getWidth() / 2 + getWidth() / 2, getPosition().y);
					}
			}
		}
		itr++;
	}
		
}

