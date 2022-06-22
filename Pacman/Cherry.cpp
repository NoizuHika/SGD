#include "Cherry.h"

Cherry::Cherry(Tile* tile, Texture* texture)
{
	currTile = tile;

	cherryTexture = texture;

	if (currTile != NULL) {
		currTile->SetCherry(this);

		position.x = currTile->GetPosition().x * Tile::Width + Margin;
		position.y = currTile->GetPosition().y * Tile::Width + Margin;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	collider.x = position.x;
	collider.y = position.y;

	cherryTexture = texture;

	LoadMedia();
}

bool Cherry::LoadMedia()
{
	// Probowalem zrobic zamiane wisni po zjedzeniu
	eatingCherry[0] = { 0,0,25,25 };
	eatingCherry[1] = { 25,0,25,25 };

	return true;
}

Cherry::~Cherry()
{
}

void Cherry::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetCherry(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetCherry(this);

		position.x = currTile->GetPosition().x * Tile::Width + Margin;
		position.y = currTile->GetPosition().y * Tile::Height + Margin;

		collider.x = position.x;
		collider.y = position.y;
	}
}

void Cherry::Render()
{
	cherryTexture->Render(position.x, position.y);
}

/*void Cherry::Update() {
	if (currTile != NULL) {
		eatingCherry[0] = { 0,0,25,25 };
	}
	else {
		eatingCherry[1] = { 25,0,25,25 };
	}
}*/

void Cherry::Delete()
{
	GameObject::Delete();

	currTile->SetCherry(NULL);
}

SDL_Rect Cherry::GetCollider()
{
	return collider;
}

SDL_Point Cherry::GetPosition()
{
	return position;
}

Tile* Cherry::GetTile()
{
	return currTile;
}