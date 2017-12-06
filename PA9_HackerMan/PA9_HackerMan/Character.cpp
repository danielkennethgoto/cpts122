#include "Character.h"
#include "GameEngine.h"
#include <windows.h> //For sleep



/*************************************************************
Function: Character() <<constructor>>
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description:
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
Character::Character()
	: GameObject::GameObject("stickman.png"),
	jump{ false },
	deltaY{ 0 },
	deltaX{ 0 },
	velocityX{ 0 },
	velocityY0{ 0 },
	velocityY{ 0 },
	freeFallTime{ 0 }

{
	load("stickman.png");
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	getSprite().setScale(2, 2);
}

/*************************************************************
Function: update()
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates the character sptite
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects) {
	updateInput(event);

	updateXKinematics(timeLastUpdate);
	updateYKinematics(timeLastUpdate);

	//update position
	getSprite().move(deltaX, deltaY);
	checkCollisionGround();
	checkCollisionPlatform(gameObjects);
	checkCollisionDanger(gameObjects);
	checkCollisionWall(gameObjects);
	checkHealth();
}

/*************************************************************
Function: updateInput()
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates the input from the event
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::updateInput(sf::Event event) {
	if (sf::Event::KeyPressed == event.type)
	{
		if (sf::Keyboard::Space == event.key.code)
		{
			jump = true;
		}
		if (sf::Keyboard::A == event.key.code)
		{
			velocityX = -1 * maxVelocityX;
		}

		if (sf::Keyboard::D == event.key.code)
		{
			velocityX = maxVelocityX;
		}
	}

	if (sf::Event::KeyReleased == event.type)
	{
		if (sf::Keyboard::Space == event.key.code)
		{
			jump = false;
		}
		if (sf::Keyboard::A == event.key.code && velocityX < 0)
		{
			velocityX = 0;
		}
		if (sf::Keyboard::D == event.key.code && velocityX > 0)
		{
			velocityX = 0;
		}
	}
}

/*************************************************************
Function: updateFreeFallTime()
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates time object has been in freefall
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::updateFreeFallTime(float timeLastUpdate) {
	freeFallTime += timeLastUpdate;
}

/*************************************************************
Function: updateYKinematics
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates velociy and displacement in the y direction
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::updateYKinematics(float timeLastUpdate) {
	if (jump && freeFallTime == 0)
	{
		velocityY0 = jumpVelocity;//should be a function setVelocityY0(jumpVelocity)
	}
	updateFreeFallTime(timeLastUpdate);
	deltaY = 5 * velocityY0 * freeFallTime + 5 * acceleration * freeFallTime * freeFallTime;
	velocityY = velocityY0 + acceleration * freeFallTime;
}

/*************************************************************
Function:  updateXKinematics
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates displacement in the x directions
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::updateXKinematics(float timeLastUpdate) {
	deltaX = velocityX * timeLastUpdate;
}

/*************************************************************
Function: checkCollisionGround()
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates character if collision with ground
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::checkCollisionGround() {
	if (getPosition().y > GameEngine::GROUND - getHeight() / 2 - 1)
	{
		setPosition(getPosition().x, GameEngine::GROUND - getHeight() / 2 - 1);
		freeFallTime = 0;
		velocityY0 = 0;
	}
}

/*************************************************************
Function: checkCollisionPlatform
Date Created: November 30, 2017
Date Last Modified: December 12, 2017
Description: updates charater if collision with platform
bugs: press space and move when next to platform that is same height
as character
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Character::checkCollisionPlatform(map<string, pair<string, GameObject*>> gameObjects) {
	GameObject* platform = nullptr;
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if ("platform" == itr->second.first)
		{
			platform = itr->second.second;
			if (getBoundingRect().intersects(platform->getBoundingRect()))
			{
				//land on platform
				if (getPosition().y + getHeight() / 2 <= platform->getBoundingRect().top + platform->getHeight()
					&& velocityY >= 0)
				{
					setPosition(getPosition().x, platform->getBoundingRect().top - getHeight() / 2);
					freeFallTime = 0;
					velocityY0 = 0;
				}
				//hit platfrom from underneath
				else if (getPosition().y - getHeight() / 2 >= platform->getBoundingRect().top
					&& velocityY <= 0)
				{
					setPosition(getPosition().x, platform->getBoundingRect().top + platform->getHeight() + getHeight() / 2);
					velocityY0 = 0;
				}
				else
				{
					if (velocityX > 0 && getPosition().x < platform->getPosition().x)
					{
						setPosition(platform->getPosition().x - platform->getWidth() / 2 - getWidth() / 2, getPosition().y);
					}
					if (velocityX < 0 && getPosition().x > platform->getPosition().x)
					{
						setPosition(platform->getPosition().x + platform->getWidth() / 2 + getWidth() / 2, getPosition().y);
					}
				}
			}
		}
		itr++;
	}
}


/*************************************************************
Function: checkCollisionBug
Date Created: December 4, 2017
Date Last Modified: 
Description: updates character if collision with bug
bugs: 
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
Notes: Should probably adjust the offset values
*************************************************************/
void Character::checkCollisionDanger(map<string, pair<string, GameObject*>> gameObjects)
{
	GameObject* bug = nullptr;
	GameObject* wall = nullptr;
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if ("bug" == itr->second.first)
		{
			bug = itr->second.second;
			if (getBoundingRect().intersects(bug->getBoundingRect()))
			{
			
				if (velocityX >= 0 && getPosition().x < bug->getPosition().x)
				{
					setPosition(bug->getPosition().x - (bug->getWidth()) / 2 - getWidth() / 2 - 100, getPosition().y);
				}
				if (velocityX <= 0 && getPosition().x > bug->getPosition().x)
				{
					setPosition(bug->getPosition().x + (bug->getWidth()) / 2 + getWidth() / 2 + 100, getPosition().y + 500);
				}
				this->healthPoints--;
			}
		}

		if ("firewall" == itr->second.first)
		{
			wall = itr->second.second;
			if (getBoundingRect().intersects(wall->getBoundingRect()))
			{
				if (velocityX > 0 && getPosition().x < wall->getPosition().x)
				{
					setPosition(wall->getPosition().x - (wall->getWidth()) / 2 - getWidth() / 2 - 75, getPosition().y);
				}
				if (velocityX < 0 && getPosition().x > wall->getPosition().x)
				{
					setPosition(wall->getPosition().x + (wall->getWidth()) / 2 + getWidth() / 2 + 75, getPosition().y);
				}
				this->healthPoints--;
				}
			
		}
		itr++;
	}
}

/*************************************************************
Function: checkCollisionWall
Date Created: December 4, 2017
Date Last Modified:
Description: updates character for collision with wall
bugs:
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
Notes: Should probably adjust the offset values
*************************************************************/
void Character::checkCollisionWall(map<string, pair<string, GameObject*>> gameObjects)
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

/*************************************************************
Function: checkHealth
Date Created: December 4, 2017
Date Last Modified:
Description: checks the state of the characters health and acts accordingly
bugs:
status: functional
Input parameters:
Returns:
Preconditions:
Postconditions:
Notes: Should probably adjust the offset values
*************************************************************/
void Character::checkHealth()
{
	if (healthPoints == 1)
	{
		getSprite().setScale(1, 1);
	}
	else if (healthPoints == 0)
	{
		//Game Over - for now just returns to start of level
		//This is currently not functioning as intend

		//Reset
		healthPoints = 2;
		Sleep(500);
		setPosition(10, GameEngine::SCREEN_HEIGHT / 2);
		getSprite().setScale(2, 2);
		
	}
}

void Character::checkCollisionGoal(map<string, pair<string, GameObject*>> gameObjects)
{
	GameObject* goal = nullptr;
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if ("goal" == itr->second.first)
		{
			goal = itr->second.second;

			if (getBoundingRect().intersects(goal->getBoundingRect())) //Wall and bug collide
			{

				if (velocityX > 0 && getPosition().x < goal->getPosition().x)
				{
					setPosition(goal->getPosition().x - goal->getWidth() / 2 - getWidth() / 2, getPosition().y);
				}
				if (velocityX < 0 && getPosition().x > goal->getPosition().x)
				{
					setPosition(goal->getPosition().x + goal->getWidth() / 2 + getWidth() / 2, getPosition().y);
				}
			}
		}
		itr++;
	}
}