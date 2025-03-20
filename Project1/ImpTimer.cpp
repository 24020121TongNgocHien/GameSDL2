#include"ImpTimer.h"

ImpTimer::ImpTimer() {
	startTick = 0;
	pauseTick = 0;
	isPause = false;
	isStarted = false;

}

ImpTimer::~ImpTimer(){}

void ImpTimer::start(){
	isStarted = true;
	isPause = false;
	startTick = SDL_GetTicks();
}

void ImpTimer::stop() {
	isStarted = false;
	isPause = false;
}

void ImpTimer::pause() {
	if (isStarted == true && isPause == false) {
		isPause = true;
		pauseTick = SDL_GetTicks() - startTick;
	}

}

void ImpTimer::unpause() {
	if (isPause == true) {
		isPause = false;
		startTick = SDL_GetTicks() - pauseTick;
		pauseTick = 0;
	}
}

int ImpTimer::getTicks() {
	if (isStarted == true) {
		if (isPause == true) {
			return pauseTick;
		}
		else return SDL_GetTicks() - startTick;
	}
	return 0;
}

bool ImpTimer::is_Start() {
	return isStarted;
}

bool ImpTimer::is_Pause() {
	return isPause;
}