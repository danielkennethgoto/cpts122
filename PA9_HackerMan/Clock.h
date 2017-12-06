#pragma once
#include <SFML/Graphics.hpp>
class Clock {
public:

	Clock();
	~Clock();
	float getTime();
	void restart();
private:
	
	sf::Clock* clock;
	


};