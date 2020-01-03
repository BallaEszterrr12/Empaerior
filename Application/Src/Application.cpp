#include <Empaerior.h>
#include <main.h>

//a user defined state
class APP_State : public Emaperior::State
{

public:
	APP_State()
	{
		
        ecs.Init();
		ecs.register_component<Empaerior::Position_Component>();
		ecs.register_component<Empaerior::Camera_Component>();
		ecs.register_component<Empaerior::Sprite_Component>();
		ecs.register_component<Empaerior::Event_Listener_Component>();


		spr_system = ecs.register_system <Sprite_System>();
		event_system = ecs.register_system<Event_System>();




		ecs.add_component_to_system<Empaerior::Sprite_Component, Sprite_System>();
		ecs.add_component_to_system<Empaerior::Event_Listener_Component, Event_System>();



		morge.id = ecs.create_entity_ID();




		ecs.add_component<Empaerior::Position_Component>(morge.id, Empaerior::Position_Component{ 10,10 });
		ecs.add_component<Empaerior::Camera_Component>(morge.id, Empaerior::Camera_Component{ {0,0,960,800} });
		ecs.add_component<Empaerior::Event_Listener_Component>(morge.id, Empaerior::Event_Listener_Component{});

		ecs.add_component<Empaerior::Sprite_Component>(morge.id, { {},{}, {},{},{} });


	
		Empaerior::Sprite borge({ 0 ,0,100,100}, { 0,0,1000,1000 }, "assets/img.png", 1);
		spr_system->add_sprite(ecs, morge.id, borge);
		
	
		camera = ecs.get_component<Empaerior::Camera_Component>(morge.id).camera;

		event_system->add_event_to_entity(ecs, morge.id, SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {  std::cout << "You just pressed a button, idiot!" << '\n'; });

	}

	void Update(const Uint32& dt)override
	{
		spr_system->update(ecs, dt);
	}

	virtual void Render() override//renders the state
	{
		spr_system->render(ecs,camera);
	}
	virtual void handleevents(const SDL_Event& event) override
	{
		event_system->handle_events(ecs, event);
	}

private:

	std::shared_ptr<Sprite_System> spr_system;
	std::shared_ptr<Event_System> event_system;

	Empaerior::Entity morge;
	Empaerior::ComponentManager mangy;
};

//a user defined application
class Test_Aplication : public Empaerior::Application
{
public:
	Test_Aplication()
	{
		std::cout << typeid(this).name() << '\n';
		window.Init("test", 960, 800);

		states.emplace_back(new APP_State());//add a new state
		//second_state = new State();

		set_state(states[0]);

		SDL_RenderSetLogicalSize(Application::window.renderer, Application::cur_state->get_camera().rect.w, Application::cur_state->get_camera().rect.h);

	}

	~Test_Aplication()
	{

	}

};


Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}