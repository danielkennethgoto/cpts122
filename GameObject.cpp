#include "GameObject.h"

/*************************************************************
Function: GameObject() <<constructor>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: initializes mIsLoaded to false

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions: 
*************************************************************/
GameObject::GameObject()
	: mIsLoaded{false} {

}

/*************************************************************
Function: ~GameObject() <<destructor>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: default

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
GameObject::~GameObject() {
	
}

/*************************************************************
Function: load()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: loads image for sprite

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameObject::load() {
	if (mImage.loadFromFile(mFileName)) //check if file successfully loaded
	{
		mSprite.setTexture(mImage);
		mIsLoaded = true;
	}
	else
	{
		mIsLoaded = false;
	}
}

/*************************************************************
Function: draw()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: draws object to render window

status: functional

Input parameters: window to be drawn to
Returns:
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
void GameObject::draw(sf::RenderWindow &window) {
	if (isLoaded())
	{
		window.draw(mSprite);
	}
}

/*************************************************************
Function: update()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: pure virtual function. Updates the object based
			 on time since last frame update, event in queue,
			 and properties of other objects

status: functional

Input parameters:
Returns:
Preconditions: must be overriden in derived classes
Postconditions:
*************************************************************/
void GameObject::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {

}

/*************************************************************
Function: setPosition() <<float>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: sets objects position

status: functional

Input parameters: new x position, new y position
Returns:
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
void GameObject::setPosition(float x, float y) {
	if (isLoaded())
	{
		mSprite.setPosition(x, y);
	}
}

/*************************************************************
Function: setPosition() <<sf::Vector2f>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: sets object position

status: functional

Input parameters: new Vector2f position
Returns:
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
void GameObject::setPosition(sf::Vector2f newPosition) {
	if (isLoaded())
	{
		mSprite.setPosition(newPosition);
	}
}

/*************************************************************
Function: getPosition()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: returns Vector2f position of object

status: functional

Input parameters:
Returns: object postion as Vector2f
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
sf::Vector2f GameObject::getPosition() const {
	return (isLoaded()) ? mSprite.getPosition() : sf::Vector2f();
}

/*************************************************************
Function: isLoaded()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: returns true if sprite image successfullly loaded

status: functional

Input parameters:
Returns: true if sprite image successfully loaded
Preconditions:
Postconditions: 
*************************************************************/
bool GameObject::isLoaded() const {
	return (mIsLoaded) ? true : false;
}

/*************************************************************
Function: getWidth()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: -returns width of object as a float
			 -accounts for rotations

status: functional

Input parameters:
Returns: object width as float
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
float GameObject::getWidth() const {
	return (isLoaded()) ? mSprite.getGlobalBounds().width : 0;
}

/*************************************************************
Function: getHeight()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: -returns height of object as a float
			 -accounts for rotations

status: functional

Input parameters:
Returns: object height as float
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
float GameObject::getHeight() const {
	return (isLoaded()) ? mSprite.getGlobalBounds().height : 0;
}

/*************************************************************
Function: getBoundingRecy()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: return Rect defining sprites bounding box

status: functional

Input parameters:
Returns: bounding box as Rect
Preconditions: sprite image must be loaded
Postconditions:
*************************************************************/
sf::Rect<float> GameObject::getBoundingRect() const {
	return (isLoaded()) ? mSprite.getGlobalBounds() : sf::Rect<float>();
}


