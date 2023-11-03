#ifndef  __ASTEROIDS_H
#define __ASTEROIDS_H



#include "InputManager.h"
#include "EventManager.h"
#include "PhysEntity.h"
#include "GLTexture.h"
#include "Timer.h"
#include "AnimatedGLTexture.h"
#include "Random.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "PhysicsHelper.h"

using namespace SDLFramework;

class Asteroids : public PhysEntity {
public:
	 enum class ObjectType {Asteroid, Planet};

protected:
	ObjectType mObjectType;
private:
	
	EventManager* mEvent;
	InputManager* mInput;
	Random* mRand;
	Timer* mTimer;

	GLTexture* mAsteroids;

	Vector2 mXMoveBounds;
	Vector2 mYMoveBounds;

	float mMoveSpeed;
	
	bool mWasHit;

	

public:
	
	bool WasHit();
	Asteroids(ObjectType type);
	~Asteroids();

	

	
	
	ObjectType getObjectType();
	void Hit(PhysEntity* other) override;

	void Respawn();

	
	

	void Update();
	void Render();
};













#endif 
