#include "Include/Timer.h"

Timer::Timer(){
	startedTime = 0;
	pausedTime = 0;
	started = false;
	paused = false;
}

void Timer::start(){
	started = true;
	paused = false;
	startedTime = SDL_GetTicks();
	pausedTime = 0;
}

void Timer::stop(){
	started = false;
	paused = false;
	startedTime = 0;
	pausedTime = 0;	
}

void Timer::pause(){
	if(started == true && paused == false){
		paused = true;
		pausedTime = SDL_GetTicks() - startedTime;
		startedTime = 0;
	}
}

void Timer::resume(){
	if(started == true && paused == true){
		paused = false;
		startedTime = SDL_GetTicks() - pausedTime;
		pausedTime = 0;
	}
}

bool Timer::isStarted() {
	return started;
}
bool Timer::isPaused() {
	return paused;
}

Uint32 Timer::getTicks(){
	Uint32 ret = 0;
	if(started){
		if(paused){
			ret = pausedTime;	
		}
		else{
			ret = SDL_GetTicks() - startedTime;	
		}
	}
	return ret;
}