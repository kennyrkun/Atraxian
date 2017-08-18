#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML\Graphics.hpp>
#include <memory>

class Taskbar;
class Pane;
class Renderer;

class Environment
{
public:
	Environment(sf::VideoMode dimensions, std::string title, int envid);
	~Environment();

	int environmentID;

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Taskbar> taskbar;
	std::shared_ptr<Renderer> renderman;

	void main();
	void switchFocusedPaneTo(Pane* pane);

private:
	std::vector<Pane*> panes;
	Pane *nullPane;
	Pane *focusedPane = nullPane;
};

const std::string ENVIRONMENT_VERSION("0.0.643");

#endif /* ENVIRONMENT_HPP*/
