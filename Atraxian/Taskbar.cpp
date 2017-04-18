#include "Taskbar.hpp"
#include "Environment.hpp"
#include "logger.hpp"

Taskbar::Taskbar(sf::RenderWindow *window)
{
	bar.setFillColor(sf::Color::White); // TODO: USERF:CUSTOMISE
	bar.setSize(sf::Vector2f(window->getSize().x, 40.0f)); // as long as the window, and 35 pixels high
	bar.setOrigin(bar.getSize().x / 2.0f, bar.getSize().y / 2.0f); // center it
	bar.setPosition(window->getSize().x / 2.0f, (window->getSize().y - (bar.getLocalBounds().height / 2.0f)));

	start_button.setFillColor(sf::Color::Red);
	start_button.setSize(sf::Vector2f(40, 40));
	start_button.setOrigin(start_button.getLocalBounds().width / 2, start_button.getLocalBounds().height / 2);
	start_button.setPosition(bar.getLocalBounds().left + 20, bar.getPosition().y);

	div.setSize(sf::Vector2f(start_button.getLocalBounds().height / 18, 36));
	div.setPosition(start_button.getPosition().x + start_button.getLocalBounds().width / 2 + div.getLocalBounds().width, bar.getPosition().y - div.getLocalBounds().height / 2);
	div.setFillColor(sf::Color::Black);

	logger::INFO("New taskbar created.");
}

Taskbar::~Taskbar()
{
	logger::INFO("Taskbar destroyed.");
}

void Taskbar::open_start_menu()
{
	is_start_open = true;

	start_button.setFillColor(sf::Color::Green);
}

void Taskbar::close_start_menu()
{
	is_start_open = false;

	start_button.setFillColor(sf::Color::Red);
}
