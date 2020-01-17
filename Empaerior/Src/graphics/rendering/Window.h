#pragma once
#include "../../eventhandler/EventHandler.h"
#include "defines/Defines.h"
namespace Empaerior
{

	class Window
	{
		friend class Application;//Game can edit it's window

	public:
		Window();
		Window(const Empaerior::string& name, const Empaerior::u_int& width, const Empaerior::u_int& height);




		~Window()
		{
			if (window != nullptr)	SDL_DestroyWindow(window);
			if (renderer != nullptr)SDL_DestroyRenderer(renderer);

		}
		int Init(const Empaerior::string& name, const Empaerior::u_int& width, const Empaerior::u_int& height);
		void render();
		void clear();

		void reset();
		void toggle_fullscreen();

		Empaerior::u_int get_width()
		{
			return width;
		}

		Empaerior::u_int get_heigth()
		{
			return height;
		}

		SDL_Renderer* renderer;
		SDL_Window* window;
		//lisens for window events
		Event_Listener window_listener;
	private:
		Empaerior::u_int width = 0;
		Empaerior::u_int height = 0;
	};
}