#ifndef PANE_HPP
#define PANE_HPP

#include "Environment.hpp"

#include <SFML\Graphics.hpp>

#include <vector>
#include <string>

class Pane
{
public:
	Pane(std::string app_name, Environment *env);
	Pane(const sf::Vector2f size, const std::string title, Environment *env);
	~Pane();

	std::string title;

	sf::RectangleShape mainpane;
	sf::RectangleShape titlebar;
	sf::RectangleShape closebutton;
	sf::RectangleShape leftborder;
	sf::RectangleShape rightborder;
	sf::RectangleShape bottomborder;
	sf::RectangleShape boundingbox;
	sf::Text titletext;

	int PID; // Pane ID
	bool focused;
	bool active;
	bool visible;

	void setPosition(const sf::Vector2f newpos);
	void setTitle(const std::string title);
	void resize(const sf::Vector2f newsize);
	void focus();
	void defocus();
	void setVisible(bool yesno);

	void handleEvents(const sf::Event &event);

private:
	Environment *environment;
	sf::Font font;
	
	void setSize(const sf::Vector2f size);
};

#endif // !PANE_HPP