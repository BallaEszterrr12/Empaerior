#include "pch.h"
#include "EventHandler.h"

void Empaerior::Event_Listener::register_event(Empaerior::u_s_int type, EventCallback callback)
{
	_registeredCallbacks[type].push_back(callback);
}


void Empaerior::Event_Listener::handleEvents(const SDL_Event& cur_event)
{
	for (int i = 0; i < _registeredCallbacks[cur_event.type].size(); i++)//iterate throught command and match thoose that fit
	{
		_registeredCallbacks[cur_event.type][i](cur_event);
	}

}
