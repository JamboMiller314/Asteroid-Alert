#include "PlayScreen.h"
#include "PhysicsHelper.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();
	mEvent = EventManager::Instance();
	mTimer = new Timer();
	mRand = Random::Instance();

	mPlayerLives = 3;

	mPlayer = Player::Instance();
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT / 2);
	
	

	mLives = new GLTexture("Lives ", "GameFont.ttf", 26, {238, 30, 238}, true);
	mLives->Parent(this);
	mLives->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.9f);
	
	
	UpdateLives();

	mLevelComplete = new GLTexture("Level 1 Complete! ", "GameFont.ttf", 32, { 238, 30, 238 }, true);
	mLevelComplete->Parent(this);
	mLevelComplete->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mTimerDisplay = new Scoreboard({ 238, 30, 238 }); 
	mTimerDisplay->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 20)); 
	
}

PlayScreen::~PlayScreen() {
	mEvent = nullptr;
	mInput = nullptr;
	mPlayer = nullptr;
	mRand = nullptr;
	mAsteroids = nullptr;
	
	delete mTimer;
	mTimer = nullptr;
	
	delete mLives;
	mLives = nullptr;
	
	
	delete mTimerDisplay;
	mTimerDisplay = nullptr;
	delete mLevelComplete;
	mLevelComplete = nullptr;
}


void PlayScreen::UpdateLives()
{
	std::string livesText = "Lives: " + std::to_string(mPlayerLives);
	delete mLives;
	mLives = new GLTexture(livesText, "GameFont.ttf", 26, { 238, 30, 238 }, true);
	mLives->Parent(this);
	mLives->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.9f);
}

void PlayScreen::generateAsteroids()
{
	
	for (int i = 0; i < 6; i++)
	{
		if (mAsteroid.size() < 9)
		{
			mAsteroid.push_back(new Asteroids(Asteroids::ObjectType::Asteroid));
			
			float randomY = mRand->RandomRange(0, Graphics::SCREEN_HEIGHT);
			mAsteroid[mAsteroid.size() - 1]->Position(Vector2(Graphics::SCREEN_WIDTH * 1.1f, randomY));
		
		}
		
		
	}
}

void PlayScreen::StartNewLevel()
{

	//mPlayer = Player::Instance();
	//mPlayer->Position(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);



	
	mPlayerLives = 4;
	Active(true);
	generateAsteroids();


	UpdateLives();
	
}

void PlayScreen::Update() {
	if (mGameOver != nullptr)
	{
		mGameOver->Update();
	}
	
	mLives->Update();
	mTimer->Update();
	float timeElapsed = mTimer->TotalTime();
	
	mTimerDisplay->Score(timeElapsed);
	
	if (std::stof(mTimerDisplay->Score()) == 100.0f)
	{
		Active(false);
		mTimerDisplay->Active(false);
		
	}
	generateAsteroids();
	
	
	if (mPlayer != nullptr && mPlayer->WasHit())
	{
		
		mPlayerLives--;
		UpdateLives();
		mPlayer = nullptr;
		
		

		if (mPlayerLives == 0)
		{
			Active(false);
			
			
			mGameOver = new GLTexture("Game Over :(\n Press Space to try again. ", "GameFont.ttf", 32, { 238, 30, 238 }, true);
			mGameOver->Parent(this);
			mGameOver->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
			
			
		}

	}
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) && mPlayerLives == 0)
	{
		
		delete mGameOver;
		mGameOver = nullptr;
		StartNewLevel();

	}
	
	if (Active())
	{
		
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

	}	

	

		
		
		
	
	
	

	if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
		mEvent->sendEvent("GameOver");
		
	}
	
	if(mPlayer == nullptr && mPlayerLives > 0)
	{
		mTimer->Update();
		
		if(mTimer->TotalTime() >= 3.0f)
		{
			Player::Release();
			mPlayer = Player::Instance();
			mPlayer->Position(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT / 2);
			
		}
		
	}
	if (mPlayerLives == 0)
	{
		mTimer->Reset();
	}
}

void PlayScreen::Render() {
	if (mLevelDone == true)
	{
		mLevelComplete->Render();
	}
	mTimerDisplay->Render();
	if (std::stof(mTimerDisplay->Score()) == 100.0f)
	{
		mLevelComplete->Render();


	}

	if (mGameOver != nullptr)
	{
		mGameOver->Render();
	}
	
	mLives->Render();
	
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
