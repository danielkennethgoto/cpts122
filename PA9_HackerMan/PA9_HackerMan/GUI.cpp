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
	char textArray[100] = " milliSeconds";
	itoa(number, &charArray[0], 10);
	int j= strlen(charArray);
	int i = 0;
	do {
		charArray[j+i] = textArray[i];
		i++;
	} while (textArray[i] != '\0');
	charArray[j + i] = '\0';
	myText.setString(charArray);
	myText.setPosition(sf::Vector2f(x, y));
	window.draw(myText);
}