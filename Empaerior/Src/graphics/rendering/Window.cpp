#include "pch.h"
#include "Window.h"
#include "../../Application.h"


Empaerior::Window::Window(const std::string& name, const Uint32& width, const Uint32& height)
: width(width),height(height)
{
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);

	window_listener.register_event(SDL_QUIT, [](SDL_Event const& event) { // add quit event 
		Empaerior::Application::is_running = false;
		});

	window_listener.register_event(SDL_WINDOWEVENT, [](SDL_Event const& event) { //add 
		switch (event.window.event) {
		case SDL_WINDOWEVENT_MINIMIZED:
			Empaerior::Application::is_paused = true;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			Empaerior::Application::is_paused = false;
			break;
		}
		});

}

Empaerior::Window::Window()
{
	

}

int Empaerior::Window::Init(const std::string& name, const Uint32& m_width, const Uint32& m_height)
{
	width = m_width;
	height = m_height;
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);

	window_listener.register_event(SDL_QUIT, [](SDL_Event const& event) { // add quit event 
		Empaerior::Application::is_running = false;
		});

	window_listener.register_event(SDL_WINDOWEVENT, [](SDL_Event const& event) { //add 
		switch (event.window.event) {
		case SDL_WINDOWEVENT_MINIMIZED:
			Empaerior::Application::is_paused = true;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			Empaerior::Application::is_paused = false;
			break;
		}
		});

	return 0;
}

void Empaerior::Window::render()
{
	SDL_RenderPresent(renderer);
}

void Empaerior::Window::clear()
{
	SDL_RenderClear(renderer);
}

void Empaerior::Window::reset()
{
	if (window != nullptr)	SDL_DestroyWindow(window);
	if (renderer != nullptr)SDL_DestroyRenderer(renderer);
}

void Empaerior::Window::toggle_fullscreen()
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
	SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
}
