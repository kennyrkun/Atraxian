#include "Pane.hpp"

#include "Environment.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"

const float titlebar_height = 32.0f;
const float border_width = 6.25f;

const sf::Color focusedColour(109, 109, 109);
const sf::Color defocusedColour(200, 200, 200);

Pane::Pane(std::string title, Environment *env) : environment(env)
{
//	MapleParser app(title);
//	paneInfo = app.appInfo; // TODO: get paneInfo out of here

	PID = env->processes.size() + 1;

	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	titletext.setFont(font);
	titletext.setFillColor(sf::Color::Black);
//	title = paneInfo.name;

//	setSize(app.appInfo.dimensions);
	setPosition(env->window->getView().getCenter());
	setTitle(title); // relies on things being in place already

	setVisible(true);

	logger::INFO("\"" + title + "\" created. (Pane" + std::to_string(PID) + ")");
}

Pane::Pane(const sf::Vector2f size, const std::string $title, Environment *env) : environment(env) // THIS METHOD SHOULD BE USED FOR DEBUGGING ONLY.
{
	title = $title;

	PID = env->processes.size() + 1;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	titletext.setFont(font);
	titletext.setFillColor(sf::Color::Black);

	setSize(size);
	setPosition(env->window->getView().getCenter());
	setTitle(title);

	setVisible(true);

	logger::INFO("'" + title + "' created. (Pane" + std::to_string(PID) + ")");
}

Pane::~Pane()
{
	setVisible(false);
	logger::INFO("Destroyed Pane" + std::to_string(PID) + ".");
}

void Pane::setPosition(const sf::Vector2f newpos)
{
	titlebar.setPosition(newpos);
	titletext.setPosition(sf::Vector2f(titlebar.getPosition().x - (titlebar.getSize().x / 2), titlebar.getPosition().y - (titlebar.getSize().y / 2)));

//	//	g j p q y
//	if (title.find('p') != std::string::npos)
//		titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 6);
//	else
//		titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);

	mainpane.setPosition(titlebar.getPosition().x, titlebar.getPosition().y + mainpane.getLocalBounds().height / 2 + (titlebar.getLocalBounds().height / 2));
	closebutton.setPosition((titlebar.getPosition().x + titlebar.getLocalBounds().width / 2) - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y);
	leftborder.setPosition((mainpane.getPosition().x - mainpane.getLocalBounds().width / 2) - leftborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	rightborder.setPosition((mainpane.getPosition().x + mainpane.getLocalBounds().width / 2 + (rightborder.getLocalBounds().width)) - rightborder.getLocalBounds().width / 2, mainpane.getPosition().y - titlebar.getLocalBounds().height / 2);
	bottomborder.setPosition(mainpane.getPosition().x, mainpane.getPosition().y + (mainpane.getLocalBounds().height / 2) + bottomborder.getLocalBounds().height / 2);
	boundingbox.setPosition(mainpane.getPosition().x, mainpane.getPosition().y - ((titlebar.getLocalBounds().height / 2) - (bottomborder.getLocalBounds().height / 2)));
}

void Pane::setTitle(const std::string new_title)
{
	//TODO: make this work properly
	// we don't need it centered, we want it to the riding on the right edge of the left border

	titletext.setString(new_title);
//	titletext.setOrigin(titletext.getLocalBounds().width / 2, titletext.getLocalBounds().height / 2);
	titletext.setPosition(sf::Vector2f(titlebar.getPosition().x - (titlebar.getSize().x / 2), titlebar.getPosition().y - (titlebar.getSize().y / 2)));

//	if (new_title.find('p') != std::string::npos ||
//		new_title.find('g') != std::string::npos ||
//		new_title.find('j') != std::string::npos ||
//		new_title.find('q') != std::string::npos ||
//		new_title.find('y') != std::string::npos)

//		titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 6);
//	else
//		titletext.setPosition(titlebar.getPosition().x - (closebutton.getLocalBounds().width / 2), titlebar.getPosition().y - (titletext.getLocalBounds().height / 2) + 2);
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

	logger::INFO("Pane" + std::to_string(PID) + " focused.");
}

void Pane::defocus()
{
	focused = false;

	titlebar.setFillColor(sf::Color(defocusedColour));
	leftborder.setFillColor(sf::Color(defocusedColour));
	rightborder.setFillColor(sf::Color(defocusedColour));
	bottomborder.setFillColor(sf::Color(defocusedColour));
	
	logger::INFO("Pane" + std::to_string(PID) + " defocused.");
}

void Pane::setVisible(bool yesno)
{
	if (yesno)
	{
		environment->renderer->addToQueue(&boundingbox);
		environment->renderer->addToQueue(&titlebar);
		environment->renderer->addToQueue(&titletext);
		environment->renderer->addToQueue(&closebutton);
		environment->renderer->addToQueue(&mainpane);
		environment->renderer->addToQueue(&leftborder);
		environment->renderer->addToQueue(&rightborder);
		environment->renderer->addToQueue(&bottomborder);

		visible = true;
		// or should it be visible = !visible;
	}
	else
	{
		environment->renderer->removeFromQueue(&boundingbox);
		environment->renderer->removeFromQueue(&titlebar);
		environment->renderer->removeFromQueue(&titletext);
		environment->renderer->removeFromQueue(&closebutton);
		environment->renderer->removeFromQueue(&mainpane);
		environment->renderer->removeFromQueue(&leftborder);
		environment->renderer->removeFromQueue(&rightborder);
		environment->renderer->removeFromQueue(&bottomborder);

		visible = false;
	}
}

void Pane::handleEvents(const sf::Event & event)
{
	logger::INFO("pane got events");
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

	titletext.setCharacterSize(static_cast<int>(titlebar.getLocalBounds().height) - 10);
//	titletext.setOrigin(sf::Vector2f(titletext.getLocalBounds().width / 2, titletext.getLocalBounds().height / 2));

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
