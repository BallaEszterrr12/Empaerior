#include "pch.h"
#include "State.h"
#include "Application.h"
#include <SDL.h>
//for testing
#include<iostream>
#include <string>
#include "utilities/Timer.h"



Emaperior::State::State()

{
	
	
	

	
}

void Emaperior::State::Update(const Uint32& dt)
{
	


}

void Emaperior::State::Render()
{



	
}
	
void Emaperior::State::set_camera(const SDL_Rect& rect)
{
	camera.set_dimensions(rect.w,rect.h);
	camera.set_position(rect.x, rect.y);
}

void Emaperior::State::handleevents(const SDL_Event& event)
{
	

}
 