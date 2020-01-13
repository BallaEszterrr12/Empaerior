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


		//CREATE AN ENTITY
		morge.id = ecs.create_entity_ID();




		//ADD SOME COMPONENTS TO IT
		ecs.add_component<Empaerior::Camera_Component>(morge.id, Empaerior::Camera_Component{ {0,0,960,800} });
		ecs.add_component<Empaerior::Event_Listener_Component>(morge.id, Empaerior::Event_Listener_Component{});
		ecs.add_component<Empaerior::Sprite_Component>(morge.id, { {},{}, {},{},{} });


		//CREATE A COLOR
		Empaerior::Color colo = { 77,55,255,255 };

		//ADD A TIMER FOR BENCHMARKING
		Empaerior::Timer timy;
		//START THE TIMER
		timy.start();
		//CREATE n^2 sprites 	
		for (int i = 0 ; i < 4;i++)
		{
			for (int j = 0; j < 4; j++)
			{
			
				//LOG WHAT SPRITE IS CURRENTLY LOADING
				APP_INFO("Generating the " + std::to_string(i) + ' ' + std::to_string(j) + " element");
				//ADD A SPRITE
				auto index = spr_system->add_sprite(ecs, morge.id, { i * 32,j * 32,32,32 }, { 0,0,960,800 }, "assets/img.png", 1);
				//SET IT'S Color to Random
				spr_system->set_color(ecs, morge.id, index, std::rand() % 255 + 1 , std::rand() % 255 + 1 , std::rand() % 255 + 1);

				
			}

		}
		//LOG THE TIME IT TOOK
		APP_INFO("GENERATING 1000 sprites took" + std::to_string(timy.getTicks()));
		
		//SET THE CAMERA
		camera = ecs.get_component<Empaerior::Camera_Component>(morge.id).camera;

		//ADD AN EVENT 
		event_system->add_event_to_entity(ecs, morge.id, SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) { APP_INFO("A button has been pressed"); });

	}

	void Update(const Empaerior::u_s_int& dt)override
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

		
		//UPDATE 
		spr_system->update(ecs, dt);
	}
	
	virtual void Render() override//renders the state
	{
		//RENDER
		spr_system->render(ecs,camera);
	
	}
	virtual void handleevents(const SDL_Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);
	}

private:
	
	std::shared_ptr<Empaerior::Sprite_System> spr_system;
	std::shared_ptr<Empaerior::Event_System> event_system;

	Empaerior::Entity morge;
	Empaerior::ComponentManager mangy;
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
		Empaerior::u_s_int framestart = 0;
		Empaerior::u_s_int frametime = 0;
		Empaerior::u_s_int currentime = 0;
		Empaerior::u_s_int acumulator = 0;

		while (Empaerior::Application::is_running)
		{



	
			while (SDL_PollEvent(&Empaerior::Application::event)) {

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


	void handlevents(const SDL_Event& event) override
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