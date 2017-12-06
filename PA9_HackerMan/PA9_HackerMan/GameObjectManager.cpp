#include "GameObjectManager.h"

/*************************************************************
Function: GameObjectManager() <<constructor>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: starts mTimeSinceLastUpdate clock

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
GameObjectManager::GameObjectManager() {
	mTimeSinceLastUpdate.restart();
}

/*************************************************************
Function: ~GameObjectManager <<destructor>>
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: calls helper functor to dellete all objects

status: functional

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
GameObjectManager::~GameObjectManager() {
	std::for_each(gameObjects.begin(), gameObjects.end(), GameObjectDeallocator());
}

/*************************************************************
Function: add()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: adds a new object associated with a key and type
to the container.

key must be unique

status: functional

Input parameters: key, pointer to GameObject
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameObjectManager::add(string name, string type, GameObject* gameObject) {
	gameObjects.insert(pair<string, pair<string, GameObject*>>(name, pair<string, GameObject*>(type, gameObject)));
}

/*************************************************************
Function: remove()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: removes object from container

status: functional

Input parameters: key
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameObjectManager::remove(string name) {
	map<string, pair<string, GameObject*>>::iterator results = gameObjects.find(name);
	if (results != gameObjects.end())
	{
		delete results->second.second;
		gameObjects.erase(results);
	}
}

/*************************************************************
Function: get()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: returns pointer to object whose key is passed in

status: functional

Input parameters: key
Returns: pointer to GameObject, nullptr if key doesn't exist
Preconditions:
Postconditions:
*************************************************************/
GameObject* GameObjectManager::get(std::string name) const {
	map<string, pair<string, GameObject*>>::const_iterator results = gameObjects.find(name);
	if (results == gameObjects.end())
	{
		return nullptr;
	}
	return results->second.second;
}

/*************************************************************
Function: getObjectCount()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: returns number of objects in container

status: functional

Input parameters:
Returns: number of objects in container
Preconditions:
Postconditions:
*************************************************************/
int GameObjectManager::getObjectCount() const {
	return gameObjects.size();
}

/*************************************************************
Function: drawAll()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: sends draw message to all objects in container

status: functional

Input parameters: window to draw to
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameObjectManager::drawAll(sf::RenderWindow &window)
{
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second.second->draw(window);
		itr++;
	}
}

/*************************************************************
Function: updateAll()
Date Created: November 27, 2017
Date Last Modified: Novemver 27, 2017

Description: sends message to all GameObjects in container to
update

status: functional

Input parameters: event to for objects to react to
Returns:
Preconditions:
Postconditions:
*************************************************************/
void GameObjectManager::updateAll(sf::Event &event) {
	map<string, pair<string, GameObject*>>::const_iterator itr = gameObjects.begin();
	sf::Time timeDelta = mTimeSinceLastUpdate.getElapsedTime();
	mTimeSinceLastUpdate.restart();

	while (itr != gameObjects.end())
	{
		itr->second.second->update(timeDelta.asSeconds(), event, gameObjects);
		itr++;
	}
}