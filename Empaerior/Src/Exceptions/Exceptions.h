#pragma once
#include <exception>
#include <stdexcept>
#include <string>

#include <iostream>

#ifdef EMP_USE_LOGS
	#include "debugging/Log.h"
#endif // EMP_USE_LOGS


class E_runtime_exception : public std::exception
{
public:
	
	


	E_runtime_exception(const std::string& what, const std::string& file, const int& line, const std::string& func)
	{
		message = "Exception: " + what + " in " + file +  " function :" + func + " at line " + std::to_string(line) + '\n';
	}
	
	void print_message()
	{
	#ifdef EMP_USE_LOGS
		ENGINE_ERROR(message);
	#endif
	}

	const char* what() const noexcept override 
	{
		return message.c_str();
	}

private:
	std::string message = "";//message
	



};