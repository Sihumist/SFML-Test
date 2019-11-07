#include "timer.h"

// Elapsed(0), ms(120)
Timer::Timer()
{
	this->elapsed = clock.restart();
	this->update_ms = sf::seconds(1.f / 120.f);
}

void Timer::setUpdateMs(const sf::Time& update_ms)
{
	this->update_ms = update_ms;
}

sf::Clock Timer::getClock()
{
	return this->clock;
}

sf::Time Timer::getElapsedTime()
{
	return this->elapsed;
}

sf::Time Timer::getUpdateMs()
{
	return this->update_ms;
}

void Timer::updateElapsedTime()
{
	this->elapsed += clock.restart();
}

void Timer::subtractMsFromElapsed()
{
	this->elapsed -= this->update_ms;
}
