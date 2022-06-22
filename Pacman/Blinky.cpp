#include "Blinky.h"

Blinky::Blinky(Tile* tile, Texture* texture)
{
	// Początkowa pozycja
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetBlinky(this);
		nextTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}

	collider.w = Width;
	collider.h = Height;

	blinkyTexture = texture;
}

Blinky::~Blinky()
{
}

void Blinky::Update()
{
	Pacman* pacman = tileGraph->GetPacman();

	if (pacman != NULL) {
		if (currTile == nextTile) {
			// Droga do pacman
			PathFinder astar(tileGraph);
			astar.SetAvoidFunction(Blinky::AvoidInPathFinder);
			path = astar.CalculateRoute(currTile, pacman->GetTile());

			nextTile = path[1];

			// gdzie ma isc
			if (position.x < nextTile->GetPosition().x * Tile::Width)
				moveDir = MOVE_RIGHT;

			else if (position.x > nextTile->GetPosition().x * Tile::Width)
				moveDir = MOVE_LEFT;

			else if (position.y > nextTile->GetPosition().y * Tile::Width)
				moveDir = MOVE_UP;

			else if (position.y < nextTile->GetPosition().y * Tile::Width)
				moveDir = MOVE_DOWN;


			// zabic pacman'a
			for (auto tile : tileGraph->GetNeighbours(currTile)) {
				if (tile->GetPacman() != NULL && CheckForCollision(tile->GetPacman()->GetCollider())) {
					tile->GetPacman()->Delete();

					//napis GameOver

				}
			}
		}

		// zmienic droge za pacman'em
		switch (moveDir)
		{
		case MOVE_UP:
			position.y = std::max(position.y - Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case MOVE_DOWN:
			position.y = std::min(position.y + Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case MOVE_LEFT:
			position.x = std::max(position.x - Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		case MOVE_RIGHT:
			position.x = std::min(position.x + Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		}

		// aktualizacja ciąstek
		collider.x = position.x;
		collider.y = position.y;

		// sledzic pacman'a
		if ((moveDir == MOVE_DOWN || moveDir == MOVE_UP) && position.y == nextTile->GetPosition().y * Tile::Height)
			SetTile(nextTile);

		if ((moveDir == MOVE_LEFT || moveDir == MOVE_RIGHT) && position.x == nextTile->GetPosition().x * Tile::Width)
			SetTile(nextTile);
	}
}

void Blinky::Render()
{
	SDL_Rect clip{ 0,0,25,25 };
	blinkyTexture->Render(position.x, position.y, &clip);
}

void Blinky::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;
}


bool Blinky::CheckForCollision(const SDL_Rect& otherCollider)
{
	if (otherCollider.x > collider.x + collider.w) {
		//printf("1");
		return false;
	}

	if (otherCollider.y > collider.y + collider.h) {
		//printf("2");
		return false;
	}

	if (otherCollider.x + otherCollider.w < collider.x) {
		//printf("3");
		return false;
	}

	if (otherCollider.y + otherCollider.h < collider.y) {
		//printf("4");
		return false;
	}

	return true;
}

bool Blinky::AvoidInPathFinder(Tile* tile)
{
	if (tile->GetWall() != NULL) return true;

	return false;
}

void Blinky::Delete()
{
	GameObject::Delete();
}


SDL_Rect Blinky::GetCollider()
{
	return collider;
}
