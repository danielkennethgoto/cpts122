#include "Character.h"
#include "GameEngine.h"
Character::Character()
	: GameObject::GameObject("stickman.png"),
	jump{ false },
	deltaY{ 0 },
	velocityX{ 0 },
	vy0{0},
	vy{0},
	freeFallTime{0}

{
	load();
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

void Character::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {
	GameObject* platform = gameObjects.find("platform")->second;
	
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
	
	if (jump)
	{
		vy0 = jumpVelocity;
	}

	//update freefall
	freeFallTime += timeLastUpdate;
	deltaY = 0.5 * vy0 * freeFallTime + 0.5 * g * freeFallTime * freeFallTime;

	//if on ground
	if (getPosition().y > GameEngine::GROUND - getHeight() / 2 - 1)
	{
		setPosition(getPosition().x, GameEngine::GROUND - getHeight() / 2 - 1);
		freeFallTime = 0;
		vy0 = 0;
		deltaY = 0;
	}

	//if jumping onto platform
	if (getBoundingRect().intersects(platform->getBoundingRect()))
	{
		if (getPosition().y + getHeight() / 2 < platform->getBoundingRect().top + platform->getHeight())
		{
			setPosition(getPosition().x, platform->getBoundingRect().top - getHeight() / 2);
			freeFallTime = 0;
			vy0 = 0;
			deltaY = 0;
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

	getSprite().move(velocityX * timeLastUpdate, deltaY);

	
}