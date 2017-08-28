#include "Taskbar.hpp"
#include "logger.hpp"

#include "Environment.hpp"
#include "Renderer.hpp"

Taskbar::Taskbar(Environment *environment_)
{
	environment = environment_;

	bar.setFillColor(sf::Color::White); // TODO: USERF:CUSTOMISE
	bar.setSize(sf::Vector2f(environment_->window->getSize().x, 40.0f)); // as long as the window, and 40 pixels high
	bar.setOrigin(bar.getSize().x / 2.0f, bar.getSize().y / 2.0f); // center it
	bar.setPosition(environment_->window->getSize().x / 2.0f, (environment_->window->getSize().y - (bar.getLocalBounds().height / 2.0f)));

	start_button.setFillColor(sf::Color::Red);
	start_button.setSize(sf::Vector2f(40, 40));
	start_button.setOrigin(start_button.getLocalBounds().width / 2, start_button.getLocalBounds().height / 2);
	start_button.setPosition(bar.getLocalBounds().left + 20, bar.getPosition().y);

	div.setSize(sf::Vector2f(start_button.getLocalBounds().height / 18, bar.getLocalBounds().height - 4.0f));
	div.setPosition(start_button.getPosition().x + start_button.getLocalBounds().width / 2 + div.getLocalBounds().width, bar.getPosition().y - div.getLocalBounds().height / 2);
	div.setFillColor(sf::Color::Black);

	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	time.setCharacterSize(bar.getLocalBounds().height - 16.0f);
	time.setFillColor(sf::Color::Black);
	time.setFont(font);
	time.setString("00:00:00");

	time.setOrigin(sf::Vector2f(time.getLocalBounds().width * 2, time.getLocalBounds().height * 2));
	time.setPosition(sf::Vector2f((bar.getPosition().x * 2) - (time.getLocalBounds().width / 2), bar.getPosition().y - (time.getLocalBounds().height / 2)));

	environment->renderman->addToQueue(&bar);
	environment->renderman->addToQueue(&start_button);
	environment->renderman->addToQueue(&div);
	environment->renderman->addToQueue(&time);

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

void Taskbar::addToTaskbar(Pane* pane)
{
	taskbarItems.push_back(pane);
}

void Taskbar::removeFromTaskbar(Pane* pane)
{
	for (size_t i = 0; i < taskbarItems.size(); i++)
		if (pane == taskbarItems[i])
			delete taskbarItems[i];
}

void Taskbar::Update()
{

}