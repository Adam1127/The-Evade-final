/*
=================
cPlayer.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _cPlayer_H
#define _cPlayer_H
#include "cSprite.h"
#include "evadegame.h"

class cPlayer : public cSprite
{
private:
	glm::vec2 PlayerVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Player update method
	void setPlayerVelocity(glm::vec2 PlayerVel);   // Sets the velocity for the Player
	glm::vec2 getPlayerVelocity();				 // Gets the Player velocity

};
#endif