#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "../../graphics/rendering/Camera.h"
#include "../../graphics/rendering/objects/Sprite.h"
#include "../../eventhandler/EventHandler.h"

namespace Empaerior
{

	//Some predifined components, feel free not to use them
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
		//the 'containers' for sprtites
		std::vector<Sprite> sprites;
		std::vector<Text_Sprite> text_sprites;
	
		

	
	
		//position of element n in the vector a_sprites
		std::vector<size_t> pos_sprites;
		std::vector<size_t> pos_text_sprites;


		//the order in which the sprites are load
		// 1 - the next sprite is drawn/updated
		// 0 - the next text_sprite is drawn/updated
		std::vector<bool> sprites_load;
		//the container which is meant to be iterated over
		std::vector<Graphic_element*> a_sprites;
		//used to make the a_sprites vector
		size_t cur_it_spr = 0;
		size_t cur_it_txt_spr = 0;
	};

	struct Event_Listener_Component
	{
		EventListener event_listener;
	};




}