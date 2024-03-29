#ifndef __GLTEXTURE_H
#define __GLTEXTURE_H

#include "Texture.h"

#include <glew.h>

namespace SDLFramework {
	class GLTexture : public Texture {
	public:
		GLuint ID;
		GLuint WrapS, WrapT;
		GLuint FilterMag, FilterMin;

		int Mode;
		bool Rendererd;
		void* Data;

		SDL_RendererFlip Flip;
		SDL_Surface* Surface;

		GLTexture(std::string filename, bool managed = true);
		GLTexture(std::string filename, int x, int y, int w, int h, bool managed = true);
		GLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);
		virtual ~GLTexture();

		void Generate();
		void Bind();

		void SetSurfaceTexture(std::string filename, bool managed = true);
		void SetSurfaceTextTexture(std::string text, std::string filename, int size, SDL_Color color, bool managed = true);

		// Inherited from Texture
		virtual void Render() override;
	};
}

#endif
