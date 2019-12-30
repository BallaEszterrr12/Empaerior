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

class Print_System : public Empaerior::System
{
public:

	void update(Empaerior::ECS& ecs)
	{
		for (auto const& e : entities_id)
		{
			std::cout << ecs.get_component<Empaerior::Print_Component>(e).message << '\n';
		}
	}

};

class Sprite_System : public Empaerior::System
{
public:

	//adds a new sprite to the entity
	//doesn't need to be efficient
	//it return the index of the sprite just in case
	size_t add_sprite(Empaerior::ECS& ecs, const uint64_t& id, Empaerior::Sprite& sprite)
	{
#define SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).sprites
		//search for the entity
		SPRITES.emplace_back(sprite);
		return SPRITES.size() - 1;

#undef SPRITES
	}


	//removes the sprite at a given index
	void remove_sprite(Empaerior::ECS& ecs, const uint64_t& id, const size_t& index)
	{
#define SPRITES ecs.get_component<Empaerior::Sprite_Component>(id).sprites
		try
		{

			if (index < SPRITES.size()) { SPRITES.erase(SPRITES.begin() + index); return; }
			throw E_runtime_exception("Cannot remove sprite: invalid index", __FILE__, __LINE__, __FUNCTION__);

		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
		}
#undef SPRITES
	}

	void update(Empaerior::ECS& ecs, const uint64_t& dt)
	{
		for (auto& e : entities_id)
		{
			for (auto& sprs : ecs.get_component<Empaerior::Sprite_Component>(e).sprites)
			{
				sprs.update(dt);
			}
		}
	}


	//renders all sprites
	void render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
	{
		for (auto& e : entities_id)
		{
			for (auto& sprs : ecs.get_component<Empaerior::Sprite_Component>(e).sprites)
			{
				sprs.draw(camera);
			}
		}
	}

};