#pragma once
//Wrappes library functions
#include <SDL.h>
#include "defines/Defines.h"

namespace Empaerior
{
	namespace Render
	{

		//TODO: USe SDL_RenderCopyFEx instead of SDL_RenderCopyEx
		inline void RenderEx(SDL_Renderer* renderer,
			SDL_Texture* texture,
			const Empaerior::Int_Rect* srcrect,
			const Empaerior::Float_Rect* dstrect,
			const double& angle,
			const SDL_Point* center,	
			const SDL_RendererFlip flip)
		{
			SDL_Rect i_dstrect = { int(dstrect->x) , int(dstrect->y)  ,  int(dstrect->w) , int(dstrect->h) };
			SDL_Rect* pdsrect = &i_dstrect;
			


			SDL_RenderCopyEx(renderer, texture, srcrect, pdsrect,angle, center, flip);
		}


	}

}