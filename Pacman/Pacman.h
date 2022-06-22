#pragma once

#include <algorithm>

#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"
#include "Point.h"
#include "MoveDirection.h"
#include "Cherry.h"
#include "Physic.h"


class Pacman : public GameObject
{
public:
	static const int Width = 25;
	static const int Height = 25;

	static const int MoveFrames = 2;

	static const int Velocity = 3;


	Pacman(Tile* tile, Texture* texture);
	~Pacman();

	bool LoadMedia();

	void SetTile(Tile* newTile);

	void SetNextTile(Tile* newNextTile);

	void HandleEvents(SDL_Event* event);

	void Update();

	void Render();

	void Delete();

	MoveDirection GetMoveDirection();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

	Tile* GetNextTile();

	bool IsMoving();

private:
	bool TryToMove(MoveDirection direction);

	bool CheckForCollision(const SDL_Rect &otherCollider);

	bool CheckForCollision(const SDL_Rect &collider, const SDL_Rect &otherCollider);

	Texture* pacmanTexture;

	SDL_Rect upAnimClips[2];
	SDL_Rect downAnimClips[2];
	SDL_Rect leftAnimClips[2];
	SDL_Rect rightAnimClips[2];

	int frame, frameCount;

	MoveDirection moveDir;
	MoveDirection nextDir;
	bool moving;
	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	SDL_Rect collider;
};

