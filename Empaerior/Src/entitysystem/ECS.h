#pragma once
#include "Entity.h"
#include "components/ComponentManager.h"
#include "system/system.h"


/*The ECS is heaviley isnpired by AUSTIN MORLAN's implementation , but it has a bit more functionality and ease of use. It's a bit more loose than his*/

namespace Empaerior
{
	class ECS
	{
	public:
		void Init()
		{
			component_manager = std::make_unique<Empaerior::ComponentManager>();
			entity_manager = std::make_unique<Empaerior::EnityManager>();
			system_manager = std::make_unique<Empaerior::SystemManager>();

		}
		void Destroy()
		{
			component_manager.reset();
			entity_manager.reset();
			system_manager.reset();
		}



		//assigns a new id for an entity
		uint64_t create_entity_ID()
		{
			return entity_manager->add_Entity();
		}
		//destroy entity
		void destroy_entity(const uint64_t& id)
		{
			entity_manager->delete_entity(id);
			component_manager->OnEntityDestroyed(id);
			system_manager->OnEntityDestroy(id);
			

		}
		//get entity signature
		std::vector<bool> get_entity_signature(const uint64_t& entity_id)
		{
			return entity_manager->get_signature(entity_id);
		}




		template<typename T>
		void register_component()
		{
			component_manager->register_component<T>();
		}

		template<typename T>
		void add_component(const uint64_t& entity_id, T component)
		{
			//add the component
			component_manager->add_component<T>(entity_id, component);


			//modify the signature to match the new addition
			std::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			uint64_t component_type = component_manager->get_component_id<T>();
			//while the vector of signature doesn't have elements until the current component add 0 to the signature
			while (e_signature.size() <= component_type)
			{
				e_signature.emplace_back(0);
			}
			//add the new signature
			e_signature[component_type] = 1;
			entity_manager->set_signature(entity_id, e_signature);
			system_manager->OnEntitySignatureChange(entity_id, e_signature);
		}

		template <typename T>
		void remove_component(const uint64_t& entity_id)
		{
			component_manager->remove_component<T>(entity_id); \
				std::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			uint64_t component_type = component_manager->get_component_id<T>();
			e_signature[component_type] = 0;
			system_manager->OnEntitySignatureChange(entity_id, e_signature);
		}

		template <typename T>
		T& get_component(const uint64_t& entity_id)
		{
			return component_manager->get_component<T>(entity_id);
		}

		template <typename T>
		uint64_t get_component_id()
		{
			return component_manager->get_component_id<T>();
		}


		template <typename T>
		std::shared_ptr<T> register_system()
		{
			return system_manager->register_system<T>();
		}

		//sets the signature of T
		template <typename T>
		void set_system_signature(std::vector<bool>& signature)
		{
			system_manager->set_signature<T>(signature);
		}

		//gets the signature of T
		template <typename T>
		std::vector<bool> get_system_signature()
		{
			return system_manager->get_system_signature<T>();
		}

		//add the component <comp> to the system <sys>
		//this can be done without template, but it's good as is now
		template<typename comp , typename sys>
		void add_component_to_system()
		{
			//get the current signature of sys
			std::vector<bool> signature = get_system_signature<sys>();

			//get the id of the component
			uint64_t component_id = get_component_id<comp>();
			//modify the signature to fit the new component
			while (signature.size() <= component_id)
			{
				signature.emplace_back(0);
			}
			//mark the component as being a part of the system
			signature[component_id] = 1;
			//set the new signature
			set_system_signature<sys>(signature);

		}



	private:	
		std::unique_ptr<Empaerior::ComponentManager> component_manager;
		std::unique_ptr<Empaerior::EnityManager> entity_manager;
		std::unique_ptr<Empaerior::SystemManager> system_manager;
	};

}