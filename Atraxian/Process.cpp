#include "Process.hpp"

#include "Logger.hpp"

Process::Process(int pid)
{
	info.pid = pid;

	logger::INFO("created process" + std::to_string(pid));
}

Process::~Process()
{
}

void Process::assignPane(Pane* pane_)
{
	pane = pane_;
}

void Process::HandleEvents(sf::Event &event)
{

}

void Process::Update()
{

}

void Process::Draw()
{

}
