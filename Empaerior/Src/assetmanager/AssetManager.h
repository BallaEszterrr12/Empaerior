#pragma once
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "../graphics/glyphs/Glyphs.h"






namespace Empaerior::Asset_Loading
{

	//texture
	 std::shared_ptr<SDL_Texture>  load_texture(const Empaerior::string& tex_path);
	//font
	 TTF_Font* load_font(const Empaerior::string& font_path, const Empaerior::s_int& size);

	//sound   
	 void play_sound(const Empaerior::string& sound_path);
	 void set_volume(const Empaerior::s_int n_volume);






	//clear ununsed
	 void clean_textures();
	//clear all
	 void clear_textures();
	 void clear_fonts();
	 void clear_sounds();
	



	 void reset_assets();



};