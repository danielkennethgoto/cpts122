#include "NewCharacter.h"
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
NewCharacter::NewCharacter()
	: GameObject::GameObject("walkingright1.png"),
	jump{ false },
	deltaY{ 0 },
	deltaX{ 0 },
	velocityX{ 0 },
	velocityY0{ 0 },
	velocityY{ 0 },
	freeFallTime{ 0 }

{
	currentSprite = "walkingright1.png";
	load("walkingright1.png");
	mImage2.loadFromFile("walkingright2.png");
	mImage3.loadFromFile("walkingright3.png");
	mImage4.loadFromFile("walkingleft1.png");
	mImage5.loadFromFile("walkingleft2.png");
	mImage6.loadFromFile("walkingleft3.png");
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	getSprite().setScale(.8, .8);
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
void NewCharacter::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects) {
	updateInput(event);
	if (ismoving) {
		updateSprite();
	}
	updateXKinematics(timeLastUpdate);
	updateYKinematics(timeLastUpdate);

	//update position
	getSprite().move(deltaX, deltaY);
	checkCollisionGround();
	checkCollisionPlatform(gameObjects);
}

void NewCharacter::updateSprite(void) {
	if (currentSprite == "walkingright1") {
		currentSprite = "walkingright2";
		setNewTexture(2);
	}
	else if (currentSprite == "walkingright2") {
		currentSprite = "walkingright3";
		setNewTexture(3);
	}
	else if (currentSprite == "walkingright3") {
		currentSprite = "walkingright1";
		setNewTexture(1);
	}
	if (currentSprite == "walkingleft1") {
		currentSprite = "walkingleft2";
		setNewTexture(5);
	}
	else if (currentSprite == "walkingleft2") {
		currentSprite = "walkingleft3";
		setNewTexture(6);
	}
	else if (currentSprite == "walkingleft3") {
		currentSprite = "walkingleft1";
		setNewTexture(4);
	}

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
void NewCharacter::updateInput(sf::Event event) {
	if (sf::Event::KeyPressed == event.type)
	{
		if (sf::Keyboard::Space == event.key.code)
		{
			jump = true;
		}
		if (sf::Keyboard::A == event.key.code)
		{
			velocityX = -1 * maxVelocityX;
			ismoving = true;
			currentSprite = "walkingleft1";
		}

		if (sf::Keyboard::D == event.key.code)
		{
			velocityX = maxVelocityX;
			ismoving = true;
			currentSprite = "walkingright1";
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
			lastdeltaX = -1;
			ismoving = false;
		}
		if (sf::Keyboard::D == event.key.code && velocityX > 0)
		{
			velocityX = 0;
			lastdeltaX = 1;
			ismoving = false;
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
void NewCharacter::updateFreeFallTime(float timeLastUpdate) {
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
void NewCharacter::updateYKinematics(float timeLastUpdate) {
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
void NewCharacter::updateXKinematics(float timeLastUpdate) {
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
void NewCharacter::checkCollisionGround() {
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
void NewCharacter::checkCollisionPlatform(map<string, pair<string, GameObject*>> gameObjects) {
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