#ifndef TURNBASEDGAME_H
#define TURNBASEDGAME_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "ScratchEngine.h"
#include "Shader.h"
#include "GameObject.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80

using namespace glm;

class TurnBasedGame :
	public Engine::ScratchEngine
{
public:
	TurnBasedGame();
	~TurnBasedGame();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	float frame_width = 0, frame_height = 0;
	GameObject player;
private:
	float frame_dur = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	GLuint texture;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	void BuildPlayerSprite();
	void DrawPlayerSprite();
	void UpdateSpriteAnim(float deltaTime);
	void ControlPlayerSprite(float deltaTime);
};
#endif

