#include "PlayScreen.h"
#include "PhysicsHelper.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mTimer = new Timer();
	mRand = Random::Instance();

	mPlayer = Player::Instance();
	mPlayer->Position(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);
	
	
	
	
	




	
}

PlayScreen::~PlayScreen() {
	mEvent = nullptr;
	mInput = nullptr;
	mPlayer = nullptr;
	mRand = nullptr;
	mAsteroids = nullptr;
	
	delete mTimer;
	mTimer = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	
	
}

void PlayScreen::generateAsteroids()
{
	
	for (int i = 0; i < 9; i++)
	{
		if (mAsteroid.size() < 9)
		{
			mAsteroid.push_back(new Asteroids(Asteroids::ObjectType::Asteroid));
			
			float randomY = mRand->RandomRange(0, Graphics::SCREEN_HEIGHT);
			mAsteroid[mAsteroid.size() - 1]->Position(Vector2(Graphics::SCREEN_WIDTH * 1.1f, randomY));
		
		}
		
		
	}
}

void PlayScreen::Update() {
	
	
	generateAsteroids();
	
	
	if (mPlayer != nullptr && mPlayer->WasHit())
	{
		
		mPlayer = nullptr;
		
		

	}

	

	if (mPlayer != nullptr)
	{
		mPlayer->Update();
	}
	
	
	
	for (int i = mAsteroid.size() - 1; i >= 0; i--)
	{
		mAsteroid[i]->Rotate(1.0f);
		if (mAsteroid[i] != nullptr)
		{
			mAsteroid[i]->Update();
			
			if (mAsteroid[i]->WasHit())
			{
				delete mAsteroid[i];
				mAsteroid[i] = nullptr;
				mAsteroid.erase(mAsteroid.begin() + i);

			}
			
		}

		
		
		
	}
	
	

	if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
		mEvent->sendEvent("GameOver");
		
	}
	std::cout << mTimer->TotalTime() << std::endl;
	if(mPlayer == nullptr)
	{
		mTimer->Update();
		//mTimer->TotalTime() == 5.0f;
		if(mTimer->TotalTime() > 5.0f)
		{
			Player::Release();
			mPlayer = Player::Instance();
			mPlayer->Position(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);
			mTimer->Reset();
		}
	}
	
}

void PlayScreen::Render() {
	
	if (mPlayer != nullptr)
	{
		mPlayer->Render();
	}
	
	
	for (int i = 0; i < mAsteroid.size(); i++)
	{
		if(mAsteroid[i] != nullptr)
		{
			mAsteroid[i]->Render();
		}
		
	}
}
