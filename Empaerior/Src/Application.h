#pragma once
#include "defines/Defines.h"


#include "assetmanager/AssetManager.h"
#include "graphics/rendering/objects/Sprite.h"
#include "graphics/glyphs/Glyphs.h"

#include "State.h"
#include "graphics/rendering/Window.h"
#include "eventhandler/EventHandler.h"



namespace  Empaerior{
//this is the base application class
//all others applications should inherit from this class
class Application
{
public:
	Application();

	virtual ~Application() {};

	void Init();

    void set_state(Empaerior::State* new_state); // sets a new state to be updated  & rendered 

	//the running function
	virtual void run() = 0;


	virtual void handlevents(const SDL_Event& event);
    virtual void Update(const unsigned int& dt);
	

	virtual void render();


private:



public:
	static Empaerior::State* cur_state;//current state

	static std::vector<Empaerior::State*> states;
	
	static Empaerior::Window window;

	static const Uint32 dt;
	
	static bool is_paused;
	static bool is_running;
	static SDL_Event event;

private:


	


};
	//defined in the application *Thanks to cherno* , 
	//it is intended to create a derived class from Application
	Application* Create_Application();
}