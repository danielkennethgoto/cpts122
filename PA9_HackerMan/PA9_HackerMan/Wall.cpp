#pragma once
#include "Wall.h"
#include "GameEngine.h"

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
Wall::Wall() : GameObject::GameObject("bitWall.png")
{
	mImage2.loadFromFile("fireWall2.png");
	load("bitWall.png");
	currentSprite = 0;
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
	getSprite().setScale(1, 1);
}


/*************************************************************
Function: setAttributes()
Date Created: December 3, 2017
Date Last Modified:
Description: Allows programmer to configure the objects properties
status: untested
Input parameters:
Returns:
Preconditions: no negative values
Postconditions:
*************************************************************/
void Wall::setAttributes(int newHeight, int newWidth, bool dangerous)
{
	this->heightScale = newHeight;
	this->widthScale = newWidth;
	this->doesDamage = dangerous;
	getSprite().setScale(widthScale, heightScale);
	if (doesDamage == true)
	{
		load("fireWall1.png");
		currentSprite = 1;
		key = "fireWall";
	}
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
void Wall::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects)
{

	if (currentSprite == 1) {
		currentSprite = 2;
		setNewTexture(1);
		printf("Update");
	}
	else if (currentSprite ==2) {
		currentSprite = 1;
		setNewTexture(2);
		printf("Update");
	}
	//Empty

}

bool Wall::getDoesDamage()
{
	return this->doesDamage;
}

string Wall::getKey()
{
	return key;
}