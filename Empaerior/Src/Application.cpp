#include "pch.h"
#include "Application.h"






Empaerior::Application::Application()
{


}

void Empaerior::Application::Init()
{

	


}



void Empaerior::Application::set_state(Empaerior::State* new_state)
{
	cur_state = new_state;
	SDL_RenderSetLogicalSize(Application::window.renderer, new_state->get_camera().rect.w, new_state->get_camera().rect.h); // set the render size to the new state's camera

}




void Empaerior::Application::Update(const unsigned int& dt )
{




	cur_state->Update(Application::dt);


}

void Empaerior::Application::handlevents(Empaerior::Event& event)
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

