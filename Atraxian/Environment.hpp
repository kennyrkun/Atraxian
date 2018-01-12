#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics\RenderWindow.hpp>

class Renderer;
class Taskbar;
class Pane;

class Environment
{
public:
	Environment(sf::VideoMode dimensions, std::string title, int envid);
	~Environment();

	int environmentID;

	std::vector<Pane*> panes;
	sf::RenderWindow *window;
	Renderer *renderer;
	Taskbar *taskbar;

	void main();
	void switchFocusedPaneTo(Pane* pane);

private:
	Pane *nullPane;
	Pane *focusedPane = nullPane;
};

const std::string ENVIRONMENT_VERSION("0.10.0");

#endif /* ENVIRONMENT_HPP*/
