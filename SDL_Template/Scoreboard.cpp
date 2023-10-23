#include "Scoreboard.h"
#include "PhysicsHelper.h"

Scoreboard::Scoreboard() : Scoreboard({230, 230, 230}) {

}

Scoreboard::Scoreboard(SDL_Color color) {
	mColor = color;
	mCurrentScore = "0";

	Score(0);
}

Scoreboard::~Scoreboard() {
	ClearBoard();
}

void Scoreboard::Score(int score, int placement) {
	Score(std::to_string(score), placement);
}

void Scoreboard::Score(std::string str, int placement) {
	if (mCurrentScore != str) {
		ClearBoard();

		mCurrentScore = str;

		unsigned lastIndex = (unsigned)str.length() - 1;

		for (unsigned i = 0; i <= lastIndex; i++) {
			mScore.push_back(new GLTexture(str.substr(i, 1), "GameFont.ttf", FONT_SIZE, mColor));
			mScore[i]->Parent(this);

			if (placement == ScorePlacement::LEFT) {
				mScore[i]->Position(Vector2(FONT_SPACING * (lastIndex - (lastIndex - i)), 0.0f));
			}
			else if (placement == ScorePlacement::CENTER) {
				mScore[i]->Position(Vector2(-FONT_SPACING * (((lastIndex / 2.0f) - 0.5f) - i), 0.0f));
			}
			else if (placement == ScorePlacement::RIGHT) {
				mScore[i]->Position(Vector2(-FONT_SPACING * (lastIndex - i), 0.0f));
			}
		}

		mSize = Vector2(FONT_SPACING * (lastIndex + 1), (float)FONT_SIZE);
	}
}

std::string Scoreboard::Score() {
	return mCurrentScore;
}

Vector2 Scoreboard::Size() {
	return mSize;
}

void Scoreboard::Render() {
	for (auto digit : mScore) {
		digit->Render();
	}
}

void Scoreboard::ClearBoard() {
	for (auto s : mScore) {
		delete s;
	}

	mScore.clear();
}
