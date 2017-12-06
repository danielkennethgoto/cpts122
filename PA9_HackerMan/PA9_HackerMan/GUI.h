#pragma once
#include <SFML/Graphics.hpp>

using std::string;
using std::map;
using std::pair;


class GUI {
public:
	GUI();
	void update(int number, sf::RenderWindow &window, int x, int y);
private:
	sf::Font MyFont;
	sf::Text myText;

};