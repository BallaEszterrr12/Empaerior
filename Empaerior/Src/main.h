#pragma once

#include "pch.h"





#define SDL_MAIN_HANDLED

//


#include "Application.h"


#include "SDLwrappers/SDL_Wrappers.h"
#include "exceptions/Exceptions.h"
#include "utilities/Utilities.h"
#include  "utilities/Timer.h"

typedef uint32_t Uint32;

//static objects variables
#pragma region static objects


std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Textures;
std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<TTF_Font>>> Fonts;
std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> Sounds;



State* Empaerior::Application::cur_state;
std::vector <State*> Empaerior::Application::states;
const Uint32 Empaerior::Application::dt = 1000 / 60;
bool Empaerior::Application::is_paused = 0;
bool Empaerior::Application::is_running = 1;
Empaerior::Window Empaerior::Application::window;

#pragma endregion


extern Empaerior::Application* Empaerior::Create_Application();

int main(int argc, char** argv)
{

	#pragma region SDL_Inititalization
	try {
		uint16_t error_flags = SDLW::Init();
		//check for errors
		if(error_flags & sdl)
		{
			throw E_runtime_exception("Failed to initialize SDL", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & sdl_image)
		{
			throw E_runtime_exception("Failed to initialize SDL Graphics", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & sdl_ttf)
		{
			throw E_runtime_exception("Failed to initialize SDL Font", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & sdl_mix)
		{
			throw E_runtime_exception("Failed to initialize SDL Audio", __FILE__, __LINE__, __FUNCTION__);
		}

	}
	catch (E_runtime_exception & e)
	{
		e.print_message();
	}
	
	
	#pragma endregion



	
	SDL_Event event;
	
	Empaerior::Application* aplication = Empaerior::Create_Application();
	
	aplication->Init();


	Uint32 framestart = 0;
	Uint32 frametime = 0;
	Uint32 currentime = 0;
	Uint32 acumulator = 0;

	
	
	
	
	try {
		while (Empaerior::Application::is_running)
		{

			

			
		
			//not a permanent solution to handle events
			while (SDL_PollEvent(&event)) {

				aplication->handlevents(event);
				
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

					aplication->Update(Empaerior::Application::dt);
					
					acumulator -= Empaerior::Application::dt;



				}
				

				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);
			


			
				Empaerior::Application::window.clear();
				aplication->render();
			
				Empaerior::Application::window.render();
				
				
			}
		
			Empaerior::Asset_Loading::clean_textures();
		
		}

	
	}
	catch (std::runtime_error & e)
	{
		std::cout <<e.what() << '\n';
	}
	

	
	Empaerior::Application::window.reset();

	Empaerior::Asset_Loading::reset_assets();

	
	

	SDLW::Quit();
	
	return 0;
}