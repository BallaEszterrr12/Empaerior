#include "pch.h"
#include "Camera.h"
#include "../../Game.h"

namespace Empaerior
{
	void Camera::set_dimensions(const int& w, const int& h)
	{

		rect.w = w;
		rect.h = h;
		if (this == &Empaerior::Game::cur_state->get_camera())// if the camera is the one used to render
		{
			SDL_RenderSetLogicalSize(Empaerior::Game::window.renderer, rect.w, rect.h); // using letterboxing, not a huge deal
		}
		
	}
}
