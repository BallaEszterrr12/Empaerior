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



Emaperior::State* Empaerior::Application::cur_state;
std::vector <Emaperior::State*> Empaerior::Application::states;
const Uint32 Empaerior::Application::dt = 1000 / 60;
bool Empaerior::Application::is_paused = 0;
bool Empaerior::Application::is_running = 1;
SDL_Event Empaerior::Application::event;
Empaerior::Window Empaerior::Application::window;

#pragma endregion


extern Empaerior::Application* Empaerior::Create_Application();
//THIS IS THE ENTRY POINT 
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



	
	
	
	Empaerior::Application* aplication = Empaerior::Create_Application();
	
	aplication->Init();




	
	
	
	
	try {
		
		aplication->run();
	
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