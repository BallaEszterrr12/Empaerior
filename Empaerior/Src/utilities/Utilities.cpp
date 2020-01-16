#include "pch.h"
#include "Utilities.h"
#include <SDL.h>
Empaerior::string Empaerior::Utilities::get_clipboard_text()
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

void Empaerior::Utilities::set_clipboard_text(const char* text)
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

Empaerior::string Empaerior::Utilities::get_platform()
{
	const char* sdl_platform = SDL_GetPlatform();
	Empaerior::string e_platform = sdl_platform;
	SDL_free((void*)sdl_platform);
	return e_platform;

}

int Empaerior::Utilities::cpu_cache_size()
{
	return SDL_GetCPUCacheLineSize();
}

int Empaerior::Utilities::get_core_number()
{
	return SDL_GetCPUCount();
}

int Empaerior::Utilities::get_system_ram()
{
	return SDL_GetSystemRAM();
}

Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> Empaerior::Utilities::get_screen_mouse_coords()
{
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	SDL_GetMouseState(&pos.first, &pos.second);

//Transform for the position of the renderer
//This is in case the viewport  doesn't match the camera (blackboxing)

	Empaerior::D_Rect renderer_viewport;
	SDL_RenderGetViewport(Empaerior::Application::window.renderer, &renderer_viewport);

	pos.first -= renderer_viewport.x;
	pos.second -= renderer_viewport.y;

	Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> f_pos;
	f_pos.first = pos.first;
	f_pos.second = pos.second;

	return f_pos;
}

Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> Empaerior::Utilities::get_world_mouse_coords(const Empaerior::Camera& camera)
{
	//get the positions
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	SDL_GetMouseState(&pos.first, &pos.second);


	//Transform the position relative to the camera
	pos.first *= camera.rect.w;
	pos.second *= camera.rect.h;



	pos.first /= Application::window.get_width();
	pos.second /= Application::window.get_heigth();



	//Tranform for position
	pos.first += camera.rect.x;
	pos.second += camera.rect.y;


	//Transform for the position of the renderer
//This is in case the viewport  doesn't match the camera (blackboxing)

	Empaerior::D_Rect renderer_viewport;
	SDL_RenderGetViewport(Application::window.renderer, &renderer_viewport);

	pos.first -= renderer_viewport.x;
	pos.second -= renderer_viewport.y;
	




	 Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> f_pos;
	 f_pos.first = Empaerior::fl_point(pos.first);
	 f_pos.second = Empaerior::fl_point(pos.second);

	 return f_pos;

}

Empaerior::boole Empaerior::Utilities::rect_contains_point(const Empaerior::Rect& rect, int x, int y)
{
	//TODO: This is the ugliest piece of code in the entire project,nice
	double p_x = double(x);
	double p_y = double(y);
	double o_x = double(rect.dimensions.x) + double(rect.dimensions.w)/2;
	double o_y = double(rect.dimensions.y) + double(rect.dimensions.h)/2;


	
	//rotating the point counter-clockwise
	double c_x = o_x +  (p_x - o_x) * cosd(rect.angle) - (p_y - o_y) *sind(rect.angle);
	double c_y = o_y +	(p_y - o_y) * cosd(rect.angle) + (p_x - o_x) *sind(rect.angle);
	
	//
	

	
	//checking the collision
	if (c_x <= double(rect.dimensions.x) || c_x > double(rect.dimensions.x) + double(rect.dimensions.w)) return false;
	if (c_y <= double(rect.dimensions.y) || c_y > double(rect.dimensions.y) + double(rect.dimensions.h)) return false;

	return true;
}

