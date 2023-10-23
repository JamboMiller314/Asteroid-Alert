#include "Asteroids.h"



Asteroids::Asteroids(ObjectType type)

{
	mRand = Random::Instance();
	mTimer = new Timer();

	mObjectType = type;
	mWasHit = false;

	if (mObjectType == ObjectType::Asteroid)
	{
		
		mAsteroids = new GLTexture("Asteroid.png", 66, 194, 58, 61, true);
		mAsteroids->Parent(this);
		mAsteroids->Position(Vec2_Zero);
		
		AddCollider(new BoxCollider(mAsteroids->ScaledDimensions()));

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Asteroid);
	}
	
	
	

	mMoveSpeed = 300.0f;

	


}

Asteroids::~Asteroids()
{
	delete mAsteroids;
	mAsteroids = nullptr;
	delete mTimer;
	mTimer = nullptr;

}

bool Asteroids::WasHit()
{
	return mWasHit;
}

Asteroids::ObjectType Asteroids::getObjectType()
{
	return mObjectType;
}

void Asteroids::Respawn()
{
	float randomY = mRand->RandomRange(0, Graphics::SCREEN_HEIGHT);
	Position(Vector2(Graphics::SCREEN_WIDTH * 1.1f, randomY));
	
}


void Asteroids::Update()

{
	
	mTimer->Update();

	if(Active())
	{
		
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		
		
	}
	if (Position().x < - 650)
	{
		Respawn();
	}

	mTimer->Reset();
}

void Asteroids::Render()
{
	mAsteroids->Render();

	PhysEntity::Render();
}

void Asteroids::Hit(PhysEntity* other)
{
	mWasHit = true;
}
