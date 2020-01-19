#pragma once

#include <string>
#include <iostream>
#include <Empaerior.h>
#include <cmath>
namespace Empaerior
{
	namespace Utilities {
		//clipboard functions
		Empaerior::string get_clipboard_text();

		void set_clipboard_text(const char* text);




		//system functions
		inline Empaerior::string get_platform()//gets the current platform
		{
			const char* sdl_platform = SDL_GetPlatform();
			Empaerior::string e_platform = sdl_platform;
			SDL_free((void*)sdl_platform);
			return e_platform;

		}

		inline int cpu_cache_size()// returns the size of the cpu  cache in bytes
		{
			return SDL_GetCPUCacheLineSize();
		}
		
		inline int get_core_number()// get the number of CPU cores available
		{
			return SDL_GetCPUCount();
		}
		inline int get_system_ram()//get the amount of RAM configured in the system.
		{
			return SDL_GetSystemRAM();
		}



		//Toggle the cursor
		//0 - no
		//1 - yes
		inline void show_cursor(Empaerior::boole toogle)
		{
			SDL_ShowCursor(toogle);
		}


	

	



		//returns the coordinates of the mouse relative to the screen
		Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> get_screen_mouse_coords();


		//gets the coordinates of the mouse based on where the camera is
		Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> get_world_mouse_coords(const Empaerior::Camera& camera);




		//check if a rect contains a point
		Empaerior::boole rect_contains_point(const Empaerior::Rect& rect, Empaerior::fl_point x , Empaerior::fl_point y);



	
		



	}

	



}