#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>

class Renderer
{
public:
	Renderer(const std::shared_ptr<sf::RenderWindow>& targetWindow_);
	~Renderer();

	void addToQueue(sf::Drawable *object);
	void removeFromQueue(sf::Drawable *object);
	void pushBack(sf::Drawable *object);
	void clearQueue();
	void render();

private:
	std::shared_ptr<sf::RenderWindow> targetWindow;
	std::vector<sf::Drawable*> render_queue;
};

#endif /* RENDERER_HPP */
