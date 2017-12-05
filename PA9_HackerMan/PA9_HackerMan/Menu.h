/*******************************************************************************************
Programmer: Andrew Feistner
Class: CptS 122, Fall  2017
Programming Assignment: PA9_Hacker_Man
Date Started: November 27, 2017
Last Update: November 27, 2017

file: Menu.h

Description: This creates a menu that will loop until Play is selected, 
				when it will then break out of the loop. 
				There are also options to see rules and credits

status: incomplete(in progress)

referenced SonarSystems: https://github.com/SonarSystems/SFML-2.1-Tutorial-51---Menu-Class/blob/master/TutorialSFML/TutorialSFML/Menu.cpp
*******************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define OPTIONSIZE 100
#define CreditSize 40

class Menu
{
public:
	Menu(sf::RenderWindow &window);
	~Menu();

	void selectOption(sf::RenderWindow &window);
	void DrawAll(sf::RenderWindow &window);

	void SelectUp();
	void SelectDown();
	void SelectEnter(sf::RenderWindow &window, int &enter);

	void drawCredits(sf::RenderWindow &window);
	void drawHelp(sf::RenderWindow &window);

	bool insideRectangle(sf::RenderWindow &window, sf::RectangleShape &Rectangle);

private:
	int OptionSelected;

	sf::Text Options[3];
	sf::Text Title;
	sf::RectangleShape optionshapes[3];//this is so the options can be selected with the mouse.

	sf::Text names[5];//This is for the credits page
	sf::Text rules[5];//This is for the help page

	sf::Font font;

	sf::Texture computerpng;
	sf::Sprite computersprite;
};

