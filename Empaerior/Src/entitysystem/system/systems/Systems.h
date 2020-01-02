#pragma once

#include "../../../exceptions/Exceptions.h"

#include "../../ECS.h"
#include "../../system/system.h"
#include "../../components/Component.h"
#include "../../../graphics/rendering/objects/Sprite.h"
#include "eventhandler/EventHandler.h"

class Event_System : public Empaerior::System
{
public:

	void add_event_to_entity(Empaerior::ECS& ecs, const uint64_t& entity_id, const Uint32& event_type, std::function<void(SDL_Event const&)> function)
	{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener

		EVENTLISTENER.register_event(event_type, function);

#undef EVENTLISTENER
	}


	void handle_events(Empaerior::ECS& ecs, const SDL_Event& event)
	{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener

		for (auto& entity_id : entities_id)
		{
			EVENTLISTENER.handleEvents(event);
		}

#undef EVENTLISTENER

	}



};


#define SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).sprites
#define POS_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).pos_sprites
#define TEXT_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).text_sprites
#define TEXT_POS_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).pos_text_sprites
#define ORDER ecs.get_component<Empaerior::Sprite_Component>(id).sprites_load
#define ALLSPRITES ecs.get_component<Empaerior::Sprite_Component>(id).a_sprites
class Sprite_System : public Empaerior::System
{
public:

	//adds a new sprite to the entity
	//doesn't need to be efficient
	//it return the index of the sprite just in case
	size_t add_sprite(Empaerior::ECS& ecs, const uint64_t& id, Empaerior::Sprite sprite)
	{

		POS_SPRITES.emplace_back(SPRITES.size());
		SPRITES.emplace_back(std::move(sprite));
		//put a true in the queue 
		ORDER.emplace_back(true);

		make_render_cache(ecs, id);


		return SPRITES.size() - 1;

	}

	size_t add_text_sprite(Empaerior::ECS& ecs, const uint64_t& id, Empaerior::Text_Sprite& sprite)
	{


		TEXT_POS_SPRITES.emplace_back(TEXT_SPRITES.size());
		TEXT_SPRITES.emplace_back(sprite);
		ORDER.emplace_back(false);
		make_render_cache(ecs, id);
	
		return TEXT_SPRITES.size() - 1;


	}


	//removes the sprite at a given index
	void remove_sprite(Empaerior::ECS& ecs, const uint64_t& id, const size_t& index)
	{

		try
		{

			if (index < SPRITES.size()) { 
				//remove the sprites from the chache
				ORDER.erase(ORDER.begin() + POS_SPRITES[index]);  
				//remove the sprites from the container
				SPRITES.erase(SPRITES.begin() + index); 
				POS_SPRITES.erase(POS_SPRITES.begin() + index); 
				make_render_cache(ecs, id);
				return;
			}
			throw E_runtime_exception("Cannot remove sprite: invalid index", __FILE__, __LINE__, __FUNCTION__);

		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
		}

	}

	void remove_text_sprite(Empaerior::ECS& ecs, const uint64_t& id, const size_t& index)
	{

		try
		{

			if (index < TEXT_SPRITES.size()) {
			ORDER.erase(ORDER.begin() + TEXT_POS_SPRITES[index]); 
			TEXT_SPRITES.erase(TEXT_SPRITES.begin() + index);
			TEXT_POS_SPRITES.erase(TEXT_POS_SPRITES.begin() + index);
			make_render_cache(ecs, id);
			return;
			}
			throw E_runtime_exception("Cannot remove sprite: invalid index", __FILE__, __LINE__, __FUNCTION__);

		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
		}

	}



	void update(Empaerior::ECS& ecs, const Uint32& dt)
	{
		for (auto& id : entities_id)
		{

			for (int i = 0; i < ALLSPRITES.size(); i++)
			{
				ALLSPRITES[i]->update(dt);
			}

		}


	}


	//renders all sprites
	void render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
	{
		for(auto & id : entities_id)
			{

				for (int i = 0; i < ALLSPRITES.size(); i++)
				{
					ALLSPRITES[i]->draw(camera);
				}

			}
	}

	//mazkes the final vector of pointers that should be iterated throught based on the load order of the sprites & text_sprites
	void make_render_cache(Empaerior::ECS& ecs, const uint64_t& id)
	{
		ALLSPRITES.clear();
		ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_spr = 0;
		ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_txt_spr = 0;
		for (int i = 0; i < ORDER.size(); i++)
		{
			
			switch (ORDER[i])
			{
			case true:
				//load the next sprite
				ALLSPRITES.emplace_back(&SPRITES[ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_spr++]);
				break;
			case false:
				ALLSPRITES.emplace_back(&TEXT_SPRITES[ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_txt_spr++]);
				break;
			}
		}


	}

};

#undef RENDER_CACHE
#undef POS_SPRITES
#undef SPRITES