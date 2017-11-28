/*******************************************************************************************
Programmer: Reid Reininger (charles.reininger@wsu.edu)
Class: CptS 122, Fall  2017; Lab Section 11
Programming Assignment: PA9_Hacker_Man
Date Started: November 27, 2017
Last Update: November 27, 2017

file: GameObject.h

Description: abstract class from which all game objects must derive

			 inspired by "Game From Scratch C++ and SFML Edition!" tutorial at
			 http://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition.aspx

status: functional
*******************************************************************************************/
#include <SFML/Graphics.hpp>

using std::string;
using std::map;

class GameObject {
public:
	GameObject();
	~GameObject();

	virtual void load();
	virtual void draw(sf::RenderWindow window);
	virtual void update(float timeLastUpdate, sf::Event event, map<string, GameObject*> gameObjects) = 0;

	virtual void setPosition(float x, float y);
	virtual void setPosition(sf::Vector2f newPosition);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;

	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual sf::Rect<float> getBoundingRect() const;

private:
	sf::Sprite mSprite;
	sf::Texture mImage;
	string mFileName; //path to sprite image
	bool mIsLoaded; //is image loaded
};