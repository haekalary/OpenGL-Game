#ifndef SCRATCHENGINE_H
#define SCRATCHENGINE_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Input.h"
#include "Time.h"

using namespace std;
using namespace glm;
using namespace Settings;

namespace Engine {
	class ScratchEngine
	{
	public:
		ScratchEngine();
		~ScratchEngine();

		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		
		State state;
		Input input;

	protected:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		unsigned int GetScreenHeight();
		unsigned int GetScreenWidth();
	
	private:
		unsigned int screenWidth, screenHeight, last = 0, _fps = 0, fps = 0;
		float targetFrameTime = 0;
		void GetFPS();
		void Err(string errorString);
		void LimitFPS();
		void PrintFPS();
	};
}
#endif

