#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"

class Physic : public GameObject
{
public:
	static const int Width = 25;
	static const int Height = 25;

	static const int Margin = 0;


	Physic(Tile* tile, Texture* texture);
	~Physic();

	void SetTile(Tile* newTile);

	void Render();

	bool LoadMedia();

	void Delete();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

private:
	Texture* physicTexture;

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

