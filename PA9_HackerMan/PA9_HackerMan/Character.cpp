#include "Character.h"
#include "GameEngine.h"

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
		if (sf::Keyboard::Space == event.key.code
			|| sf::Keyboard::W == event.key.code
			|| sf::Keyboard::Up == event.key.code)
		{
			jump = true;
		}
		if (sf::Keyboard::A == event.key.code
			|| sf::Keyboard::Left == event.key.code)
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
	deltaY = 0.5 * velocityY0 * freeFallTime + 0.5 * acceleration * freeFallTime * freeFallTime;
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