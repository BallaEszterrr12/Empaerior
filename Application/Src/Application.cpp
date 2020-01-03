#include <Empaerior.h>
#include <main.h>

class Test_Aplication : public Empaerior::Application
{
public:
	Test_Aplication()
	{
		std::cout << typeid(this).name() << '\n';
		window.Init("test", 960, 800);

		states.emplace_back(new State());//add a new state
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