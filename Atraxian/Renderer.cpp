#include "Renderer.hpp"
#include "logger.hpp"

Renderer::Renderer(const std::shared_ptr<sf::RenderWindow>& targetWindow_)
{
	targetWindow = targetWindow_;

	logger::INFO("New Renderer instance created.");
}

Renderer::~Renderer()
{
	render_queue.clear();

	logger::INFO("Renderer instance destroyed.");
}

void Renderer::addToQueue(sf::Drawable *object)
{
 	render_queue.push_back(object);
}

void Renderer::removeFromQueue(sf::Drawable *object) // still gives us memory leaks
{
	render_queue.erase(std::remove(render_queue.begin(), render_queue.end(), object), render_queue.end());
}

void Renderer::pushBack(sf::Drawable *object) // still wastes memory.
{
	for (size_t i = 0; i < render_queue.size(); i++)
	{
		if (object == render_queue[i])
		{
			render_queue.push_back(render_queue[i]);
			break;
		}
	}
}

void Renderer::clearQueue()
{
	render_queue.clear();

	logger::INFO("Cleared the Render Queue.");
}

void Renderer::render()
{
	if (!render_queue.empty())
	{
		for (size_t i = 0; i < render_queue.size(); i++)
		{
			targetWindow.get()->draw(*render_queue[i]);
		}
	}
}
