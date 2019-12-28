#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../../graphics/rendering/Camera.h"
#include "../../graphics/rendering/objects/Sprite.h"
#include "../../eventhandler/EventHandler.h"
namespace Empaerior
{

	//Some predifined components, feel free not to use them
	struct Print_Component 
	{
		std::string message = "succes";
	};

	struct Position_Component
	{
		int x = 12;
		int y = 10;
	};

	//camera that follows an entity
	struct Camera_Component
	{
		Empaerior::Camera camera;
	};
	

	/*
	This component hold the sprites of an entity
	 *all sprites are always updated(as of yet)
	*/
	struct Sprite_Component
	{
		std::vector<Sprite> sprites;
		//std::vector<Text_Sprite> text_sprites;
	};

	struct Event_Listener_Component
	{
		EventListener event_listener;
	};




}