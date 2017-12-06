#include "Menu.h"

/*************************************************************
Function: Menu() <<constructor>>
Date Created: November 29, 2017
Date Last Modified: Novemver 30, 2017

Description:

status:

Input parameters: sf::RenderWindow window
Returns:
Preconditions: window is opended, font file must be included(needs to be added) inside project!!!
Postconditions:
*************************************************************/
Menu::Menu(sf::RenderWindow &window)
{
	if (!font.loadFromFile("arial.ttf"))//this is for loading the font for the text
	{
		// file didn't load
		std::cout << "File Wasn't Loaded" << std::endl;
		system("pause");
	}

	if (!computerpng.loadFromFile("gamebackground.png")) {
		std::cout << "Picture File Wasn't Loaded" << std::endl;
	}
	computersprite.setTexture(computerpng);
	//computersprite.setPosition(window.getSize().x / 15, window.getSize().y / 2);
	computersprite.setPosition(0, 0);

	sf::Color newColor(0, 128, 0);
	color = newColor;

	Title.setFont(font);
	Title.setString("HackerMan");
	Title.setColor(color);
	Title.setPosition(window.getSize().x / 6, window.getSize().y / 13);
	Title.setCharacterSize(OPTIONSIZE * 1.5);

	Options[0].setFont(font);
	Options[0].setString("Play");
	Options[0].setColor(sf::Color::White);
	Options[0].setPosition(window.getSize().x / 2.5, window.getSize().y / 4);
	Options[0].setCharacterSize(OPTIONSIZE);

	Options[1].setFont(font);
	Options[1].setString("Help");
	Options[1].setColor(color);
	Options[1].setPosition(window.getSize().x / 2.5, window.getSize().y / 2);
	Options[1].setCharacterSize(OPTIONSIZE);

	Options[2].setFont(font);
	Options[2].setString("Credits");
	Options[2].setColor(color);
	Options[2].setPosition(window.getSize().x / 2.5, window.getSize().y * 3 / 4);
	Options[2].setCharacterSize(OPTIONSIZE);

	sf::Vector2f shapesize(300, 100);

	optionshapes[0].setFillColor(sf::Color::Transparent);
	optionshapes[0].setPosition(Options[0].getPosition());//set it to the same position as its corresponding option
	optionshapes[0].setSize(shapesize);

	optionshapes[1].setFillColor(sf::Color::Transparent);
	optionshapes[1].setPosition(Options[1].getPosition());//set it to the same position as its corresponding option
	optionshapes[1].setSize(shapesize);

	optionshapes[2].setFillColor(sf::Color::Transparent);
	optionshapes[2].setPosition(Options[2].getPosition());//set it to the same position as its corresponding option
	optionshapes[2].setSize(shapesize);

	window.draw(optionshapes[0]);
	window.draw(optionshapes[1]);
	window.draw(optionshapes[2]);
	window.draw(Title);
	window.draw(Options[0]);
	window.draw(Options[1]);
	window.draw(Options[2]);
}


/*************************************************************
Function: selectOption
Date Created: November 29, 2017
Date Last Modified: Novemver 30, 2017

Description: This function allows for the user to select up and down with the arrow keys and press enter to select a choice

status: unfinished

Input parameters: sf::RenderWindow window
Returns:
Preconditions: window is opended, font file must be included(needs to be added) inside project!!!
Postconditions:
*************************************************************/
void Menu::selectOption(sf::RenderWindow &window)
{
	/*while (window.isOpen())
	{*/
	OptionSelected = 0;
	int enter = 0;//will change when enter is selected
	while (enter == 0)
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case  sf::Event::MouseButtonPressed:
				if (insideRectangle(window, optionshapes[0]))
				{
					std::cout << "Play Button Pressed" << std::endl;
					enter = 1;
					window.clear();
				}
				else if (insideRectangle(window, optionshapes[1]))
				{
					std::cout << "Help Button Pressed" << std::endl;
					drawHelp(window);
				}
				else if (insideRectangle(window, optionshapes[2]))
				{
					std::cout << "Credit Button Pressed" << std::endl;
					drawCredits(window);
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					SelectEnter(window, enter);
					break;
				case sf::Keyboard::Up:
					SelectUp();//moves selction up
					break;
				case sf::Keyboard::W:
					SelectUp();//moves selction up
					break;
				case sf::Keyboard::S:
					SelectDown();//moves selction down
					break;
				case sf::Keyboard::Down:
					SelectDown();//moves selction down
					break;
				default:
					break;
				}
				break;
			}

		}

		window.clear();
		DrawAll(window);
		window.display();
	}
}

void Menu::DrawAll(sf::RenderWindow &window)
{
	window.draw(computersprite);
	window.draw(optionshapes[0]);
	window.draw(optionshapes[1]);
	window.draw(optionshapes[2]);
	window.draw(Title);
	window.draw(Options[0]);
	window.draw(Options[1]);
	window.draw(Options[2]);
}

/*************************************************************
Function: SelectUP()
Date Created: November 29, 2017
Date Last Modified: Novemver 30, 2017

Description: This function allows for the user to select up

status:

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Menu::SelectUp()
{
	if (OptionSelected == 0)//so the options can roll over
	{
		Options[OptionSelected].setColor(color);
		OptionSelected = 2;
		Options[OptionSelected].setColor(sf::Color::White);
	}
	else
	{
		Options[OptionSelected].setColor(color);
		OptionSelected--;
		Options[OptionSelected].setColor(sf::Color::White);
	}
}
/*************************************************************
Function: SelectDown()
Date Created: November 29, 2017
Date Last Modified: Novemver 30, 2017

Description: This function allows for the user to select Down

status:

Input parameters:
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Menu::SelectDown()
{
	if (OptionSelected == 2)
	{
		Options[OptionSelected].setColor(color);
		OptionSelected = 0;
		Options[OptionSelected].setColor(sf::Color::White);
	}
	else
	{
		Options[OptionSelected].setColor(color);
		OptionSelected++;
		Options[OptionSelected].setColor(sf::Color::White);
	}
}

/*************************************************************
Function: SelectEnter()
Date Created: November 29, 2017
Date Last Modified: Novemver 30, 2017

Description: This function allows for the user to select their option
if Play is pressed the menu closes
if Help is pressed the rules are displayed
if credits is pressed the credits are displayed

status: complete

Input parameters: sf::RenderWindow &window, int &enter
Returns:
Preconditions:
Postconditions:
*************************************************************/
void Menu::SelectEnter(sf::RenderWindow &window, int &enter)
{
	if (OptionSelected == 0)//Play
	{
		std::cout << "Play Button Pressed" << std::endl;
		enter = 1;
		window.clear();
	}
	else if (OptionSelected == 1)//Help
	{
		std::cout << "Help Button Pressed" << std::endl;
		drawHelp(window);
	}
	else//Credits
	{
		std::cout << "Credit Button Pressed" << std::endl;
		drawCredits(window);

	}
}

Menu::~Menu()
{
}

/*************************************************************
Function: drawCredits()
Date Created: December 1, 2017
Date Last Modified: December 1, 2017

Description: This function instantiates the text for the credits page and draws it to the screen

status: complete

Input parameters: sf::RenderWindow &window
Returns:
Preconditions: window is opened
Postconditions:
*************************************************************/
void Menu::drawCredits(sf::RenderWindow &window)
{

	//Credits Title
	names[0].setFont(font);
	names[0].setString("Credits");
	names[0].setColor(color);
	names[0].setPosition(window.getSize().x / 6, window.getSize().y / 20);
	names[0].setCharacterSize(CreditSize * 1.5);

	//Reid Reininger - Game Engine/Object Manager
	names[1].setFont(font);
	names[1].setString("Reid Reininger - Game Engine/Object Manager");
	names[1].setColor(color);
	names[1].setPosition(window.getSize().x / 6, window.getSize().y / 5);
	names[1].setCharacterSize(CreditSize);
	//Daniel Goto - Artwork/Main Character
	names[2].setFont(font);
	names[2].setString("Daniel Goto - Artwork/Main Character");
	names[2].setColor(color);
	names[2].setPosition(window.getSize().x / 6, window.getSize().y * 3 / 10);
	names[2].setCharacterSize(CreditSize);
	//Patrick McCornack - Obstacles
	names[3].setFont(font);
	names[3].setString("Patrick McCornack - Obstacles");
	names[3].setColor(color);
	names[3].setPosition(window.getSize().x / 6, window.getSize().y * 2 / 5);
	names[3].setCharacterSize(CreditSize);
	//Andrew Feistner - Menus
	names[4].setFont(font);
	names[4].setString("Andrew Feistner - Menus");
	names[4].setColor(color);
	names[4].setPosition(window.getSize().x / 6, window.getSize().y / 2);
	names[4].setCharacterSize(CreditSize);
	int enter = 0;
	while (enter == 0)
	{

		window.clear();
		for (int i = 0; i < 5; i++)
		{
			window.draw(names[i]);
		}
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					enter = 1;
					break;
					break;
				}
			case  sf::Event::MouseButtonPressed:
				enter = 1;
				break;

			}
		}
	}
}

/*************************************************************
Function: drawHelp()
Date Created: December 1, 2017
Date Last Modified: December 1, 2017

Description: This function instantiates the text for the help page and draws it to the screen

status: complete

Input parameters: sf::RenderWindow &window
Returns:
Preconditions: window is opened
Postconditions:
*************************************************************/
void Menu::drawHelp(sf::RenderWindow &window)
{
	//Rules Title
	rules[0].setFont(font);
	rules[0].setString("Controls");
	rules[0].setColor(color);
	rules[0].setPosition(window.getSize().x / 6, window.getSize().y / 20);
	rules[0].setCharacterSize(CreditSize * 1.5);


	rules[1].setFont(font);
	rules[1].setString("\"a\" or \"left\" - go left");
	rules[1].setColor(color);
	rules[1].setPosition(window.getSize().x / 6, window.getSize().y / 5);
	rules[1].setCharacterSize(CreditSize);

	rules[2].setFont(font);
	rules[2].setString("\"d\" or \"right\"  - go right");
	rules[2].setColor(color);
	rules[2].setPosition(window.getSize().x / 6, window.getSize().y * 3 / 10);
	rules[2].setCharacterSize(CreditSize);

	rules[3].setFont(font);
	rules[3].setString("space bar or \"w\" - jump");
	rules[3].setColor(color);
	rules[3].setPosition(window.getSize().x / 6, window.getSize().y * 2 / 5);
	rules[3].setCharacterSize(CreditSize);

	rules[4].setFont(font);
	rules[4].setString("escape - pause menu");
	rules[4].setColor(/*sf::Color::*/color);
	rules[4].setPosition(window.getSize().x / 6, window.getSize().y / 2);
	rules[4].setCharacterSize(CreditSize);
	int enter = 0;
	while (enter == 0)
	{

		window.clear();
		for (int i = 0; i < 5; i++)
		{
			window.draw(rules[i]);
		}

		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					enter = 1;
					break;
					break;
				}
			case  sf::Event::MouseButtonPressed:
				enter = 1;
				break;

			}
		}
	}
}

/*************************************************************
Function: insideRectangle()
Date Created: December 3, 2017
Date Last Modified: December 3, 2017

Description: This function checks to see if the mouse curser is in the passed in rectangle

status: complete

Input parameters: sf::RenderWindow &window, sf::RectangleShape Rectangle
Returns: true if mouse is inside the rectangle, false if not inside the rectangle
Preconditions: window is opened
Postconditions:
*************************************************************/
bool Menu::insideRectangle(sf::RenderWindow &window, sf::RectangleShape &Rectangle)
{
	if (sf::Mouse::getPosition(window).x >= Rectangle.getPosition().x //leftmost side
		&& sf::Mouse::getPosition(window).x <= Rectangle.getPosition().x + Rectangle.getSize().x //rightmost side
		&& sf::Mouse::getPosition(window).y >= Rectangle.getPosition().y //top side
		&& sf::Mouse::getPosition(window).y <= Rectangle.getPosition().y + Rectangle.getSize().y)//bottom side
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
Function: DisplayStoryText()
Date Created: December 5, 2017
Date Last Modified: December 5, 2017

Description: This function displays text that tells the story of the game

status: complete

Input parameters: sf::RenderWindow &window
Returns: true if mouse is inside the rectangle, false if not inside the rectangle
Preconditions: window is opened
Postconditions:
*************************************************************/
void Menu::DisplayStoryText(sf::RenderWindow &window)
{	
	sf::Text story;

	story.setFont(font);
	story.setString("HackerMan,\n\nI forgot to turn in PA9. Your mission is to hack\ninto the OSBLE Site, make it past the firewall\nand place my PA9 into the turn in folder.\n\nGodspeed!");
	story.setColor(color);
	story.setPosition(window.getSize().x / 10, window.getSize().y / 12);
	story.setCharacterSize(CreditSize);


	//story[1].setFont(font);
	//story[1].setString("");
	//story[1].setColor(color);
	//story[1].setPosition(window.getSize().x / 6, window.getSize().y / 5);
	//story[1].setCharacterSize(CreditSize);

	//story[2].setFont(font);
	//story[2].setString("");
	//story[2].setColor(color);
	//story[2].setPosition(window.getSize().x / 6, window.getSize().y * 3 / 10);
	//story[2].setCharacterSize(CreditSize);

	//story[3].setFont(font);
	//story[3].setString("");
	//story[3].setColor(color);
	//story[3].setPosition(window.getSize().x / 6, window.getSize().y * 2 / 5);
	//story[3].setCharacterSize(CreditSize);

	//story[4].setFont(font);
	//story[4].setString("");
	//story[4].setColor(/*sf::Color::*/color);
	//story[4].setPosition(window.getSize().x / 6, window.getSize().y / 2);
	//story[4].setCharacterSize(CreditSize);
	int enter = 0;
	

		window.clear();
		/*for (int i = 0; i < 5; i++)
		{*/
		window.draw(story);
		

		window.display();
		while (enter == 0)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					enter = 1;
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Return:
						enter = 1;
						break;
						break;
					}
				case  sf::Event::MouseButtonPressed:
					enter = 1;
					break;
				}
			}
		}
}