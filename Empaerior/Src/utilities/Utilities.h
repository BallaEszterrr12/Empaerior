#pragma once

#include <string>
#include <iostream>
#include <Empaerior.h>
namespace Empaerior
{
	namespace Utilities {
		//clipboard functions
		Empaerior::string get_clipboard_text();

		void set_clipboard_text(const char* text);




		//system functions
		Empaerior::string get_platform();//gets the current platform


		int cpu_cache_size();//returns the size of the cpu  cache in bytes
		int get_core_number();// get the number of CPU cores available
		int get_system_ram();//get the amount of RAM configured in the system.






		//returns the coordinates of the mouse relative to the screen
		Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> get_screen_mouse_coords();


		//gets the coordinates of the mouse based on where the camera is
		Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> get_world_mouse_coords(const Empaerior::Camera& camera);



	}

	



}