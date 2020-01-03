#include "pch.h"
#include "Application.h"

#define fullscreen 0





Empaerior::Application::Application()
{


}

void Empaerior::Application::Init()
{

	


}



void Empaerior::Application::set_state(Emaperior::State* new_state)
{
	cur_state = new_state;
	SDL_RenderSetLogicalSize(Application::window.renderer, new_state->get_camera().rect.w, new_state->get_camera().rect.h); // set the render size to the new state's camera

}


void Empaerior::Application::run()
{
	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;

	while (Empaerior::Application::is_running)
	{





		//not a permanent solution to handle events
		while (SDL_PollEvent(&Empaerior::Application::event)) {

			handlevents(Empaerior::Application::event);

		}
		if (!Empaerior::Application::is_paused)
		{


			framestart = SDL_GetTicks();
			frametime = framestart - currentime;

			if (frametime > 25) frametime = 25; //if too many frames are skipped

			currentime = framestart;
			acumulator += frametime;



			while (acumulator >= Empaerior::Application::dt)
			{


				//update 

				Update(Empaerior::Application::dt);

				acumulator -= Empaerior::Application::dt;



			}


			//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);




			Empaerior::Application::window.clear();
			render();

			Empaerior::Application::window.render();


		}

		Empaerior::Asset_Loading::clean_textures();

	}
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

