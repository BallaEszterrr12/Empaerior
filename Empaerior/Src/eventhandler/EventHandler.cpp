#include "pch.h"
#include "EventHandler.h"

void Empaerior::Event_Listener::register_event(Empaerior::u_int type, EventCallback callback)
{
	_registeredCallbacks[type].push_back(callback);
}


void Empaerior::Event_Listener::handleEvents(Empaerior::Event& cur_event)
{
	for (int i = 0; i < _registeredCallbacks[cur_event.event.type].size(); i++)//iterate throught command and match thoose that fit
	{
		_registeredCallbacks[cur_event.event.type][i](cur_event);
	}

}

void Empaerior::event_handled(Empaerior::Event& event)
{
	event.is_handled = true;
}

Empaerior::boole Empaerior::is_event_handled(const Empaerior::Event& event)
{
	return event.is_handled;
}
