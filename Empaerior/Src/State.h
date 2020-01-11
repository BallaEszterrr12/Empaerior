#pragma once

#include "graphics/rendering/objects/Sprite.h"
#include "graphics/rendering/Camera.h"

//entity tests

#include "entitysystem/ECS.h"
#include "entitysystem/system/systems/Systems.h"


#include "defines/Defines.h"
/*
	A state of the engine.
*/

namespace Empaerior {
	class  State
	{
	public:
		State();
		virtual ~State() {

		};

		virtual void Update(const Empaerior::u_s_int& dt) = 0;
		virtual void Render() = 0 ;//renders the state
		virtual void handleevents(const SDL_Event& event) = 0;

		void set_camera(const Empaerior::Rect& rect);//sets the camera to the specified sdl rect
		
		Empaerior::Camera& get_camera() { return camera; } // return the camera

	protected:
		Empaerior::Camera camera;
		Empaerior::ECS ecs;


	
	};
}