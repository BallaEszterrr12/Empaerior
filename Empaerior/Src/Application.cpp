#include "pch.h"
#include "Application.h"

#define fullscreen 0





Empaerior::Application::Application()
{

	
	window.Init("test", 960, 800);
	
	states.emplace_back(new State());//add a new state
	//second_state = new State();

	set_state(states[0]);
	
	SDL_RenderSetLogicalSize(Application::window.renderer, Application::cur_state->get_camera().rect.w, Application::cur_state->get_camera().rect.h);


}

void Empaerior::Application::Init()
{

	


}



void Empaerior::Application::set_state(State* new_state)
{
	cur_state = new_state;
	SDL_RenderSetLogicalSize(Application::window.renderer, new_state->get_camera().rect.w, new_state->get_camera().rect.h); // set the render size to the new state's camera

}

void Empaerior::Application::Update(const unsigned int& dt )
{




	cur_state->Update(Application::dt);


}

void Empaerior::Application::handlevents(const SDL_Event & event)
{
	
	Empaerior::Application::window.window_listener.handleEvents(event);
	cur_state->handleevents(event);

}

void Empaerior::Application::render()
{
	//SDL_RenderClear(Game::renderer);

	cur_state->Render();

	//SDL_RenderPresent(Game::renderer);

}

