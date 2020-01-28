#include "pch.h"
#include "Application.h"






Empaerior::Application::Application()
{


}

void Empaerior::Application::Init()
{

	


}



void Empaerior::Application::Update(const unsigned int& dt )
{




	for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Update(dt);
	}


}

void Empaerior::Application::handlevents(Empaerior::Event& event)
{
	
	Empaerior::Application::window.window_listener.handleEvents(event);

	Empaerior::Application::window.window_listener.handleEvents(event);
	for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->handleevents(event);
	}

}

void Empaerior::Application::render()
{
	//SDL_RenderClear(Game::renderer);

	for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Render();
	}

	//SDL_RenderPresent(Game::renderer);

}

