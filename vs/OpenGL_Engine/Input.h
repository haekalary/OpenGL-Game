#pragma once
#include <SDL/SDL.h>
#include <string>
#include <unordered_map>
#include <GLM/glm.hpp>
#include "Settings.h"

using namespace std;

class Input {
public:
	Input();
	~Input();
	// Input Handling
	void PressKey(unsigned int keyID);
	void ReleaseKey(unsigned int keyID);
	void SetMouseCoords(float x, float y);
	// Returns true if the key is held down
	bool GetKeyDown(string name);
	// Returns true if the key was just pressed
	bool GetKeyUp(string name);
	// getters
	glm::vec2 GetMouseCoords() const { return _mouseCoords; }
	// Returns true if the key is held down
	bool GetKey(string name);

	Settings::State GetState();

	void InputMapping(string mappingName, unsigned int keyId);

	void PollInput();
private:
	unordered_map<unsigned int, string> _mapNames;
	unordered_map<string, bool> _keyMap;
	unordered_map<string, bool> _previousKeyMap;
	glm::vec2 _mouseCoords;
	Settings::State state;
};
