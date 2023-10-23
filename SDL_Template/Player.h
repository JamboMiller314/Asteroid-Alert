#ifndef __PLAYER_H
#define __PLAYER_H

#include "InputManager.h"
#include "EventManager.h"
#include "PhysEntity.h"
#include "GLTexture.h"
#include "Timer.h"
#include "AnimatedGLTexture.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	static Player* sInstance;

	EventManager* mEvent;
	InputManager* mInput;
	Timer* mTimer;

	AnimatedGLTexture* mTexture;

	Vector2 mXMoveBounds;
	Vector2 mYMoveBounds;

	float mMoveSpeed;
	int mScore;

	bool IgnoreCollisions() override;
	bool mWasHit;

public:
	static Player* Instance();
	static void Release();

	Player();
	~Player();

	void move();

	int score();
	void score(int value);

	void Hit(PhysEntity* other) override;

	void processEvents();
	bool WasHit();

	void loadData();
	void saveData();

	void Update();
	void Render();
};

#endif