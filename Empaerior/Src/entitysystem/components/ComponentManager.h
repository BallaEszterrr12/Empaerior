#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

#include "../../exceptions/Exceptions.h"
#include "../Entity.h"
#include "Component.h"
//thanks to Austin Morlan for providing a ECS template
namespace Empaerior
{
	//virtual cointainer for polymorphism
	class VContainer
	{
	public:
		virtual ~VContainer() {};
		virtual void OnEntityDestroyed(const uint64_t& entity_id) noexcept {};
	};


	//contains..components
	template <typename  T>
	class ComponentContainer : public VContainer
	{
	public:
		virtual ~ComponentContainer() {};

		//update a specific component
		void add_component(const uint64_t& entity_id,T component)
		{
			try {
				//if the entity does have this type of component throw exception
				if (componenttoentity.find(entity_id) != componenttoentity.end())
				{
					throw E_runtime_exception("Cannot add component: the entity already has this type of component: " + Empaerior::string(typeid(T).name()),__FILE__,__LINE__, __FUNCTION__);
				}



				//if there isn't any free space,create one
				if (free_index.empty())
				{
					components.push_back(component);
					entitytocomponent[entity_id] = components.size() - 1;
					componenttoentity[components.size() - 1] = entity_id;

				}
				else//just take an unused component
				{
					components[free_index.front()] = component;
					entitytocomponent[entity_id] = free_index.front();
					componenttoentity[free_index.front()] = entity_id;
					free_index.pop();


				}
			}
			catch(E_runtime_exception & e)
			{
				e.print_message();

			}




		}

		T& get_component(const uint64_t& entity_id)
		{

			try
			{
				if (entitytocomponent.find(entity_id) == entitytocomponent.end())
				{
					throw E_runtime_exception("Cannot get component : entity doesn't own the specified type of component: " + Empaerior::string(typeid(T).name()), __FILE__, __LINE__, __FUNCTION__);
				}
				
				
				return components[entitytocomponent[entity_id]];


			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
				//something else should happen here, but I can't think what
				throw;
			
				
			}

		}

		
		void remove_component(const uint64_t& entity_id)
		{
			try
			{
				//if the entity doesn't have this type of component throw exception
				if (componenttoentity.find(entity_id) == componenttoentity.end())
				{
					//I don't know why it's giving a warning, only here as I have multiple blocks like this, not a big deal
					E_runtime_exception("Cannot delete component: the entity doesn't have this type of component : " + Empaerior::string(typeid(T).name()), __FILE__, __LINE__, __FUNCTION__);
				}
				
				//get the index of the removed entity
				uint64_t removed_index = entitytocomponent[entity_id];


				//add the id to the list of unused ids
				free_index.push(removed_index);



				//delete the entity from the registries
				entitytocomponent.erase(entity_id);
				componenttoentity.erase(removed_index);

				//the data is still there until is overwritten by a new component
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}


		}

		//deletes the 
		void OnEntityDestroyed(const uint64_t& entity_id)  noexcept  override//this function never throws exception because not finding the component of the entity is  intended
		{
			//there is already an exception to point if something happenes
			remove_component(entity_id);
			//add more relevant code

		}



	private:
		//components vector
		std::vector<T> components;

		//the next component's index to be used
		std::queue<uint64_t> free_index;


		//lookup the component of a entity
		std::unordered_map<uint64_t, uint64_t> entitytocomponent;
		//lookup the entity of a component
		std::unordered_map<uint64_t, uint64_t> componenttoentity;





	};
	

	
	//handles all components
	class ComponentManager {

	public:
		//register a component
		//Note: add_component already registers a coponentthat has not been use before
		//this function is not really useful at this point
		template<typename T>
		void register_component()
		{
			try {
				const char* componentid = typeid(T).name();
				//and it does what it looks it should do

				//check if the container type is registered
				if (component_type.find(componentid) == component_type.end())
				{
					//if the type of the container is not registered ,register it
					component_type.insert({ componentid,top_component_type++ });

					component_containers.insert({ componentid,std::make_shared<ComponentContainer<T>>() });

				}
				else
				{
					throw E_runtime_exception("Component " + Empaerior::string(componentid) + " already registered", __FILE__, __LINE__, __FUNCTION__);
				}
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}

		}



		template <typename T>
		void add_component(const uint64_t& entity_id, T& component)
		{
		   
			get_container<T>()->add_component(entity_id,std::move(component));
	
		}
		template <typename T>
		void remove_component(const Entity& entity)
		{

			get_container<T>()->remove_component(entity);

		}
		template<typename T>
		T& get_component(const uint64_t& entity_id)
		{
			return get_container<T>()->get_component(entity_id);
		}

		//gets the id of a component in the manager
		template <typename T>
		uint64_t get_component_id()
		{
			const char* component_name = typeid(T).name();
			try
			{
				if (component_type.find(component_name) == component_type.end())
				{
					throw E_runtime_exception("Cannot fetch component id" + Empaerior::string(component_name) + " : invalid component", __FILE__, __LINE__, __FUNCTION__);
				}
				return component_type[component_name];

			}
			catch (E_runtime_exception& e)
			{
				e.print_message();
				return -1;
			}


		}


		//iterate throught all components of the entity and delete them
		void OnEntityDestroyed(const uint64_t& entity_id)
		{
			for (auto const& i : component_containers)
			{
				auto const& component = i.second;
				component->OnEntityDestroyed(entity_id);
			}

		}



	private:

		//gets the container of the specified type
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> get_container()
		{
		
				//(apparently this is possible)
				
				const char* componentid = typeid(T).name();
				//and it does what it looks it should do

				//check if the container type is registered
				if (component_type.find(componentid) == component_type.end())
				{
					//if the type of the container is not registered ,register it
					component_type.insert({ componentid,top_component_type++ });

					component_containers.insert({ componentid,std::make_shared<ComponentContainer<T>>() });

				}
				return std::static_pointer_cast<ComponentContainer<T>>(component_containers[componentid]);
				

		}
		
		





	private:
	
		//the largest id
		uint64_t top_component_type = 0;
		//type -> id
		std::unordered_map<const char*, uint64_t> component_type;

		//contains 
		std::unordered_map<const char*, std::shared_ptr<Empaerior::VContainer>> component_containers;


	};


}