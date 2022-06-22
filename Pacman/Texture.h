#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Texture
{
public:
	static SDL_Renderer* Renderer;

	Texture();
	~Texture();
	bool LoadFromImage(std::string path, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

	bool LoadFromRenderedText(TTF_Font* font, std::string text, SDL_Color textColor);

	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip renderFlip = SDL_FLIP_NONE);

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	void SetBlendMode(SDL_BlendMode blendMode);

	void SetAlpha(Uint8 alpha);

	void Free();

	int GetWidth();
	int GetHeight();

private:
	SDL_Texture* texture;

	int width;
	int height;
};

