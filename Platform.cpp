#include "Platform.h"

Platform::Platform() 
	: GameObject("platform.png")
{
	load();
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

void Platform::update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) {

}