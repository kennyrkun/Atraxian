#include "Logger.hpp"
#include "Environment.hpp"
#include "Filesystem.hpp"
#include "Renderer.hpp"
#include "Taskbar.hpp"
#include "Pane.hpp"
#include "MapleParser.hpp"
#include "Util.hpp"

#include <ctime>

Environment::Environment(sf::VideoMode dimensions, std::string title, int envID)
{
	if (!environment::util::fs_ready())
		environment::util:: ready_fs();

	logger::setOutputDir("root", ("environment" + std::to_string(envID)));

	logger::INFO("Creating new Environment instance...");
	environmentID = envID;

	window = new sf::RenderWindow;
	window->create(dimensions, (title + " (" + std::to_string(envID) + ")"), (sf::Style::Close | sf::Style::Titlebar));
	window->setFramerateLimit(60);

	renderer = new Renderer(this);

	taskbar = new Taskbar(this);

	nullPane = new Pane(sf::Vector2f(0, 0), "null", this);
	nullPane->PID = 0;
	nullPane->setVisible(false);

	logger::INFO("New Environment instance created.");
}

Environment::~Environment()
{
	logger::INFO("Cleaning up...");

	delete window;
	delete taskbar;
	delete renderer;
	delete focusedPane;

	logger::INFO("Environment destroyed.");
}

bool mouseIsOver(sf::Shape &object, sf::RenderWindow &window)
{
	if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		return true;
	else
		return false;
}

void Environment::switchFocusedPaneTo(Pane* pane)
{
	if (panes.size() > 1 && pane != nullPane)
		focusedPane->defocus();

	focusedPane = pane;
	focusedPane->focus();
}

void Environment::main()
{
	renderer->addToQueue(&taskbar->bar);
	renderer->addToQueue(&taskbar->startButton);
	renderer->addToQueue(&taskbar->div);
//	renderer->addToQueue(&taskbar->time);

	bool dragging_pane(false);
	
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				panes.clear();
				renderer->clearQueue();
				window->close();
				return;
			}

			else if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (!panes.empty()) // make sure there are panes
					{
						bool selected(false);
						bool already_selected(false);

						// if we clicked on any pane
						for (int i = panes.size() - 1; i >= 0; i--)
						{
							if (mouseIsOver(panes[i]->boundingbox, *window) && panes[i]->visible) // check if we're in the pane, and it's visible
							{
								logger::SILENT("EXTRA-INFO", "Clicked inside the boundingbox of Pane" + std::to_string(panes[i]->PID));

								if (mouseIsOver(panes[i]->titlebar, *window)) // then on the title bar
								{
									logger::SILENT("EXTRA-INFO", "Clicked inside the titlebar of Pane" + std::to_string(panes[i]->PID));

									if (mouseIsOver(panes[i]->closebutton, *window)) // then the close button
									{
										logger::SILENT("EXTRA-INFO", "Clicked the close button of Pane" + std::to_string(panes[i]->PID));

										delete panes[i];
										panes.erase(std::remove(panes.begin(), panes.end(), panes[i]), panes.end());
										break;
									}
									else
									{
										logger::SILENT("EXTRA-INFO", "Clicked only the titlebar, started dragging.");

										dragging_pane = true;
									}
								}

								if (panes[i] == focusedPane)
								{
									already_selected = true;

									logger::SILENT("EXTRA-INFO", "Pane" + std::to_string(focusedPane->PID) + " was already focused.");
								}
								else // wasn't already selected.
								{
									logger::SILENT("EXTRA-INFO", "Pane" + std::to_string(focusedPane->PID) + " was not already focused.");

									switchFocusedPaneTo(panes[i]);
									selected = true;

									logger::SILENT("EXTRA-INFO", "Bringing Pane" + std::to_string(focusedPane->PID) + " to the top of the Render Queue.");
									renderer->pushBack(&focusedPane->titletext);
									renderer->pushBack(&focusedPane->titlebar);
									renderer->pushBack(&focusedPane->closebutton);
									renderer->pushBack(&focusedPane->mainpane);
									renderer->pushBack(&focusedPane->leftborder);
									renderer->pushBack(&focusedPane->rightborder);
									renderer->pushBack(&focusedPane->bottomborder);
									renderer->pushBack(&focusedPane->titletext);
								}

								break;
							}
						}

						// if we didn't select anything, do nothing.
						// if there is nothing we *could have* selected, do nothing (because they might have clicked the close button).
						if (!already_selected && !panes.empty())
						{
							if (!selected)
							{
								if (focusedPane != nullPane)
								{
									logger::SILENT("EXTRA-INFO", "Nothing was selected. (Not even Pane0 D:)");

									focusedPane->defocus();
									focusedPane = nullPane;
								}
								else
								{
									logger::SILENT("EXTRA-INFO", "No pane was already selected.");
								}
							}
							else
							{
								logger::SILENT("EXTRA-INFO", "Something new was selected. (Pane" + std::to_string(focusedPane->PID) + ")");
							}
						}
					}

					if (mouseIsOver(taskbar->bar, *window)) // if we click the taskbar
					{
						if (mouseIsOver(taskbar->startButton, *window)) // clicked the startbutton
						{
							logger::INFO("Clicked the start button.");

							taskbar->startButton.setFillColor(sf::Color::Green);

							if (!panes.empty())																				// TODO: this
								focusedPane->defocus(); // we defocus it because we are focused on the start menu while we do this, we will refocus when the start menu is closed.
						}
					}
				}
			}

			else if (event.type == sf::Event::EventType::MouseButtonReleased)
			{
				if (mouseIsOver(taskbar->bar, *window))
				{
					if (mouseIsOver(taskbar->startButton, *window)) // let go of the start menu
					{
						logger::INFO("Released the start button.");

						taskbar->startButton.setFillColor(sf::Color::Red);

//						if (!panes.empty() && focusedPane->focused == true)
//							focusedPane->focus(); // refocus the panel.

//						we want to refocus the pane only if it was already focused.						
					}
				}

				if (dragging_pane)
				{
					logger::INFO("Pane" + std::to_string(focusedPane->PID) + " was dragged to X: " + std::to_string(static_cast<int>(focusedPane->boundingbox.getPosition().x)) + ", Y: " + std::to_string(static_cast<int>(focusedPane->titlebar.getPosition().y)) + ".");

					dragging_pane = false;
				}
			}

			else if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::N) // NEW PANE HOTKEY
				{
					sf::Clock creation_timer;

					logger::BREAK();
					Pane* newpane = new Pane("root//apps//test", this);
					panes.push_back(newpane);
					switchFocusedPaneTo(newpane);

					logger::INFO("Pane creation took " + std::to_string(creation_timer.getElapsedTime().asSeconds()) + " seconds.");
					logger::BREAK();
				}
				else if (focusedPane != nullPane && event.key.code == sf::Keyboard::Key::Delete) // DELETE PANE HOTKEY
				{
					delete focusedPane;
					panes.erase(std::remove(panes.begin(), panes.end(), focusedPane), panes.end()); // remove it from the stack
					focusedPane = nullPane;
				}
			}
		} // event loop

		{
			// if we are holding the left alt key and space at the same time, and there is at least one pane, center it.
			if (!panes.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				focusedPane->setPosition(sf::Vector2f(window->getView().getCenter()));

				logger::SILENT("EXTRA-INFO", "Pane" + std::to_string(focusedPane->PID) + " centered.");
			}
			// if we are left clicking, panes exist, and are holding over the focused one, then move it to the position of the mouse. used for click and drag positioning.
			else if (dragging_pane)
			{
				sf::Vector2i move_origin;
				move_origin.x = sf::Mouse::getPosition(*window).x;
				move_origin.y = sf::Mouse::getPosition(*window).y;

				focusedPane->setPosition(sf::Vector2f(move_origin));
			}
		}

		window->clear(sf::Color::Blue);
		renderer->render();
		window->display();
	}
}
