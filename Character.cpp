#include "Character.h"
#include "GameEngine.h"
Character::Character()
	: GameObject::GameObject("stickman.png"),
	jump{ false },
	isJumping{false},
	timeSinceJumpStart{ 0 },
	velocityX {0},
	deltaY {0}
{
	load();
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

void Character::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {
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
		isJumping = true;
	}

	if (isJumping)
	{
		timeSinceJumpStart += timeLastUpdate;
		deltaY = 0.5 * jumpVelocity * timeSinceJumpStart + 0.5 * acceleration * timeSinceJumpStart * timeSinceJumpStart;
	}

	if (getSprite().getPosition().y > GameEngine::GROUND - getHeight() / 2 - 1)
	{
		isJumping = false;
		getSprite().setPosition(getSprite().getPosition().x, GameEngine::GROUND - getHeight() / 2 - 1);
		timeSinceJumpStart = 0;
		velocityY = 0;
		deltaY = 0;
	}

	if (getBoundingRect().intersects(gameObjects.find("platform")->second->getBoundingRect()))
	{
		isJumping = false;
		getSprite().setPosition(getSprite().getPosition().x, gameObjects.find("platform")->second->getBoundingRect().top - getHeight()/2);
	}

	getSprite().move(velocityX * timeLastUpdate, deltaY);

	
}