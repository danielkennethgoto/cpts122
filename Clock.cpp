#include "Clock.h"

Clock::Clock() {
	clock = new sf::Clock;
}

Clock::~Clock() {

}
float Clock::getTime() {
	return clock->getElapsedTime().asMilliseconds();
}
void Clock::restart() {
	clock->restart();
}