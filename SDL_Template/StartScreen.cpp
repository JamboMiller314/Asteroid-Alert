#include "StartScreen.h"

StartScreen::StartScreen() {
	mLogo = new GLTexture("Asteroid Alert", "GameFont.ttf", 48, {230, 30, 230});
	mLogo->Parent(this);
	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);

	mStart = new Button("Start", new GLTexture("START", "GameFont.ttf", 48, { 230, 30, 230 }));
	mStart->Parent(this);
	mStart->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f + 35.0f);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mBottomBar->Parent(this);

	mNamco = new GLTexture("James Miller", "GameFont.ttf", 20, { 230, 30, 230 });
	mNamco->Parent(mBottomBar);
	mNamco->Position(Vec2_Zero);
}

StartScreen::~StartScreen() {
	delete mLogo;
	mLogo = nullptr;

	delete mStart;
	mStart = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mNamco = nullptr;
}

void StartScreen::Update() {
	mStart->Update();
}

void StartScreen::Render() {
	mLogo->Render();
	mStart->Render();
	mNamco->Render();
}