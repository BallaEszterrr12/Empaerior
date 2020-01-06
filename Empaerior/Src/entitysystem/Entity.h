#pragma once
#include "defines/Defines.h"
#include "components/Component.h"
#include <vector>
#include <algorithm>
#include "../exceptions/Exceptions.h"
#include<iostream>
//thanks to Austin Morlan for providing a ECS template

namespace Empaerior
{
	
	//I could probably get away with just havind an id as an entity,but I prefer this way, consider I might need to add something else here someday
	class Entity
	{
	public:

	
		uint64_t id = 0;
	
	};


	class EnityManager
	{
	public:

		//takes a freed or makes a new one if there's no id
		uint64_t add_Entity()
		{
			
			return get_id();
		}


		void delete_entity(const uint64_t & id)//deletes an entity ,removes all components and puts its id in the queue
		{
			try
			{
				if (id > lowest_unallocatedid )
				{
					throw E_runtime_exception("Invalid id for deletion : id doesn't exist", __FILE__, __LINE__, __FUNCTION__);

				} 
				//if the id appears in the delted entities
				else if(std::binary_search(freed_id.begin(),freed_id.end(),id))
				{
					throw E_runtime_exception("Invalid id deletion : id is not a valid entity", __FILE__, __LINE__, __FUNCTION__);
				
				}

				//***delete entity's component's (not implemented yet) ***//
				//
				//
				//.................
				entity_signature[id].clear();
				//push the freed id into the queue

				freed_id.push_back(id);
				//the vector is always sorted in order to check if id apears in it using binary search
				std::sort(freed_id.begin(), freed_id.end());
			}
			catch(E_runtime_exception& e)
			{
				e.print_message();
			}


		}

		//setsa the signature
		void set_signature(const uint64_t& id, const std::vector<bool>& signature)
		{
			try
			{
				if (id > lowest_unallocatedid)
				{
					throw E_runtime_exception("Cannot set id signature  : id doesn't exist", __FILE__, __LINE__, __FUNCTION__);

				}
				//if the id appears in the delted entities
				else if (std::binary_search(freed_id.begin(), freed_id.end(), id))
				{
					throw E_runtime_exception("Cannot set id signature : id is not a valid entity", __FILE__, __LINE__, __FUNCTION__);

				}
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}

			entity_signature[id] = signature;
		}

		//gets the signature
		std::vector<bool> get_signature(const uint64_t& id)
		{

			try
			{
				if (id > lowest_unallocatedid)
				{
					throw E_runtime_exception("Cannot fetch entity signature : id doesn't exist", __FILE__, __LINE__,__FUNCTION__);

				}
				//if the id appears in the delted entities
				else if (std::binary_search(freed_id.begin(), freed_id.end(), id))
				{
					throw E_runtime_exception("Cannot fetch entity signature : id is not a valid entity", __FILE__, __LINE__, __FUNCTION__);

				}
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}
			return entity_signature[id];

		}


		//gets an id that is not used
		uint64_t get_id()
		{
			//if there isn't any idin the queue,create a new one and a new entry in the signature list
			if (freed_id.empty())
			{

				entity_signature.emplace_back(std::vector<bool>());
				return lowest_unallocatedid++;


			}
			else
			{
				//take the id from   the front of the queue
				uint64_t id = freed_id.front();
				//popit
				freed_id.pop_back();
				return  id;

			}
		}
		

	private:
		//ids that had once an entity but now are 
		std::vector<uint64_t> freed_id;

		//stores the signature of an entity with the id as key
		std::vector<std::vector<bool>> entity_signature;

		//the lowest unallocated id that has not interacted with
		uint64_t lowest_unallocatedid = 0;
	};


	

}