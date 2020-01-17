#pragma once
#include <SDL.h>
//thanks to Lazy Foo productions  for making this 
namespace  Empaerior
{

	//The application time based timer
	class Timer
	{
	public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Empaerior::u_int getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

	private:
		//The clock time when the timer started
		Empaerior::u_int mStartTicks;

		//The ticks stored when the timer was paused
		Empaerior::u_int mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};
}