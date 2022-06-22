#include "Texture.h"

SDL_Renderer* Texture::Renderer = NULL;

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromImage(std::string path, Uint8 r, Uint8 g, Uint8 b)
{
	Free();

	// Render
	if (Renderer == NULL)
		return false;

	// Obrazki
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		return false;
	}

	// Tekstury
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
		return false;
	}

	// wysokosc/szerokosc tekstur
	width = loadedSurface->w;
	height = loadedSurface->h;

	return true;
}

bool Texture::LoadFromRenderedText(TTF_Font* font, std::string text, SDL_Color textColor)
{
	if (Renderer == NULL)
		return false;

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (loadedSurface == NULL) {
		return false;
	}

	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
		return false;
	}

	width = loadedSurface->w;
	height = loadedSurface->h;
	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip renderFlip)
{
	if (Renderer == NULL)
		return;

	SDL_Rect renderQuad = { x, y, GetWidth(), GetHeight() };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Renderer, texture, clip, &renderQuad, angle, center, renderFlip);
}

void Texture::Free()
{
	if (texture != NULL) {
		// tekstury to NULL
		SDL_DestroyTexture(texture);
		texture = NULL;

		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}



