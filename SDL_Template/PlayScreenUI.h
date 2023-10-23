#ifndef __PLAYSCREENUI_H
#define __PLAYSCREENUI_H

#include "GameEntity.h"
#include "Scoreboard.h"
#include "ScrollBar.h"
#include "Player.h"

using namespace SDLFramework;

class PlayScreenUI : public GameEntity {
private:
	Player* mPlayer;

	GameEntity* mDisplay;
	Scoreboard* mDisplayScore;
	ScrollBar* mScrollBar;

public:
	PlayScreenUI();
	~PlayScreenUI();

	void Update() override;
	void Render() override;
};

#endif