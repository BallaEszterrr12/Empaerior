#include <Empaerior.h>
#include <main.h>

//An example of what a application might look like

//a user defined state
class APP_State1 : public Empaerior::State
{

public:
	
	APP_State1()
	{

		Empaerior::Window_Functions::change_window_name(Empaerior::Application::window, "Testing stuff");
		
		//INITIALIZE THE ECS
		ecs.Init();

		//set the camera
		camera = { 0,0,960,800 };

		//REGISTER SOME COMPONENTS
		ecs.register_component<Empaerior::Camera_Component>();
		ecs.register_component<Empaerior::Sprite_Component>();
		ecs.register_component<Empaerior::Event_Listener_Component>();

		//CREATE SOME SYSTEMS TO USE THE COMPONENTS
		spr_system = ecs.register_system <Empaerior::Sprite_System>();
		event_system = ecs.register_system<Empaerior::Event_System>();
		//SPECIFIY WHAT TYPES OF COMPONENT EACH SYSTEM NEEDS
		ecs.add_component_to_system<Empaerior::Sprite_Component, Empaerior::Sprite_System>();
		ecs.add_component_to_system<Empaerior::Event_Listener_Component, Empaerior::Event_System>();


		//Create an entity
		morge.id = ecs.create_entity_ID();

		ecs.add_component<Empaerior::Sprite_Component>(morge.id, {});
		spr_system->add_sprite(ecs, morge.id, { 0,0,960,800 }, { 0,0,1,1 }, "assets/img.png", 1);
		spr_system->add_text_sprite(ecs, morge.id, { 0,0,960,800 }, "assets/font.ttf", 100, "THIS IS THE FIRST STATE", {255,255,0});

	
	

	}
	void Update(const Empaerior::u_int& dt)override
	{
		//DEBUG CODE, LETS YOU MOVE AROUND THE MAP



		unsigned char const* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_UP])
		{
			camera.set_dimensions(camera.rect.w + 12, camera.rect.h + 10);
		}
		else if (keys[SDL_SCANCODE_DOWN])
		{
			camera.set_dimensions(camera.rect.w - 12, camera.rect.h - 10);
		}
		else if (keys[SDL_SCANCODE_W])
		{
			camera.set_position(camera.rect.x, camera.rect.y - 10);
		}
		else if (keys[SDL_SCANCODE_S])
		{
			camera.set_position(camera.rect.x, camera.rect.y + 10);
		}
		else if (keys[SDL_SCANCODE_A])
		{
			camera.set_position(camera.rect.x - 10, camera.rect.y);
		}
		else if (keys[SDL_SCANCODE_D])
		{
			camera.set_position(camera.rect.x + 10, camera.rect.y);
		}


		//i++;
		//spr_system->set_angle(ecs, norge.id, 0, i);
		
		//UPDATE 
		spr_system->update(ecs, dt);
	}
	
	virtual void Render() override//renders the state
	{
	
		SDL_RenderSetLogicalSize(Empaerior::Application::window.renderer, camera.rect.w, camera.rect.h);
		//RENDER
		spr_system->render(ecs,camera);
		
	
	}
	virtual void handleevents(Empaerior::Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);
	}


	std::shared_ptr<Empaerior::Sprite_System> spr_system;
	std::shared_ptr<Empaerior::Event_System> event_system;


private:
	

	int i = 0;
	Empaerior::Entity morge;
	Empaerior::Entity norge;

};

class APP_State2 : public Empaerior::State
{

public:

	APP_State2()
	{

		Empaerior::Window_Functions::change_window_name(Empaerior::Application::window, "Testing stuff");


		//set camera
		camera = { 0,0,960,800 };

		//INITIALIZE THE ECS
		ecs.Init();

		//REGISTER SOME COMPONENTS
		ecs.register_component<Empaerior::Camera_Component>();
		ecs.register_component<Empaerior::Sprite_Component>();
		ecs.register_component<Empaerior::Event_Listener_Component>();

		//CREATE SOME SYSTEMS TO USE THE COMPONENTS
		spr_system = ecs.register_system <Empaerior::Sprite_System>();
		event_system = ecs.register_system<Empaerior::Event_System>();
		//SPECIFIY WHAT TYPES OF COMPONENT EACH SYSTEM NEEDS
		ecs.add_component_to_system<Empaerior::Sprite_Component, Empaerior::Sprite_System>();
		ecs.add_component_to_system<Empaerior::Event_Listener_Component, Empaerior::Event_System>();




		//Create an entity
		morge.id = ecs.create_entity_ID();

		ecs.add_component<Empaerior::Sprite_Component>(morge.id, {});


	
		spr_system->add_text_sprite(ecs, morge.id, { 0,0,960,800 }, "assets/font.ttf", 100, "THIS IS THE SECOND STATE", { 255,255,0 });




	}
	void Update(const Empaerior::u_int& dt)override
	{
		


		//i++;
		//spr_system->set_angle(ecs, norge.id, 0, i);

		//UPDATE 
		spr_system->update(ecs, dt);
	}

	virtual void Render() override//renders the state
	{


		//RENDER
		SDL_RenderSetLogicalSize(Empaerior::Application::window.renderer, camera.rect.w, camera.rect.h);
		spr_system->render(ecs, camera);



	}
	virtual void handleevents(Empaerior::Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);
	}


	std::shared_ptr<Empaerior::Sprite_System> spr_system;
	std::shared_ptr<Empaerior::Event_System> event_system;
private:


	int i = 0;
	Empaerior::Entity morge;
	Empaerior::Entity norge;

};


//a user defined application
class Test_Aplication : public Empaerior::Application
{
public:
	Test_Aplication()
	{
		//CREATE A WINDOW
		window.Init("test", 960, 800);
		//CREATE A NEW STATE
		main_state = push_state(new APP_State1());
		//make the state active
		activate_state(main_state);
		//SET THE DIMENSIONS OF THE CAMERA
		SDL_RenderSetLogicalSize(Application::window.renderer, states[active_states[0]]->get_camera().rect.w, states[active_states[0]]->get_camera().rect.h);
		//ADD AN OVERLAY STATE
		
	//	pause_state(main_state);

		second_state = push_state(new APP_State2());

	

		activate_state(second_state);

	
	

	}

	~Test_Aplication()
	{

	}

	//the main loop

	void run() override
	{
		//GAME LOOP
		Empaerior::u_int framestart = 0;
		Empaerior::u_int frametime = 0;
		Empaerior::u_int currentime = 0;
		Empaerior::u_int acumulator = 0;

		while (Empaerior::Application::is_running)
		{



			//poll what event is registered
			while (SDL_PollEvent(&Empaerior::Application::event.event)) {
				//make it not handled yet
				Empaerior::Application::event.is_handled = false;
				//handle it
				handlevents(Empaerior::Application::event);

			}
			if (!Empaerior::Application::is_paused)
			{


				framestart = SDL_GetTicks();
				frametime = framestart - currentime;

				if (frametime > 25) frametime = 25; //if too many frames are skipped

				currentime = framestart;
				acumulator += frametime;



				while (acumulator >= Empaerior::Application::dt)
				{


					//update 

					Update(Empaerior::Application::dt);

					acumulator -= Empaerior::Application::dt;



				}


				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);


				Empaerior::Application::window.clear();
				render();

				Empaerior::Application::window.render();
				

				//refresh the application
				refresh();

			}

			Empaerior::Asset_Loading::clean_textures();

		}
	}


	void handlevents(Empaerior::Event& event) override
	{

		Empaerior::Application::window.window_listener.handleEvents(event);
		for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
		{
			states[active_states[i]]->handleevents(event);
		}
	}
	void Update(const unsigned int& dt)override
	{
		
		for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
		{
			states[active_states[i]]->Update(dt);
		}
	}


	void render() override
	{
	
		for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
		{
			states[active_states[i]]->Render();
		}
	}

	Empaerior::s_int main_state;
	Empaerior::s_int second_state;


};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}