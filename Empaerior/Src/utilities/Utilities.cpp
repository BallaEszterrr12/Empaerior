#include "pch.h"
#include "Utilities.h"
#include <SDL.h>
Empaerior::string Empaerior::get_clipboard_text()
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

void Empaerior::set_clipboard_text(const char* text)
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

Empaerior::string Empaerior::get_platform()
{
	const char* sdl_platform = SDL_GetPlatform();
	Empaerior::string e_platform = sdl_platform;
	SDL_free((void*)sdl_platform);
	return e_platform;

}

int Empaerior::cpu_cache_size()
{
	return SDL_GetCPUCacheLineSize();
}

int Empaerior::get_core_number()
{
	return SDL_GetCPUCount();
}

int Empaerior::get_system_ram()
{
	return SDL_GetSystemRAM();
}

Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> Empaerior::get_screen_mouse_coords()
{
	v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	SDL_GetMouseState(&pos.first, &pos.second);
	return pos;
}

Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> Empaerior::get_world_mouse_coords(const Empaerior::Camera& camera)
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
