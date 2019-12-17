#pragma once
#include <SDL.h>
#include<SDL_events.h>
#include <map>
#include <functional>

namespace Empaerior {


	//stack overflow to the rescue
	class EventListener//handles only one type of SDL_event
	{
	public:

		using EventCallback = std::function<void(SDL_Event const&)>;

		EventListener() {};
		~EventListener() {};


		void register_event(Uint32 type, EventCallback callback); //put a callback in the lisener
		
		void handleEvents(const SDL_Event& cur_event); //execute commands
		
	private:
		std::unordered_map<uint64_t, std::vector<EventCallback>> _registeredCallbacks;//type of the event and function
	};
}

