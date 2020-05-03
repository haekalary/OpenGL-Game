#include "ScratchEngine.h"

using namespace Engine;

ScratchEngine::ScratchEngine()
{
}


ScratchEngine::~ScratchEngine()
{

}

void ScratchEngine::Start(string windowTitle, unsigned int screenWidth, unsigned int screenHeight, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale)
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->timeScale = timeScale;

	if (targetFrameRate > 0) {
		targetFrameTime = 1000.0f / targetFrameRate;
	}


	Uint32 flags = SDL_WINDOW_OPENGL;

	if (WindowFlag::EXCLUSIVE_FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WindowFlag::FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (WindowFlag::BORDERLESS == windowFlag) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Setup SDL Window
	SDL_Window* window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (window == nullptr) {
		Err("Failed to create SDL window!");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		Err("Failed to create SDL_GL context!");
	}

	//Set up glew (optional but recommended)
	GLenum glewStat = glewInit();
	if (glewStat != GLEW_OK) {
		Err("Failed to initialize glew!");
	}

	//Set VSYNC
	SDL_GL_SetSwapInterval(vsync);

	this->state = State::RUNNING;

	Init();

	// Init delta time calculation
	last = SDL_GetTicks();

	//Will loop until we set _gameState to EXIT
	while (State::RUNNING == state) {
		float deltaTime = GetDeltaTime();
		GetFPS();
		PollInput();
		Update(deltaTime);
		Render();
		SDL_GL_SwapWindow(window);
		LimitFPS();
		PrintFPS();
	}

}


float ScratchEngine::GetDeltaTime()
{
	unsigned int time = SDL_GetTicks();
	unsigned int delta = time - lastFrame;
	lastFrame = time;

	return delta * timeScale;
}

void ScratchEngine::GetFPS()
{
	if (SDL_GetTicks() - last > 1000) {
		fps = _fps;
		_fps = 0;
		last += 1000;
	}
	_fps++;
}

void ScratchEngine::PrintFPS() {
	//print only once every 60 frames
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 60) {
		cout << "FPS: " << fps << endl;
		frameCounter = 0;
	}
}

void ScratchEngine::OpenGameController()
{
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(0))
		{
			controller = SDL_GameControllerOpen(0);
			if (controller != nullptr)cout << "Game Controller is Detected" << endl;
		}
	}
}

void ScratchEngine::CloseGameController()
{
	if (controller != nullptr) {
		SDL_GameControllerClose(0);
		cout << "Game Controller is Removed" << endl;
	}
}

// -------------- Input Handling --------------------

void ScratchEngine::PollInput()
{
	SDL_Event evt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			SetMouseCoords((float)evt.motion.x, (float)evt.motion.y);
			break;
		case SDL_KEYDOWN:
			PressKey(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			ReleaseKey(evt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			PressKey(evt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			ReleaseKey(evt.button.button);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			OpenGameController();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			CloseGameController();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			PressKey(evt.cbutton.button);
			break;
		case SDL_CONTROLLERBUTTONUP:
			ReleaseKey(evt.cbutton.button);
			break;
		}
	}
}

void ScratchEngine::PressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = true;
	}

}

void ScratchEngine::ReleaseKey(unsigned int keyID) {
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = false;
	}
}

void ScratchEngine::SetMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool ScratchEngine::IsKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(name);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool ScratchEngine::IsKeyUp(string name) {
	// Check if it is pressed this frame, and wasn't pressed last frame
	if (IsKeyDown(name) == true && WasKeyDown(name) == false) {
		return true;
	}
	return false;
}

bool ScratchEngine::WasKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(name);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

void ScratchEngine::InputMapping(string mappingName, unsigned int keyId)
{
	_mapNames.insert(pair<unsigned int, string>(keyId, mappingName));
}

//Prints out an error message and exits the game
void ScratchEngine::Err(string errorString)
{
	cout << errorString << endl;
	SDL_Quit();
	exit(1);
}

void ScratchEngine::LimitFPS()
{
	//Limit the FPS to the max FPS
	SDL_Delay((Uint32)(targetFrameTime));

}

unsigned int ScratchEngine::GetScreenHeight() {
	return this->screenHeight;
}

unsigned int ScratchEngine::GetScreenWidth() {
	return this->screenWidth;
}



