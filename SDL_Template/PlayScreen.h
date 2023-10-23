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

	bool mWasHit;
	

public:
	PlayScreen();
	~PlayScreen();
	void generateAsteroids();
	
	void Update() override;
	void Render() override;
};

#endif