#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
//define flags
#define sdl 1
#define sdl_image 1<<1
#define sdl_ttf 1<<2
#define sdl_mix 1<<3

namespace SDLW {

	inline uint16_t Init()
	{
		uint16_t flags = 0;
		
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			flags |= sdl;
		}
		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		{
			flags |= sdl_image;
		}
		if (TTF_Init() < 0)
		{
			flags |= sdl_ttf;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			flags |=sdl_mix;
		}


		return flags;
	}
	inline void Quit()
	{

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

	}

}
