/*
=================
cMissile.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _cMissile_H
#define _cMissile_H
#include "cSprite.h"

class cMissile : public cSprite
{
private:
	glm::vec2 MissileVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Player update method
	void setMissileVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the Player
	glm::vec2 getMissileVelocity();				 // Gets the Player velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif