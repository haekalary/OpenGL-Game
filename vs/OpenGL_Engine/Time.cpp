#include "Time.h"

unsigned int Time::currentTime = 0, Time::lastFrameTime = 0;
float Time::deltaTime = 0, Time::timeScale = 1, Time::gameTime = 0;

void Time::CalculateTime() {
	gameTime = SDL_GetTicks();

	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastFrameTime) * timeScale;
	lastFrameTime = currentTime;
}
