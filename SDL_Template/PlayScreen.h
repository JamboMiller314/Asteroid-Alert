#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H

#include "EventManager.h"
#include "InputManager.h"
#include "PlayScreenUI.h"
#include "GameEntity.h"
#include "Player.h"
#include "Timer.h"
#include "Asteroids.h"
#include "Random.h"
#include "PhysEntity.h"
#include "PhysicsManager.h"
#include "PhysicsHelper.h"
#include "BoxCollider.h"

class PlayScreen : public GameEntity {
private:
	EventManager* mEvent;
	InputManager* mInput;
	Timer* mTimer;
	Player* mPlayer;
	Random* mRand;
	Asteroids* mAsteroids;
	std::vector<Asteroids*> mAsteroid;
	PlayScreenUI* mSideBar;
	GameEntity* mLivesBar;
	Scoreboard* mTimerDisplay;
	GLTexture* mLives;
	GLTexture* mGameOver;
	GLTexture* mLevelComplete;

	int mPlayerLives;
	bool mWasHit;
	bool mLevelDone;

public:
	PlayScreen();
	~PlayScreen();
	void generateAsteroids();
	void UpdateLives();
	void StartNewLevel();
	void Update() override;
	void Render() override;
};

#endif