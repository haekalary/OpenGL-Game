#ifndef DEBUG_H
#define DEBUG_H

#include <SDL/SDL.h>
#include <string>
#include <iostream>

using namespace std;

class Debug {
public :
	static void Err(string errorString) {
		cout << errorString << endl;
		SDL_Quit();
		exit(1);
	}
};

#endif