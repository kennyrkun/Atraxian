#include "Taskbar.hpp"
#include "logger.hpp"

#include "Environment.hpp"

Taskbar::Taskbar(Environment *environment)
{
	bar.setFillColor(sf::Color::White); // TODO: USERF:CUSTOMISE
	bar.setSize(sf::Vector2f(environment->window->getSize().x, 40.0f)); // as long as the window, and 40 pixels high
	bar.setOrigin(bar.getSize().x / 2.0f, bar.getSize().y / 2.0f); // center it
	bar.setPosition(environment->window->getSize().x / 2.0f, (environment->window->getSize().y - (bar.getLocalBounds().height / 2.0f)));

	startButton.setFillColor(sf::Color::Red);
	startButton.setSize(sf::Vector2f(40, 40));
	startButton.setOrigin(startButton.getLocalBounds().width / 2, startButton.getLocalBounds().height / 2);
	startButton.setPosition(bar.getLocalBounds().left + 20, bar.getPosition().y);

	div.setSize(sf::Vector2f(startButton.getLocalBounds().height / 18, bar.getLocalBounds().height - 4.0f));
	div.setPosition(startButton.getPosition().x + startButton.getLocalBounds().width / 2 + div.getLocalBounds().width, bar.getPosition().y - div.getLocalBounds().height / 2);
	div.setFillColor(sf::Color::Black);

	logger::INFO("New taskbar created.");
}

Taskbar::~Taskbar()
{
	logger::INFO("Taskbar destroyed.");
}

void Taskbar::openStartMenu()
{
	isStartMenuOpen = true;
	startButton.setFillColor(sf::Color::Green);
}

void Taskbar::closeStartMenu()
{
	isStartMenuOpen = false;
	startButton.setFillColor(sf::Color::Red);
}
