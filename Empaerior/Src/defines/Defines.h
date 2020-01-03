#pragma once
#include <memory>
#include <iostream>
//Platform detection

#ifdef _WIN32
	#ifdef _WIN64//if 64 bit 
	//add 64 flag
		
	#else // if 32 bit
		#pragma warning  "x86 is not a actively tested"	//x86 flag
	#endif // _WIN64

#elif __APPLE__
	#error "No Apple platforms are supported"
#elif __linux__
	#error "Linus is not a supported platform yet"

#endif // __WIN32

//platform specific linking
#ifdef  EMPAERIOR_WINDOWS

	#define EMPAERIOR_API __declspec(dllexport)
#elif EMPAERIOR_LINUX
	#error "Platform is not yet supported"
#else 
	#error "Platform is not supported"

#endif