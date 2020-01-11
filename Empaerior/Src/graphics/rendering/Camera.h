#pragma once
#include <SDL.h>
#include "defines/Defines.h"
namespace Empaerior
{

	class Camera
	{
	public:
		Camera()
		{

		}
		~Camera()
		{

		}
		Camera(const Empaerior::Rect& camera)
			:rect(camera)

		{

		}
		Camera(const int& x, const int& y, const int& w, const int& h)
			:rect({ x,y,w,h })

		{

		}
		void set_position(const int& x, const int& y)
		{
			rect.x = x;
			rect.y = y;

		}
		void set_dimensions(const  Empaerior::s_int& w, const  Empaerior::s_int& h);


		Empaerior::Rect rect = { 0,0,0,0 };
	private:


	};
}