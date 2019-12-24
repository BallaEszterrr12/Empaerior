#pragma once

#include "graphics/rendering/objects/Sprite.h"
#include "graphics/rendering/Camera.h"

//entity tests

#include "entitysystem/ECS.h"
#include "entitysystem/system/systems/print_system.h"
#include "entitysystem/system/systems/sprite_system.h"
#include "entitysystem/system/systems/event_system.h"
/*
	A state of the game engine.
*/


class State
{
public:
	State();
	void Update(const uint64_t& dt);
	void Render();//renders the state
	void set_camera(const SDL_Rect& rect);//sets the camera to the specified sdl rect
	void handleevents(const SDL_Event& event);
	Empaerior::Camera& get_camera() { return camera; } // return a shared pointer to the camera

private:
	Empaerior::Camera camera;
	Empaerior::ECS ecs;

	std::shared_ptr<Print_System> printy;
	std::shared_ptr<Sprite_System> spr_system;
	std::shared_ptr<Event_System> event_system;

	Empaerior::Entity morge;
	Empaerior::ComponentManager mangy;
};