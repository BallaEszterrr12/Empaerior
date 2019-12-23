#pragma once
#include <exception>
#include <stdexcept>
#include <string>

#include <iostream>

class E_runtime_exception : public std::exception
{
public:
	
	


	E_runtime_exception(const std::string& what, const std::string& file, const int& line, const std::string& func)
	{
		message = "Exception: " + what + " in " + file +  " function :" + func + " at line " + std::to_string(line);
	}
	
	void print_message()
	{
		std::cout << message << '\n';
	}

	const char* what() const noexcept override 
	{
		return message.c_str();
	}

private:
	std::string message = "";//message
	



};