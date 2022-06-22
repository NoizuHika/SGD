#pragma once

#include <algorithm>

#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"
#include "Point.h"
#include "MoveDirection.h"
#include "PathFinder.h"
#include "Pacman.h"
#include "Cherry.h"
#include "Physic.h"

class Blinky : public GameObject
{
public:
	// Prefixed w,h blinky
	static const int Width = 25;
	static const int Height = 25;

	// Movement per frame
	static const int Velocity = 2;

	Blinky(Tile* tile, Texture* texture);
	~Blinky();

	// Pozycja
	void SetTile(Tile* newTile);

	// Dalsza droga
	void SetNextTile(Tile* newNextTile);

	// Aktualizacja
	void Update();

	// Render
	void Render();

	// Delete
	void Delete();

	// Gdzie teraz
	MoveDirection GetMoveDirection();

	// Collider
	SDL_Rect GetCollider();

	// Pozycja
	SDL_Point GetPosition();

	// Tile
	Tile* GetTile();

	// Nastepny tile
	Tile* GetNextTile();

	// porusza sie
	bool IsMoving();

private:
	// kolizja
	bool CheckForCollision(const SDL_Rect &otherCollider);

	// kolizja
	bool CheckForCollision(const SDL_Rect &collider, const SDL_Rect &otherCollider);

	// pozycji
	bool HasPositionChanged(SDL_Point firstPos, SDL_Point secondPoint);

	static bool AvoidInPathFinder(Tile* tile);

	Texture* blinkyTexture;

	MoveDirection moveDir;
	MoveDirection nextDir;
	bool moving;

	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	std::vector<Tile*> path;
	SDL_Point lastPacmanPos;

	SDL_Rect collider;
};

