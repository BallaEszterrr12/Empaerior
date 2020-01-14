#pragma once

#include <string>
#include <SDL.h>

//Platform detection
#ifdef _WIN32
	#ifdef _WIN64//if 64 bit 
	//add 64 flag
		#define EMPAERIOR_64BIT
	#else // if 32 bit
		#define EMPAERIOR_32BIT
		#pragma warning  "x86 is not a actively tested"	//x86 flag
	
#endif // _WIN64

#elif __APPLE__
	#error "No Apple platforms are supported"
#elif __linux__
	#error "Linux is not a supported platform yet"
#else
	#error "platform not supported yet"

#endif 

//Log usage

#if defined(EMPAERIOR_DEBUG) || defined(EMPAERIOR_RELEASE)

#define EMP_USE_LOGS

#endif


//Variable defines // just in case

namespace Empaerior
{
	


	//BASIC TYPES
	//one byte interger
	using byte = uint8_t;
	//type compatible with SDL
	using u_s_int = uint32_t;
	using s_int = int32_t;
	//the type the engine works with 
	using u_inter = uint64_t;
	using inter = int64_t;
	using boole = bool;
	using ch = char;
	using fl_point = double;


	//OTHER TYPES
	//value tuple // fore small types
	template <typename T, typename Y>
	using v_pair = std::pair<T, Y>;
	//string definition
	using string = std::string;
	//Dimensions Rectangle (without rotation)
	using D_Rect = SDL_Rect;

	struct Rect
	{

		Empaerior::D_Rect dimensions;
		Empaerior::fl_point angle;

	};


	using Color = SDL_Color;
}