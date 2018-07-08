#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "Environment.hpp"
#include "Pane.hpp"
#include "App.hpp"

struct ProcessInfo
{
	int pid;
};

class Process
{
public:
	Process(int pid);
	~Process();

	App* app;
	Pane* pane;

	ProcessInfo info;

	void assignPane(Pane* pane_);

	void HandleEvents(sf::Event &event);
	void Update();
	void Draw();
};

#endif // !PROCESS_HPP