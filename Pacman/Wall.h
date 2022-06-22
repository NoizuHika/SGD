#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"

enum WorldDirections {
	DIR_N = 1 << 0,
	DIR_E = 1 << 1,
	DIR_S = 1 << 2,
	DIR_W = 1 << 3
};

class Wall : public GameObject
{
public:
	static const int Width = 25;
	static const int Height = 25;

	static void CreateClips();

	Wall(Tile* tile, Texture* texture);
	~Wall();

	void SetTile(Tile* newTile);

	void UpdateConnections();

	void Delete();

	void Render();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

private:
	bool CheckForWall(Tile* tile);

	Texture* wallTexture;
	int connections;
	static SDL_Rect textureClips[16];

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

