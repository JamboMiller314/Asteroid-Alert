#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H

#include "InputManager.h"
#include "GameEntity.h"
#include "GLTexture.h"
#include "Button.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {
private:
	GLTexture* mLogo;

	Button* mStart;

	GameEntity* mBottomBar;
	GLTexture* mNamco;

public:
	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;
};
#endif