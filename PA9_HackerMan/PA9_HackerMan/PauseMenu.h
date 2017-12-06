#pragma once
#include "Menu.h"
#define OPTIONSIZE 100
#define CreditSize 40

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow &window);
	~PauseMenu();

	void selectOption(sf::RenderWindow &window);
	void DrawAll(sf::RenderWindow &window);

	void SelectUp();
	void SelectDown();
	void SelectEnter(sf::RenderWindow &window, int &enter);

	void drawHelp(sf::RenderWindow &window);

	void setTextVisible();
	void setTextTransparent();
	void setTextVisible_Rules();
	void setTextTransparent_Rules();

	bool insideRectangle(sf::RenderWindow &window, sf::RectangleShape &Rectangle);
private:
	int OptionSelected;

	sf::Text Options[2];
	sf::Text Title;
	sf::RectangleShape optionshapes[2];//this is so the options can be selected with the mouse.

	sf::Text rules[5];//This is for the help page

	sf::Texture computerpng;
	sf::Sprite computersprite;

	sf::Font font;
	sf::Color color;
};

