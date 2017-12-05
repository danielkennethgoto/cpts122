#include "Platform.h"

Platform::Platform()
	: GameObject("platform.png")
{
	load("platform.png");
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
}

Platform::~Platform() {

}

void Platform::update(float timeLastUpdate, sf::Event event, map<string, pair<string, GameObject*>> gameObjects) {

}