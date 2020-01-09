#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <Empaerior.h>
namespace Empaerior
{
	//clipboard functions
	Empaerior::string get_clipboard_text()
	{
		if (SDL_HasClipboardText())//if there's text
		{
			char* sdl_text = SDL_GetClipboardText();//get the clipboard content as char*
			Empaerior::string clip_text = sdl_text;//transfom  the char* into a Empaerior::string
			SDL_free(sdl_text);//free the char*
			return clip_text;//return a string
		}
		return "";
	}
	void set_clipboard_text(const char* text)
	{
		try
		{
			if (SDL_SetClipboardText(text) < 0)
			{
				throw E_runtime_exception("Cannot copy text to clipboard", __FILE__, __LINE__, __FUNCTION__);
			}
		}
		catch (E_runtime_exception & e) {

			e.print_message();
			return;
		}
	}



	//system functions
	Empaerior::string get_platform()//gets the current platform
	{
		const char* sdl_platform = SDL_GetPlatform();
		Empaerior::string e_platform = sdl_platform;
		SDL_free((void*)sdl_platform);
		return e_platform;

	}

	int cpu_cache_size()//returns the size of the cpu  cache in bytes
	{
		return SDL_GetCPUCacheLineSize();
	}

	int get_core_number()// get the number of CPU cores available
	{
		return SDL_GetCPUCount();
	}

	int get_system_ram()//get the amount of RAM configured in the system.
	{
		return SDL_GetSystemRAM();
	}


	//returns the coordnitaes of the mouse relative to the screen
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> get_screen_mouse_coords()
	{
		v_pair<Empaerior::s_int, Empaerior::s_int> pos;
		SDL_GetMouseState(&pos.first, &pos.second);
		return pos;
	}


	//gets the coordinates of the mouse based on where the camera is
	Empaerior::v_pair<Empaerior::s_int,Empaerior::s_int> get_world_mouse_coords(const Empaerior::Camera& camera)
	{
		//get the positions
		v_pair<Empaerior::s_int, Empaerior::s_int> pos;
		SDL_GetMouseState(&pos.first, &pos.second);


		//Transform the position relative to the camera
		pos.first *= camera.rect.w;
		pos.second *= camera.rect.h;



		pos.first /= Application::window.get_width();
		pos.second /= Application::window.get_heigth();

		pos.first += camera.rect.x;
		pos.second += camera.rect.y;


		return pos;
	}



	




}