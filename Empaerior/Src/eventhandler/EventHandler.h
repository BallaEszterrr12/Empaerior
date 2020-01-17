#pragma once
#include <SDL.h>
#include<SDL_events.h>
#include <functional>
#include "defines/Defines.h"

namespace Empaerior {


	struct Event
	{
		//the event
		SDL_Event event;
		//Check to see if it was handled
		Empaerior::boole is_handled = false;
	};

	//make an event handled
	void event_handled(Empaerior::Event& event);
	//check if is handled
	Empaerior::boole is_event_handled(const Empaerior::Event& event);

	//stack overflow to the rescue
	class Event_Listener
	{
	public:

		using EventCallback = std::function<void(Empaerior::Event&)>;

		Event_Listener() {};
		~Event_Listener() {};


		void register_event(Empaerior::u_int type, EventCallback callback); //put a callback in the lisener
		
		void handleEvents(Empaerior::Event& cur_event); //execute commands
		
	private:
		std::unordered_map<uint64_t, std::vector<EventCallback>> _registeredCallbacks;//type of the event and function
	};
}

