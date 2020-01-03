#pragma once



#include "Application.h"
#include "State.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <SDL_mixer.h>
#include <SDL_ttf.h> 

#include "assetmanager/AssetManager.h"
#include "graphics/glyphs/Glyphs.h"
#include "SDLwrappers/Ptr_Wrappers.h"
#include "SDLwrappers/SDL_Wrappers.h"

#include "entitysystem/ECS.h"
#include "entitysystem/system/systems/Systems.h"
#include "entitysystem/components/Component.h"

#include "graphics/rendering/Window.h"
#include "graphics/rendering/Camera.h"
#include "graphics/rendering/objects/Sprite.h"

#include "eventhandler/EventHandler.h"