#pragma once
#ifndef TIME_H
#define TIME_H

#include <SDL/SDL.h>

static class Time {
public :
	static float deltaTime;
	static float timeScale;
	static float gameTime;
	static void CalculateTime();

private :
	static unsigned int lastFrameTime, currentTime;
};

#endif