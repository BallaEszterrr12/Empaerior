#include <Empaerior.h>
#include <main.h>

//An example of what a application might look like

//a user defined state
class APP_State : public Empaerior::State
{

public:
	
	APP_State()
	{
		
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


		//CREATE Two ENTITY
		morge.id = ecs.create_entity_ID();




		//ADD SOME COMPONENTS TO Them
		ecs.add_component<Empaerior::Camera_Component>(morge.id, Empaerior::Camera_Component{ {0,0,960,800} });
		ecs.add_component<Empaerior::Event_Listener_Component>(morge.id, Empaerior::Event_Listener_Component{});
		ecs.add_component<Empaerior::Sprite_Component>(morge.id, { {},{}, {},{},{} });


		//CREate a Sprite for each
		

		

		//set the camera
		camera = ecs.get_component<Empaerior::Camera_Component>(morge.id).camera;

		Empaerior::Timer timy;
		timy.start();
		//Add a tile map worth of sprites
		
		auto index = spr_system->add_sprite(ecs, morge.id, { { 0,0,960,800},0 }, { 0,0,1000,1000 }, "assets/img.png", 1);
		spr_system->set_color(ecs, morge.id, index, 255, 0, 0);

		 index = spr_system->add_text_sprite(ecs, morge.id, { { 0,100.0f,320,32 } ,0 }, "assets/font.ttf", 32, " The quick blue fuck fdwsiousdfojsdf husdfhu9dfshu8fsdhu8fsdhsdfhuisdfhusfhdu9sfdhu9sdfh9u8sfhd89hsfd9hsdf89", {0,0,255,255});
		



		event_system->add_event_to_entity(ecs, morge.id, SDL_MOUSEBUTTONDOWN,
			[&Ecs = ecs, &Camera =camera, &Spr_system =spr_system,&ID =morge.id](Empaerior::Event& event) 
			
			{
				auto m_pos = Empaerior::Utilities::get_world_mouse_coords(Camera);
				auto index = Spr_system->add_sprite(Ecs, ID, { { m_pos.first,m_pos.second,10,10},0 }, {0,0,1000,1000}, "assets/img.png", 1);
			
			
			}


		);
	

	
	

	}
	void Update(const Empaerior::u_int& dt)override
	{
		//DEBUG CODE, LETS YOU MOVE AROUND THE MAP
		unsigned char const* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_UP])
		{
			Empaerior::Application::cur_state->get_camera().set_dimensions(Empaerior::Application::cur_state->get_camera().rect.w + 12, Empaerior::Application::cur_state->get_camera().rect.h + 10);
		}
		else if (keys[SDL_SCANCODE_DOWN])
		{
			Empaerior::Application::cur_state->get_camera().set_dimensions(Empaerior::Application::cur_state->get_camera().rect.w - 12, Empaerior::Application::cur_state->get_camera().rect.h - 10);
		}
		else if (keys[SDL_SCANCODE_W])
		{
			Empaerior::Application::cur_state->get_camera().set_position(Empaerior::Application::cur_state->get_camera().rect.x, Empaerior::Application::cur_state->get_camera().rect.y - 10);
		}
		else if (keys[SDL_SCANCODE_S])
		{
			Empaerior::Application::cur_state->get_camera().set_position(Empaerior::Application::cur_state->get_camera().rect.x, Empaerior::Application::cur_state->get_camera().rect.y + 10);
		}
		else if (keys[SDL_SCANCODE_A])
		{
			Empaerior::Application::cur_state->get_camera().set_position(Empaerior::Application::cur_state->get_camera().rect.x - 10, Empaerior::Application::cur_state->get_camera().rect.y);
		}
		else if (keys[SDL_SCANCODE_D])
		{
			Empaerior::Application::cur_state->get_camera().set_position(Empaerior::Application::cur_state->get_camera().rect.x + 10, Empaerior::Application::cur_state->get_camera().rect.y);
		}


		//i++;
		//spr_system->set_angle(ecs, norge.id, 0, i);
		
		//UPDATE 
		spr_system->update(ecs, dt);
	}
	
	virtual void Render() override//renders the state
	{
		//RENDER
		spr_system->render(ecs,camera);
		
	
	}
	virtual void handleevents(Empaerior::Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);
	}

private:
	
	std::shared_ptr<Empaerior::Sprite_System> spr_system;
	std::shared_ptr<Empaerior::Event_System> event_system;
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
		states.emplace_back(new APP_State());//add a new state
		//SET THE CURRENTLY RUNNING STATE
		set_state(states[0]);
		//SET THE DIMENSIONS OF THE CAMERA
		SDL_RenderSetLogicalSize(Application::window.renderer, Application::cur_state->get_camera().rect.w, Application::cur_state->get_camera().rect.h);

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


			}

			Empaerior::Asset_Loading::clean_textures();

		}
	}


	void handlevents(Empaerior::Event& event) override
	{
		Empaerior::Application::window.window_listener.handleEvents(event);
		cur_state->handleevents(event);
	}
	void Update(const unsigned int& dt)override
	{
		cur_state->Update(Application::dt);
	}


	void render() override
	{
		cur_state->Render();
	}

	



};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}