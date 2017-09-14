#ifndef TASKBAR_HPP
#define TASKBAR_HPP

#include <SFML\Graphics.hpp>

class Environment;

class Taskbar
{
public:
	Taskbar(Environment *environment);
	~Taskbar();

	sf::RectangleShape bar;
	sf::RectangleShape div;
	sf::RectangleShape startButton;

	bool isStartMenuOpen;
	bool isTaskbarHidden;

	void openStartMenu();
	void closeStartMenu();

private:
	Environment *environment;
};

#endif /* TASKBAR_HPP */