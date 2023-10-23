#include "PlayScreenUI.h"

PlayScreenUI::PlayScreenUI() {
	mPlayer = Player::Instance();

	mDisplay = new GameEntity();
	mDisplay->Parent(this);
	mDisplay->Position(Vector2(Vec2_Zero));

	mDisplayScore = new Scoreboard({ 255, 0, 0 });
	mDisplayScore->Parent(mDisplay);
	mDisplayScore->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 60.0f));

	mScrollBar = new ScrollBar(Vector2(250.0f, 1200.0f), 5);
	mScrollBar->Parent(this);
	mScrollBar->Position(Vector2(Graphics::SCREEN_WIDTH - 125.0f, Graphics::SCREEN_HEIGHT * 0.5f));
}

PlayScreenUI::~PlayScreenUI() {
	mPlayer = nullptr;

	delete mDisplay;
	mDisplay = nullptr;
	delete mDisplayScore;
	mDisplayScore = nullptr;
	delete mScrollBar;
	mScrollBar = nullptr;
}

void PlayScreenUI::Update() {
	mDisplayScore->Score(mPlayer->score());
	mScrollBar->Update();
}

void PlayScreenUI::Render() {
	mDisplayScore->Render();
	mScrollBar->Render();
}