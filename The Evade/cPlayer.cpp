/*
=================
cPlayer.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayer.h"

void cPlayer::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayer::update(float deltaTime)
{

	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spriteTranslation = (glm::vec2(1000.0f, 0.0f));
		spritePos2D += spriteTranslation * deltaTime;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spriteTranslation = (glm::vec2(-1000.0f, 0.0f));
		spritePos2D += spriteTranslation * deltaTime;

	}
	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new bullet sprite to the vector array
		thePlayerBullets.push_back(new cBullet);
		int numBullets = thePlayerBullets.size() - 1;
		thePlayerBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y - 32));
		thePlayerBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		thePlayerBullets[numBullets]->setTexture(theGameTextures[10]->getTexture());
		thePlayerBullets[numBullets]->setTextureDimensions(theGameTextures[10]->getTWidth(), theGameTextures[10]->getTHeight());
		thePlayerBullets[numBullets]->setSpriteCentre();
		thePlayerBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		thePlayerBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		thePlayerBullets[numBullets]->setActive(true);
		thePlayerBullets[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	PlayerVelocity += spriteVelocityAdd;

	spritePos2D += PlayerVelocity * deltaTime;

	PlayerVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/

	for (vector<cBullet*>::iterator bulletIterartor = thePlayerBullets.begin(); bulletIterartor != thePlayerBullets.end(); ++bulletIterartor)
	{
		(*bulletIterartor)->update(deltaTime);
		for (vector<cMissile*>::iterator MissileIterator = theMissile.begin(); MissileIterator != theMissile.end(); ++MissileIterator)
		{
			if ((*MissileIterator)->collidedWith((*MissileIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*MissileIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
			}
		}
	}

	vector<cBullet*>::iterator bulletIterartor = thePlayerBullets.begin();
	while (bulletIterartor != thePlayerBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = thePlayerBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*bulletIterartor)->render();
			++bulletIterartor;
		}
	}
	setBoundingRect(&boundingRect);
}
/*
=================================================================
  Sets the velocity for the Player
=================================================================
*/
void cPlayer::setPlayerVelocity(glm::vec2 PlayerVel)
{
	PlayerVelocity = PlayerVel;
}
/*
=================================================================
  Gets the Player velocity
=================================================================
*/
glm::vec2 cPlayer::getPlayerVelocity()
{
	return PlayerVelocity;
}
