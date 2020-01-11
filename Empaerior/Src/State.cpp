#include "pch.h"
#include "State.h"
#include "Application.h"
#include <SDL.h>
//for testing
#include<iostream>
#include <string>
#include "utilities/Timer.h"



Empaerior::State::State()

{
	
	
	

	
}


	
void Empaerior::State::set_camera(const Empaerior::Rect& rect)
{
	camera.set_dimensions(rect.w,rect.h);
	camera.set_position(rect.x, rect.y);
}


 