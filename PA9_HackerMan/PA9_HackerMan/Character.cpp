#include "Character.h"
#include "GameEngine.h"
Character::Character()
	: GameObject::GameObject("stickman.png"),
	jump{ false },
	deltaY{ 0 },
	deltaX{0},
	velocityX{ 0 },
	velocityY0{0},
	velocityY{0},
	freeFallTime{0}

{
	load();
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	getSprite().setScale(2, 2);
}

void Character::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {
	GameObject* platform = gameObjects.find("platform")->second;//get pointer to platform
	
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
	
	if (jump && freeFallTime == 0)
	{
		velocityY0 = jumpVelocity;//should be a function setVelocityY0(jumpVelocity)
	}

	//should be a funciton updateFreeFallTime()
	//update freefall
	freeFallTime += timeLastUpdate;
	//should be function updateYKinematics();
	deltaY = 0.5 * velocityY0 * freeFallTime + 0.5 * acceleration * freeFallTime * freeFallTime;
	velocityY = velocityY0 + acceleration * freeFallTime;

	//function to update deltaX
	deltaX = velocityX * timeLastUpdate;

	//update position
	getSprite().move(deltaX, deltaY);

	//check new location collisions
	//if on ground
	if (getPosition().y > GameEngine::GROUND - getHeight() / 2 - 1)
	{
		setPosition(getPosition().x, GameEngine::GROUND - getHeight() / 2 - 1);
		freeFallTime = 0;
		velocityY0 = 0;
	}

	//should be own function, glitch when platform is less than a char height from other plaform but top of char is within height of platform
	//if jumping onto platform
	for (int i = 0; i < 2; i++)
	{
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
		platform = gameObjects.find("platform2")->second;
	}

	

	
}