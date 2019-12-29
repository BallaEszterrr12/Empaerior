#include "pch.h"
#include "State.h"
#include "Game.h"
#include <SDL.h>
//for testing
#include<iostream>
#include <string>
#include "utilities/Timer.h"

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};


State::State()

{
	
	
	

	ecs.Init();
	ecs.register_component<Empaerior::Print_Component>();
	ecs.register_component<Empaerior::Position_Component>();
	ecs.register_component<Empaerior::Camera_Component>();
	ecs.register_component<Empaerior::Sprite_Component>();
	ecs.register_component<Empaerior::Event_Listener_Component>();
	ecs.register_component<Empaerior::Event_Listener_Component>();

	printy = ecs.register_system<Print_System>();
	spr_system = ecs.register_system <Sprite_System>();
	event_system = ecs.register_system<Event_System>();



	ecs.add_component_to_system<Empaerior::Print_Component, Print_System>();
	ecs.add_component_to_system<Empaerior::Sprite_Component, Sprite_System>();
	ecs.add_component_to_system<Empaerior::Event_Listener_Component, Event_System>();



	morge.id = ecs.create_entity_ID();
	


	ecs.add_component<Empaerior::Print_Component>(morge.id, Empaerior::Print_Component{ "morgeee" });
	ecs.add_component<Empaerior::Position_Component>(morge.id, Empaerior::Position_Component{ 10,10 });
	ecs.add_component<Empaerior::Camera_Component>(morge.id, Empaerior::Camera_Component{ {0,0,960,800} });
	ecs.add_component<Empaerior::Event_Listener_Component>(morge.id, Empaerior::Event_Listener_Component{});

	ecs.add_component<Empaerior::Sprite_Component>(morge.id, {});
	



		
	camera = ecs.get_component<Empaerior::Camera_Component>(morge.id).camera;
	
	event_system->add_event_to_entity(ecs, morge.id, SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {  std::cout << "You just pressed a button, idiot!" << '\n'; });

	
}

void State::Update(const uint64_t& dt)
{
	
	spr_system->update(ecs,dt);

	

	

}

void State::Render()
{


	spr_system->render(ecs,camera);
	
}
	
void State::set_camera(const SDL_Rect& rect) 
{
	camera.set_dimensions(rect.w,rect.h);
	camera.set_position(rect.x, rect.y);
}

void State::handleevents(const SDL_Event& event)
{
	event_system->handle_events(ecs, event);

}
 