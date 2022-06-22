#include "Pacman.h"
#include "Texture.h"

Pacman::Pacman(Tile* tile, Texture* texture)
{
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	pacmanTexture = texture;

	LoadMedia();
}

Pacman::~Pacman()
{
}

void Pacman::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;

	//gracz nie przeszkadza duchu
	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Tile::Width;
		position.y = currTile->GetPosition().y * Tile::Height;
	}
}

void Pacman::SetNextTile(Tile* newNextTile)
{
	nextTile = newNextTile;
}

void Pacman::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
		switch (event->key.keysym.sym)
		{
			// Move up
		case SDLK_UP:
		case SDLK_w: nextDir = MOVE_UP; break;

			// Move down
		case SDLK_DOWN:
		case SDLK_s: nextDir = MOVE_DOWN; break;

			// Move left
		case SDLK_LEFT:
		case SDLK_a: nextDir = MOVE_LEFT; break;

			// Move right
		case SDLK_RIGHT:
		case SDLK_d: nextDir = MOVE_RIGHT; break;
		}
	}
}

bool Pacman::LoadMedia()
{
	leftAnimClips[0] = { 0,0,25,25 };
	leftAnimClips[1] = { 25,0,25,25 };

	rightAnimClips[0] = { 0,25,25,25 };
	rightAnimClips[1] = { 25,25,25,25 };

	downAnimClips[0] = { 50,0,25,25 };
	downAnimClips[1] = { 75,0,25,25 };

	upAnimClips[0] = { 50,25,25,25 };
	upAnimClips[1] = { 75,25,25,25 };

	return true;
}

bool Pacman::TryToMove(MoveDirection direction)
{
	Tile* destTile = NULL;

	switch (direction)
	{
	case MOVE_UP:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y - 1);
		break;
	case MOVE_DOWN:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y + 1);
		break;
	case MOVE_LEFT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x - 1, currTile->GetPosition().y);
		break;
	case MOVE_RIGHT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x + 1, currTile->GetPosition().y);
		break;
	}

	// sciana
	if (destTile->GetWall() != NULL) {
		SetNextTile(NULL);
		return false;
	}

	SetNextTile(destTile);

	return true;
}

bool Pacman::CheckForCollision(const SDL_Rect& collider, const SDL_Rect& otherCollider)
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

void Pacman::Update()
{
	// colisja
	if (currTile != NULL && currTile->GetPoint() != NULL) {
		SDL_Rect eatingHole = {
			position.x + Point::Margin,
			position.y + Point::Margin,
			Point::Width,
			Point::Height,
		};

		if (CheckForCollision(eatingHole, nextTile->GetPoint()->GetCollider())) {
			nextTile->GetPoint()->Delete();
		}
	}
	else if (currTile != NULL && currTile->GetCherry() != NULL) {
		SDL_Rect eatingCherry = {
			position.x + Point::Margin,
			position.y + Point::Margin,
			Point::Width,
			Point::Height,
		};

		if (CheckForCollision(eatingCherry, nextTile->GetCherry()->GetCollider())) {
			nextTile->GetCherry()->Delete();
		}
	}

	// animacja
	if (moving) {
		frameCount++;
		frame = frameCount / 8;

		if (frame > MoveFrames - 1) {
			frame = 0;
			frameCount = 0;
		}
	}

	// movement
	if (nextTile == currTile || nextTile == NULL) {
		if (nextDir != moveDir && TryToMove(nextDir))
			moveDir = nextDir;
		else
			TryToMove(moveDir);

		if (nextTile == NULL)
			moving = false;
		else
			moving = true;
	}
	else {
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

		collider.x = position.x;
		collider.y = position.y;

		if ((moveDir == MOVE_DOWN || moveDir == MOVE_UP) && position.y == nextTile->GetPosition().y * Tile::Height)
			SetTile(nextTile);

		if ((moveDir == MOVE_LEFT || moveDir == MOVE_RIGHT) && position.x == nextTile->GetPosition().x * Tile::Width)
			SetTile(nextTile);
	}
}

void Pacman::Render()
{
	SDL_Rect* animClip = NULL;

	switch (moveDir)
	{
	case MOVE_UP:
		animClip = &upAnimClips[frame];
		break;
	case MOVE_DOWN:
		animClip = &downAnimClips[frame];
		break;
	case MOVE_LEFT:
		animClip = &leftAnimClips[frame];
		break;
	case MOVE_RIGHT:
		animClip = &rightAnimClips[frame];
		break;
	}

	pacmanTexture->Render(position.x, position.y, animClip);
}

void Pacman::Delete()
{
	GameObject::Delete();

	currTile->SetPacman(NULL);
}


SDL_Rect Pacman::GetCollider()
{
	return collider;
}


Tile* Pacman::GetTile()
{
	return currTile;
}
