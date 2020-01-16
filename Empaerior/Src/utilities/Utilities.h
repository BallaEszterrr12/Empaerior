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
		Empaerior::string get_platform();//gets the current platform


		int cpu_cache_size();//returns the size of the cpu  cache in bytes
		int get_core_number();// get the number of CPU cores available
		int get_system_ram();//get the amount of RAM configured in the system.


		
		




		//returns the coordinates of the mouse relative to the screen
		Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> get_screen_mouse_coords();


		//gets the coordinates of the mouse based on where the camera is
		Empaerior::v_pair<Empaerior::fl_point, Empaerior::fl_point> get_world_mouse_coords(const Empaerior::Camera& camera);




		//check if a rect contains a point
		Empaerior::boole rect_contains_point(const Empaerior::Rect& rect, int x, int y);


		inline double d2r(double d)
		{
			return (d / 180.0) * ((double)M_PI);
		}

		inline double sind(double x) 
		{
			
			return std::sin(d2r(x));
		}


		inline double cosd(double x) 
		{
			return std::cos(d2r(x));
		}

		



	}

	



}