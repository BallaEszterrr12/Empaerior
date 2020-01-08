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

	void add_event_to_entity(Empaerior::ECS& ecs, const uint64_t& entity_id, const Empaerior::u_s_int& event_type, std::function<void(SDL_Event const&)> function)
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

//SPRITE SYSTEM
#define SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).sprites // the sprites vector
#define POS_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).pos_sprites // the position of the sprite in  the render cache
#define TEXT_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).text_sprites// the text_sprite
#define TEXT_POS_SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).pos_text_sprites // the position of the text_ sprite in  the render cache
#define ORDER ecs.get_component<Empaerior::Sprite_Component>(id).sprites_load//the order in which the sprites were loaded 0 for text_Sprites and 1 for sprites
#define ALLSPRITES ecs.get_component<Empaerior::Sprite_Component>(id).a_sprites//all sprites to be rendered
//An abstraction over the sprite and text_sprite rendering for ease of use
class Sprite_System : public Empaerior::System
{
public:

	//CREATES A SPRITE WITH THE GIVEN PROPERTIES
	//doesn't need to be efficient
	//it return the index of the sprite just in case
	size_t add_sprite(Empaerior::ECS& ecs, const uint64_t& id, 
		
		const SDL_Rect& m_rect, const SDL_Rect& m_tex_rect, const Empaerior::string& tex_path, const unsigned int& m_frames)
	{
		//on the top 
		POS_SPRITES.emplace_back(ORDER.size());
		//put a new sprite in the vector
		SPRITES.push_back({});
		SPRITES[SPRITES.size() - 1].Init(m_rect, m_tex_rect, tex_path, m_frames);

		//put a true in the queue 
		ORDER.emplace_back(true);

		make_render_cache(ecs, id);


		return SPRITES.size() - 1;

	}
	//CREATES A TEXT SPRITE WITH THE GIVEN PROPERTIES
	//returns the index of the text_sprite in a text sprites list
	size_t add_text_sprite(Empaerior::ECS& ecs, const uint64_t& id, 
		const SDL_Rect& m_rect, const Empaerior::string& font_path, const unsigned int& m_size, const Empaerior::string& message, SDL_Color& m_color)
	{
		//the same as add_sprite
		
		TEXT_POS_SPRITES.emplace_back(ORDER.size());

		TEXT_SPRITES.push_back({});
		TEXT_SPRITES[TEXT_SPRITES.size() - 1].Init(m_rect, font_path, m_size, message, m_color);

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
			   //remove the sprites from the container
				SPRITES.erase(SPRITES.begin() + index); 
				//remove from the order
				ORDER.erase(ORDER.begin() + POS_SPRITES[index]);
				//remove from the position container
				POS_SPRITES.erase(POS_SPRITES.begin() + index);
				//make a new render cache based on the new order
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
	//REMOVES THE TEXT_SPRITE BASED ON THE INDEX IN THE CONTAINER OF TEXT_SPRITES , SO INDEX 0 WOULD BE THE FIRST TEXT_SPRITE ADDED TO THE COMPONENT
	void remove_text_sprite(Empaerior::ECS& ecs, const uint64_t& id, const size_t& index)
	{

		try
		{

			if (index < TEXT_SPRITES.size()) {
			//delete from render cache
		 

			//clean the glyphs
			TEXT_SPRITES[index].clean();
			//delete from veectors
			TEXT_SPRITES.erase(TEXT_SPRITES.begin() + index);
			std::cout << TEXT_POS_SPRITES[index] << '\n';
			ORDER.erase(ORDER.begin() + TEXT_POS_SPRITES[index]);
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

	//sets the texture of the sprite at the specified file path
	void set_texture(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& index,const Empaerior::string& file)
	{
		ecs.get_component<Empaerior::Sprite_Component>(id).sprites[index].set_texture(file);
	}
	//sets the color of the sprite at the specified index
	void set_color(Empaerior::ECS& ecs, const Empaerior::u_inter& id,const Empaerior::u_inter& index,const Empaerior::byte r, const Empaerior::byte g, const Empaerior::byte b)
	{
		ecs.get_component<Empaerior::Sprite_Component>(id).sprites[index].set_color(r, g, b);
	}

	void update(Empaerior::ECS& ecs, const Empaerior::u_s_int& dt)
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

	//makes the final vector of pointers that should be iterated throught based on the load order of the sprites & text_sprites
	void make_render_cache(Empaerior::ECS& ecs, const uint64_t& id)
	{
		//CLEAR THE CONTAINERS
		ALLSPRITES.clear();
		TEXT_POS_SPRITES.clear();
		POS_SPRITES.clear();
		//cur_it_spr & cur_it_txt_spr are the current indexes of the added sprite or txt_spr in the render cache
		ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_spr = 0;
		ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_txt_spr = 0;
		for (int i = 0; i < ORDER.size(); i++)
		{
			switch (ORDER[i])
			{
			case true:
				//load the next sprite
				ALLSPRITES.emplace_back(&SPRITES[ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_spr++]);
				POS_SPRITES.emplace_back(ALLSPRITES.size() - 1);
				break;
			case false:
				
				ALLSPRITES.emplace_back(&TEXT_SPRITES[ecs.get_component<Empaerior::Sprite_Component>(id).cur_it_txt_spr++]);
				TEXT_POS_SPRITES.emplace_back(ALLSPRITES.size() - 1);
				break;
			}
		}


	}

};

#undef RENDER_CACHE
#undef POS_SPRITES
#undef SPRITES