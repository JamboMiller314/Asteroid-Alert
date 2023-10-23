#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

#include <iostream>
#include <fstream>
#include <limits>

Player* Player::sInstance = nullptr;

Player* Player::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Player();
	}

	return sInstance;
}

void Player::Release() {
	delete sInstance;
	sInstance = nullptr;
}

bool Player::IgnoreCollisions() {
	return !Active();
}

Player::Player() {
	mEvent = EventManager::Instance();
	mInput = InputManager::Instance();
	mTimer = new Timer();
	mTag = "Player";
	mWasHit = false;

	mTexture = new AnimatedGLTexture("Move.png",49, 64, 104, 64, 5.0f, 1.0f, Animation::Layouts::Horizontal, true);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mXMoveBounds = Vector2(0.0f, Graphics::SCREEN_WIDTH);
	mYMoveBounds = Vector2(0.0f, Graphics::SCREEN_HEIGHT);

	mScore = 0;
	mMoveSpeed = 250.0f;

	loadData();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Player);
}

Player::~Player() {
	mEvent = nullptr;
	mInput = nullptr;

	delete mTimer;
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Player::move() {
	if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
		Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_UP)) {
		Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime());
	}

	if (Position().x < mXMoveBounds.x) {
		Position(Vector2(mXMoveBounds.x, Position().y));
	}
	else if (Position().x > mXMoveBounds.y) {
		Position(Vector2(mXMoveBounds.y, Position().y));
	}

	if (Position().y < mYMoveBounds.x) {
		Position(Vector2(Position().x, mYMoveBounds.x));
	}
	else if (Position().y > mYMoveBounds.y) {
		Position(Vector2(Position().x, mYMoveBounds.y));
	}
}

int Player::score() {
	return mScore;
}

void Player::score(int amount) {
	mScore += amount;
	saveData();
}

void Player::Hit(PhysEntity* other) {
	mWasHit = true;
}

void Player::processEvents() {
	std::vector<std::string> events = mEvent->getEvents();

	for (int i = (int)events.size() - 1; i >= 0; i--) {
		if (events[i] == "Blank") {
			mEvent->removeEvent(i);
		}
	}
}

bool Player::WasHit()
{
	return mWasHit;
}

void Player::loadData() {
	std::ifstream inputFile("data.txt");

	if (inputFile.is_open()) {
		std::string line;

		int lineIndex = 0;

		while (std::getline(inputFile, line)) {
			if (lineIndex == 0) {
				mScore = stoi(line);
			}

			lineIndex++;
		}

		inputFile.close();
	}
}

void Player::saveData() {
	std::ofstream outputFile("data.txt", std::ios::trunc);

	if (outputFile.is_open()) {
		outputFile << mScore << std::endl;

		outputFile.close();
	}
}

void Player::Update() {
	mTimer->Update();

	if (Active()) {
		move();
		mTexture->Update();
	}

	processEvents();

	mTimer->Reset();
}

void Player::Render() {
	if (Active()) {
		mTexture->Render();

		PhysEntity::Render();
	}
}