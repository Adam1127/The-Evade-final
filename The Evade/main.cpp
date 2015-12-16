#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include <iostream>
#include <MMSystem.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "evadegame.h"
#include "cButton.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

	int numberer = 0;
	int timekeep = 0;
	int score = 0;
	// Keeps the score



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\Missile_Sprite1.png", "Images\\Missile_Sprite2.png", "Images\\Missile_Sprite3.png", "Images\\Missile_Sprite4.png", "Images\\Missile_Sprite5.png", "Images\\Missile_Sprite6.png", "Images\\Missile_Sprite7.png", "Images\\Missile_Sprite8.png", "Images\\Missile_Sprite9.png", "Images\\Missile_Sprite10.png", "Images\\Bullet.png"};
	for (int tCount = 0; tCount < 11; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}


	// load game sounds
	// Load Sound
	LPCSTR gameSounds[4] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav", "Audio/BGMusic.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);
	theSoundMgr->add("BK_Music", gameSounds[3]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	string StringScore = "";

	// Create vector array of textures

	//Created the 10 Missiles 
	//Sets their spawn and movement
	// spwan on a randon x and 0 on the y
	//Sets the Missile velocity

	

	// Create vector array of textures
	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images/StartBK.jpg", "Images/BG_Image_1024x768.png", "Images/EndBK.jpg" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgList[1]->getTexture());
	spriteBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround spriteStartBkgd;
	spriteStartBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteStartBkgd.setTexture(textureBkgList[0]->getTexture());
	spriteStartBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround spriteEndBkgd;
	spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteEndBkgd.setTexture(textureBkgList[2]->getTexture());
	spriteEndBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());

	//Creates the background textures
	//Selects the texture to be used
	//Sets the texture and gets its dimentions.

	cTexture PlayerTxt;
	PlayerTxt.createTexture("Images\\Player_Sprite.png");
	cPlayer PlayerSprite;
	PlayerSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	PlayerSprite.setSpritePos(glm::vec2(512.0f, 736.0f));
	PlayerSprite.setTexture(PlayerTxt.getTexture());
	PlayerSprite.setTextureDimensions(PlayerTxt.getTWidth(), PlayerTxt.getTHeight());
	PlayerSprite.setSpriteCentre();
	PlayerSprite.setPlayerVelocity(glm::vec2(0.0f, 0.0f));

	//Creates the Player texture
	//Selects the texture to be used
	//Sets the textures start position
	//Sets the texture and gets its dimentions.
	//Sets the sprites centre point and velocity

	string outputMsg;
	string strMsg[] = { "The world is in danger!", "Shoot the Missiles to gain points.", "The Evade", "Thanks for playing!", "Did you get all the missiles?" };

	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Buttons/exitBtn.png", "Images/Buttons/instructionsBtn.png", "Images/Buttons/loadBtn.png", "Images/Buttons/playBtn.png", "Images/Buttons/saveBtn.png", "Images/Buttons/settingsBtn.png" };
	for (int tCount = 0; tCount < 6; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}

	cButton exitButton;
	exitButton.attachInputMgr(theInputMgr);
	exitButton.setTexture(btnTextureList[0]->getTexture());
	exitButton.setTextureDimensions(btnTextureList[0]->getTWidth(), btnTextureList[0]->getTHeight());

	cButton playButton;
	playButton.attachInputMgr(theInputMgr);
	playButton.setTexture(btnTextureList[3]->getTexture());
	playButton.setTextureDimensions(btnTextureList[3]->getTWidth(), btnTextureList[3]->getTHeight());

	// Attach sound manager to Player sprite

	PlayerSprite.attachSoundMgr(theSoundMgr);


	gameState theGameState = MENU;
	btnTypes theBtnType = EXIT;

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		switch (theGameState)
		{
		case MENU:

			spriteStartBkgd.render();

			theFontMgr->getFont("Space")->printText("The Evade By Adam McLaughlin", FTPoint(50.0f, -30.0f, 0.0f));
			theFontMgr->getFont("Space")->printText("The world is in Danger!!!", FTPoint(100, -100, 0.0f));
			theFontMgr->getFont("Space")->printText("Controls:", FTPoint(600, -590, 0.0f));
			theFontMgr->getFont("Space")->printText("Left Arrow: Move Left", FTPoint(600, -610, 0.0f));
			theFontMgr->getFont("Space")->printText("Right Arrow: Move Right", FTPoint(600, -630, 0.0f));
			theFontMgr->getFont("Space")->printText("Space Bar: Shoot", FTPoint(600, -650, 0.0f));

			playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 375.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();

			if (exitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			break;
		case PLAYING:

			spriteBkgd.render();

			PlayerSprite.update(elapsedTime);
			{
				vector<cMissile*>::iterator MissileIterator = theMissile.begin();

				while (MissileIterator != theMissile.end())
				{
					if ((*MissileIterator)->isActive() == false)
					{
						MissileIterator = theMissile.erase(MissileIterator);
						numberer--;
						score = score++;
					}
					else if (PlayerSprite.collidedWith(PlayerSprite.getBoundingRect(), (*MissileIterator)->getBoundingRect()))
					{
						theGameState = playButton.update(theGameState, MENU);
					}
					else
					{
						(*MissileIterator)->update(elapsedTime);
						(*MissileIterator)->render();

						++MissileIterator;
					}
				}
			}

			PlayerSprite.render();

			theFontMgr->getFont("Space")->printText("The Evade", FTPoint(0.0f, -1.0f, 0.0f));
			StringScore = "Score: " + std::to_string(score);
			theFontMgr->getFont("Space")->printText(StringScore.c_str(), FTPoint(840.0f, -1.0f, 0.0f));



			timekeep++;

				if (timekeep > 50)
				{
					theMissile.push_back(new cMissile);
					theMissile[numberer]->setSpritePos(glm::vec2(windowWidth / (rand() % 5 + 1), 0));
					theMissile[numberer]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), 25));
					int randMissile = rand() % 4;
					theMissile[numberer]->setTexture(theGameTextures[randMissile]->getTexture());
					theMissile[numberer]->setTextureDimensions(theGameTextures[randMissile]->getTWidth(), theGameTextures[randMissile]->getTHeight());
					theMissile[numberer]->setSpriteCentre();
					theMissile[numberer]->setMissileVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
					theMissile[numberer]->setActive(true);
					theMissile[numberer]->setMdlRadius();

					numberer++;

					timekeep = 0;
				}

			// render button and reset clicked to false

			exitButton.setSpritePos(glm::vec2(850.0f, 32.0f));
			exitButton.render();
			theGameState = exitButton.update(theGameState, END);

			outputMsg = strMsg[2];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(10, 15, 0.0f));

			break;
		case END:
			spriteEndBkgd.render();

			playButton.setClicked(false);
			exitButton.setClicked(false);

			playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 375.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();

			outputMsg = strMsg[2];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(10, -15, 0.0f));
			outputMsg = strMsg[3];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, -100, 0.0f));
			outputMsg = strMsg[4];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, -150, 0.0f));
			if (exitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}

			break;
		}

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
