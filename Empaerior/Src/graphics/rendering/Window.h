#pragma once
#include "../../eventhandler/EventHandler.h"
#include "defines/Defines.h"
namespace Empaerior
{

	class Window
	{
		friend class Application;

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
		

		inline Empaerior::u_int get_width()
		{
			return width;
		}

		inline Empaerior::u_int get_heigth()
		{
			return height;
		}


		inline void set_render_dimensions(const Empaerior::Int_Rect& rect)
		{
			SDL_RenderSetLogicalSize(renderer, rect.w, rect.h);
		}


		SDL_Renderer* renderer;
		SDL_Window* window;
		//lisens for window events
		Event_Listener window_listener;
	private:
		Empaerior::u_int width = 0;
		Empaerior::u_int height = 0;
	};


	namespace Window_Functions
	{
	


		//Changes the name of the window
		inline void change_window_name(const Empaerior::Window& window,const Empaerior::string& new_name)
		{
			SDL_SetWindowTitle(window.window, new_name.c_str());
		}

		//Toggles fullscreen
		inline void toggle_fullscreen(const Empaerior::Window& window)
		{
			Empaerior::u_int FullscreenFlag = SDL_WINDOW_FULLSCREEN;
			bool IsFullscreen = SDL_GetWindowFlags(window.window) & FullscreenFlag;
			SDL_SetWindowFullscreen(window.window, IsFullscreen ? 0 : FullscreenFlag);
		}

		//TODO : ADD SET ICON FUNCTION


	}


}