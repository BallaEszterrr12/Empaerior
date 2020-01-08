#pragma once

#include "pch.h"





#define SDL_MAIN_HANDLED

//


#include "Empaerior.h"


#include "SDLwrappers/SDL_Wrappers.h"
#include "exceptions/Exceptions.h"
#include "utilities/Utilities.h"
#include  "utilities/Timer.h"


//static objects variables
#pragma region static objects


std::unordered_map<Empaerior::string, std::shared_ptr<SDL_Texture>> Textures;
std::unordered_map<Empaerior::string, std::unordered_map<int, std::unique_ptr<TTF_Font>>> Fonts;
std::unordered_map<Empaerior::string, std::unique_ptr<Mix_Chunk>> Sounds;



Empaerior::State* Empaerior::Application::cur_state;
std::vector <Empaerior::State*> Empaerior::Application::states;
//time between frames
const Empaerior::u_s_int Empaerior::Application::dt = 1000 / 60;
bool Empaerior::Application::is_paused = 0;
bool Empaerior::Application::is_running = 1;
SDL_Event Empaerior::Application::event;
Empaerior::Window Empaerior::Application::window;



#pragma endregion


extern Empaerior::Application* Empaerior::Create_Application();
//THIS IS THE ENTRY POINT 
int main(int argc, char** argv)
{

#ifdef EMP_USE_LOGS

	Empaerior::Log::Init();

#endif // EMPAERIOR_DEBUG

	#pragma region SDL_Inititalization


	
	try {
#ifdef EMP_USE_LOGS
		ENGINE_INFO("INITIALIZING SDL");
#endif // EMPAERIOR_DEBUG
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




	
	
	
#ifdef EMP_USE_LOGS
	Empaerior::Timer timer;
	timer.start();

	ENGINE_INFO("Creating Application");
#endif // EMPAERIOR_DEBUG
	Empaerior::Application* aplication = Empaerior::Create_Application();
	
	aplication->Init();




	
	
	
	
	try {
		
#ifdef EMP_USE_LOGS
		ENGINE_INFO("Runnning Aplication");
#endif // EMPAERIOR_DEBUG
		aplication->run();

	}
	catch (std::runtime_error & e)
	{
#ifdef EMP_USE_LOGS
		ENGINE_CRITICAL(e.what() + '\n');
#endif // EMPAERIOR_DEBUG
	}
	

	

#ifdef EMP_USE_LOGS
	ENGINE_INFO("Stoping Application");
	
	ENGINE_INFO("Application runned for " +std::to_string(timer.getTicks()) + " ms");
	timer.stop();
#endif // EMPAERIOR_DEBUG
	Empaerior::Application::window.reset();

	Empaerior::Asset_Loading::reset_assets();


	SDLW::Quit();
	
#ifdef EMP_USE_LOGS
	ENGINE_WARN("Stopped Application");
#endif // EMPAERIOR_DEBUG
	return 0;
}