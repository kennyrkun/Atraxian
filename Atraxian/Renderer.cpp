#include "Environment.hpp"
#include "Renderer.hpp"
#include "logger.hpp"

Renderer::Renderer(Environment *target_env)
{
	environment = target_env;

	logger::INFO("New Renderer instance created.");
}

Renderer::~Renderer()
{
	for (size_t i = 0; i < render_queue.size(); i++)
		delete render_queue[i];

	render_queue.clear();

	logger::INFO("Renderer instance destroyed.");
}

void Renderer::addToQueue(sf::Drawable *object)
{
 	render_queue.push_back(object);
}

void Renderer::removeFromQueue(sf::Drawable *object) // still gives us memory leaks
{
	for (size_t i = 0; i < render_queue.size(); i++)
	{
		if (object == render_queue[i])
		{
			// render_queue[i];
			render_queue.erase(std::remove(render_queue.begin(), render_queue.end(), object), render_queue.end());

			//FIXME: memory leaks here
			// attempting to do render_queue[i] instead of object causes a breakpoint to be triggered.
			// supposedly after deleting the object, but this is untested.

			break;
		}
	}
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
			environment->window->draw(*render_queue[i]);
		}
	}
}
