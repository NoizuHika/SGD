#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"

class Point : public GameObject
{
public:
	static const int Width = 3;
	static const int Height = 3;

	static const int Margin = 11;


	Point(Tile* tile, Texture* texture);
	~Point();

	void SetTile(Tile* newTile);

	void Render();

	void Delete();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

private:
	Texture* pointTexture;

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

