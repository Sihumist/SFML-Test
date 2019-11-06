#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timer
{
public:
	Timer();

	void setUpdateMs(const sf::Time& update_ms);	// set fps of objects using this class object


	sf::Clock getClock();
	sf::Time getElapsedTime();
	sf::Time getUpdateMs();

	void updateElapsedTime();
	void subtractMsFromElapsed();

private:
	sf::Clock clock;
	sf::Time elapsed;
	sf::Time update_ms;
};