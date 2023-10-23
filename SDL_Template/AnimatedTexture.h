#ifndef __ANIMATEDTEXTURE_H
#define __ANIMATEDTEXTURE_H

#include "Texture.h"
#include "Timer.h"

namespace SDLFramework {
	struct Animation {
		enum class WrapModes { Once = 0, Loop = 1 } wrapMode;
		enum class Layouts { Horizontal = 0, Vertical = 1 } layout;

		unsigned startX, startY;

		unsigned frameCount;

		float speed;
		float timePerFrame;
		float frameTimer;

		bool done;
	};

	class AnimatedTexture :
		public Texture
	{
	protected:
		Timer * mTimer;
		
		virtual void RunAnimation();

	private:
		Animation mAnim;

	public:
		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts layout, bool managed = true);
		~AnimatedTexture();

		void SetWrapMode(Animation::WrapModes mode);

		virtual void ResetAnimation();
		bool IsAnimating();

		void Update();
	};
}

#endif