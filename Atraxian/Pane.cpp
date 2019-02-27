#include "Environment.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"
#include "logger.hpp"

const float titlebar_height = 32.0f;
const float border_width = 6.25f;

Pane::Pane(const sf::Vector2f size, const std::string title, const int pid, Environment *environment_)
{
	environment = environment_;
	PID = pid;

	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	titletext.setFont(font);
	titletext.setString(title);

	setSize(size);

	setPosition(environment->window->getView().getCenter());
	
	logger::INFO("Pane" + std::to_string(pid) + " created");
}

Pane::~Pane()
{
	logger::INFO("Pane " + std::to_string(PID) + " destroyed.");
}

const sf::Color focusedColour(109, 109, 109);
const sf::Color defocusedColour(190, 190, 190);
const sf::Color closeButtonColor;
const sf::Color closeButtonHoverColor;

void Pane::setPosition(const sf::Vector2f newpos)
{
	titlebar.setPosition(newpos);
	titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);
	mainpane.setPosition(titlebar.getPosition().x, titlebar.getPosition().y + mainpane.getLocalBounds().height / 2 + (titlebar.getLocalBounds().height / 2));
	closebutton.setPosition((titlebar.getPosition().x + titlebar.getLocalBounds().width / 2) - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y);
	leftborder.setPosition((mainpane.getPosition().x - mainpane.getLocalBounds().width / 2) - leftborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	rightborder.setPosition((mainpane.getPosition().x + mainpane.getLocalBounds().width / 2 + (rightborder.getLocalBounds().width)) - rightborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	bottomborder.setPosition(mainpane.getPosition().x, mainpane.getPosition().y + (mainpane.getLocalBounds().height / 2) + bottomborder.getLocalBounds().height / 2);
	boundingbox.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - ((titlebar.getLocalBounds().height / 2) - (bottomborder.getLocalBounds().height / 2)));
}

void Pane::setTitle(const std::string title)
{
	titletext.setString(title);
	titletext.setOrigin(titletext.getLocalBounds().width / 2, titletext.getLocalBounds().height / 2);
	titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);

	titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);
}

void Pane::resize(const sf::Vector2f newsize)
{
	setSize(newsize);
	setPosition(titlebar.getPosition());
}

void Pane::focus()
{
	focused = true;

	titlebar.setFillColor(sf::Color(focusedColour));
	leftborder.setFillColor(sf::Color(focusedColour));
	rightborder.setFillColor(sf::Color(focusedColour));
	bottomborder.setFillColor(sf::Color(focusedColour));

	logger::INFO("Focused Pane" + std::to_string(PID) + ".");
}

void Pane::defocus()
{
	focused = false;

	titlebar.setFillColor(sf::Color(defocusedColour));
	leftborder.setFillColor(sf::Color(defocusedColour));
	rightborder.setFillColor(sf::Color(defocusedColour));
	bottomborder.setFillColor(sf::Color(defocusedColour));
	
	logger::INFO("Defocused Pane" + std::to_string(PID) + ".");
}

void Pane::addToTaskbar()
{
	environment->taskbar->addToTaskbar(this);
}

void Pane::removeFromTaskbar()
{
	environment->taskbar->removeFromTaskbar(this);
}

// PRIVATE

void Pane::setSize(const sf::Vector2f size)
{
	boundingbox.setSize(size);
	boundingbox.setOrigin(sf::Vector2f(boundingbox.getLocalBounds().width / 2, boundingbox.getLocalBounds().height / 2));

	mainpane.setFillColor(sf::Color::White);
	mainpane.setSize(sf::Vector2f(boundingbox.getLocalBounds().width - (border_width + border_width), boundingbox.getLocalBounds().height - (titlebar_height + border_width)));
	mainpane.setOrigin(sf::Vector2f(mainpane.getLocalBounds().width / 2, mainpane.getLocalBounds().height / 2));

	titlebar.setSize(sf::Vector2f(mainpane.getLocalBounds().width, titlebar_height));
	titlebar.setOrigin(sf::Vector2f(titlebar.getLocalBounds().width / 2, titlebar.getLocalBounds().height / 2));

	titletext.setCharacterSize(static_cast<int>(titlebar.getLocalBounds().height) - 8);
	titletext.setOrigin(sf::Vector2f(titletext.getLocalBounds().width / 2, titletext.getLocalBounds().height / 2));

	closebutton.setFillColor(sf::Color::Red);
	closebutton.setSize(sf::Vector2f(titlebar.getLocalBounds().height, titlebar.getLocalBounds().height));
	closebutton.setOrigin(sf::Vector2f(closebutton.getLocalBounds().width / 2, closebutton.getLocalBounds().height / 2));

	leftborder.setSize(sf::Vector2f(border_width, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	leftborder.setOrigin(sf::Vector2f(leftborder.getLocalBounds().width / 2, leftborder.getLocalBounds().height / 2));

	rightborder.setSize(sf::Vector2f(border_width, mainpane.getLocalBounds().height + titlebar.getLocalBounds().height));
	rightborder.setOrigin(sf::Vector2f(rightborder.getLocalBounds().width / 2, rightborder.getLocalBounds().height / 2));

	bottomborder.setSize(sf::Vector2f(mainpane.getLocalBounds().width + (border_width * 2), border_width));
	bottomborder.setOrigin(sf::Vector2f(bottomborder.getLocalBounds().width / 2, bottomborder.getLocalBounds().height / 2));
}