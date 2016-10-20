#include <SDL.h>
#include <stdio.h>

class Timer{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void resume();
	
		bool isStarted();
		bool isPaused();
	
		Uint32 getTicks();
	private:
		Uint32 startedTime;
		Uint32 pausedTime;
		bool started;
		bool paused;
};