#pragma once
#include "defines/Defines.h"


#include "assetmanager/AssetManager.h"
#include "graphics/rendering/objects/Sprite.h"
#include "graphics/glyphs/Glyphs.h"

#include "State.h"
#include "graphics/rendering/Window.h"
#include "eventhandler/EventHandler.h"



namespace  Empaerior{
class Application
{
public:
	Application();

	virtual ~Application() {};

	void Init();

    void set_state(State* new_state); // sets a new state to be updated  & rendered 

	


	void handlevents(const SDL_Event& event);
    void Update(const unsigned int& dt);
	

	 void render();


private:



public:
	static State* cur_state;//current state

	static std::vector<State*> states;
	
	static Empaerior::Window window;

	static const Uint32 dt;
	
	static bool is_paused;
	static bool is_running;


private:


	


};
	//defined in the application *Thanks to cherno*
	Application* Create_Application();
}