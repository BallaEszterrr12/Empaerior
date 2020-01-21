#pragma once

#include "../../../exceptions/Exceptions.h"

#include "../../ECS.h"
#include "../../system/system.h"
#include "../../components/Component.h"
#include "../../../graphics/rendering/objects/Sprite.h"
#include "eventhandler/EventHandler.h"


namespace Empaerior
{
	class Event_System : public Empaerior::System
	{
	public:

		void add_event_to_entity(Empaerior::ECS& ecs, const uint64_t& entity_id, const Empaerior::u_int& event_type, std::function<void(Empaerior::Event&)> function)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener

			EVENTLISTENER.register_event(event_type, function);

#undef EVENTLISTENER
		}


		void handle_events(Empaerior::ECS& ecs,Empaerior::Event& event)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(*Iterator).event_listener
			//REVERSE ITERATOR
			std::set<Empaerior::u_inter>::reverse_iterator Iterator = entities_id.rbegin();
			//ITERATING THROUGH THE ENTITIES IN REVERSE
			while (Iterator != entities_id.rend() && !Empaerior::is_event_handled(event))
			{
				EVENTLISTENER.handleEvents(event);
				Iterator++;
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

			const Empaerior::Rect& m_rect, const Empaerior::Int_Rect& m_tex_rect, const Empaerior::string& tex_path, const unsigned int& m_frames)
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
			const Empaerior::Rect& m_rect, const Empaerior::string& font_path, const unsigned int& m_size, const Empaerior::string& message, Empaerior::Color m_color)
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
		void set_texture(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& index, const Empaerior::string& file)
		{
			try {
				if (index < SPRITES.size())
				{
					ecs.get_component<Empaerior::Sprite_Component>(id).sprites[index].set_texture(file);
				}
				else
				{
					throw E_runtime_exception("Cannot set the texture of the sprite, index " + std::to_string(index) + "  is invalid", __FILE__, __LINE__, __FUNCTION__);
				}
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}
		}
		//sets the color of the sprite at the specified index
		void set_color_blend(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& index, const Empaerior::byte r, const Empaerior::byte g, const Empaerior::byte b)
		{
			try {
				if (index < SPRITES.size())
				{

					ecs.get_component<Empaerior::Sprite_Component>(id).sprites[index].set_color_blend(r, g, b);
				}
				else
				{
					throw E_runtime_exception("Cannot set the color of the sprite, index " + std::to_string(index) + "  is invalid", __FILE__, __LINE__, __FUNCTION__);
				}

			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}

		}

		void set_angle(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& index, const Empaerior::fl_point& angle)
		{

			try {
				if (index < SPRITES.size())
				{

					ecs.get_component<Empaerior::Sprite_Component>(id).sprites[index].set_angle(angle);
				}
				else
				{
					throw E_runtime_exception("Cannot set the color of the sprite, index " + std::to_string(index) + "  is invalid", __FILE__, __LINE__, __FUNCTION__);
				}

			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}

		}

		void update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
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
			for (auto& id : entities_id)
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

#undef ALLSPRITES
#undef ORDER
#undef TEXT_POS_SPRITES
#undef TEXT_SPRITES
#undef POS_SPRITES
#undef SPRITES



	class T_E_System : public Empaerior::System
	{
	public:
		using Timed_Function = std::function<void()>;

		//Adds a function to the container
		void add_function(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& time, Timed_Function function)
		{
			//adds the necessary data in the containers
			ecs.get_component<T_E_Component>(id).time.emplace_back(time);
			ecs.get_component<T_E_Component>(id).functions.emplace_back(function);
			ecs.get_component<T_E_Component>(id).elapsed_time.emplace_back(0);

		}

	//iterates throught the container and executes the functions for which enough time has passed
#define component ecs.get_component<T_E_Component>(id)
		void Update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
		{
			for (auto& id : entities_id)
			{
				for (Empaerior::u_inter i = 0; i < component.functions.size(); i++)
				{
					component.elapsed_time[i] += dt;
					//if enought time has passed,execute the function and delete it from the registry
					if (component.elapsed_time[i] >= component.time[i])
					{
						//call function
						component.functions[i]();
						//erase all
						component.elapsed_time.erase(component.elapsed_time.begin() + i);
						component.time.erase(component.time.begin() + i);
						component.functions.erase(component.functions.begin() + i);

					}

				}

			}

		}
#undef component


	};
}