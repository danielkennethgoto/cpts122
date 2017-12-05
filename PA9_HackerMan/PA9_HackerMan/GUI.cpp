#include "GUI.h"

GUI::GUI() {
	if (!MyFont.loadFromFile("OpenSans.ttf"))
	{
		// Error...
	}
	
	myText.setCharacterSize(50);
	myText.setFont(MyFont);
	myText.setString("Hello");
	// Or, if you want to do it after the construction :


}

void GUI::update(int number, sf::RenderWindow &window, int x, int y) {
	char charArray[100];
	itoa(number, &charArray[0], 10);
	myText.setString(charArray);
	myText.setPosition(sf::Vector2f(x, y));
	window.draw(myText);
}