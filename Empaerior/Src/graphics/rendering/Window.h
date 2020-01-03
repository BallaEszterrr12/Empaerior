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
		Window(const std::string& name, const Uint32& width, const Uint32& height);




		~Window()
		{
			if (window != nullptr)	SDL_DestroyWindow(window);
			if (renderer != nullptr)SDL_DestroyRenderer(renderer);

		}
		int Init(const std::string& name, const Uint32& width, const Uint32& height);
		void render();
		void clear();

		void reset();
		void toggle_fullscreen();

		Uint32 get_width()
		{
			return width;
		}

		Uint32 get_heigth()
		{
			return height;
		}

		SDL_Renderer* renderer;
		SDL_Window* window;
	private:

		EventListener window_listener;
		Uint32 width = 0;
		Uint32 height = 0;
	};
}