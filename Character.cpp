#include "Character.h"
#include "GameEngine.h"
Character::Character()
	: GameObject::GameObject("stickman.png"),
	isJumping{ false },
	timeSinceJumpStart{ 0 },
	velocityX {0}
{
	load();
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

void Character::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {
	if (getSprite().getPosition().y >= GameEngine::GROUND - getHeight()/2 - 1)
	{
		isJumping = false;
		getSprite().setPosition(getSprite().getPosition().x, GameEngine::GROUND - getHeight()/2 - 1);
		timeSinceJumpStart = 0;
		velocityY = 0;
	}
	
	if (sf::Event::KeyPressed == event.type)
	{
		if (sf::Keyboard::Space == event.key.code)
		{
			if (!isJumping)
			{
				isJumping = true;
			}
		}
		if (sf::Keyboard::Left == event.key.code)
		{
			velocityX = -1 * maxVelocityX;
		}

		if (sf::Keyboard::Right == event.key.code)
		{
			velocityX = maxVelocityX;
		}
	}

	if (sf::Event::KeyReleased == event.type)
	{
		if (sf::Keyboard::Left == event.key.code && velocityX < 0)
		{
			velocityX = 0;
		}
		if (sf::Keyboard::Right == event.key.code && velocityX > 0)
		{
			velocityX = 0;
		}
	}

	if (isJumping)
	{
		timeSinceJumpStart += timeLastUpdate;
		float deltaY = 0.5 * jumpVelocity * timeSinceJumpStart + 0.5 * acceleration * timeSinceJumpStart * timeSinceJumpStart;
		getSprite().move(0, deltaY);
	}

	getSprite().move(velocityX * timeLastUpdate, 0);

	
}