#include "Physic.h"

Physic::Physic(Tile* tile, Texture* texture)
{
	currTile = tile;

	physicTexture = texture;

	if (currTile != NULL) {
		currTile->SetPhysic(this);

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

	physicTexture = texture;
}


Physic::~Physic()
{
}

void Physic::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPhysic(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetPhysic(this);

		position.x = currTile->GetPosition().x * Tile::Width + Margin;
		position.y = currTile->GetPosition().y * Tile::Height + Margin;

		collider.x = position.x;
		collider.y = position.y;
	}
}

void Physic::Render()
{
	physicTexture->Render(position.x, position.y);
}


void Physic::Delete()
{
	GameObject::Delete();

	currTile->SetPhysic(NULL);
}

SDL_Rect Physic::GetCollider()
{
	return collider;
}

SDL_Point Physic::GetPosition()
{
	return position;
}

Tile* Physic::GetTile()
{
	return currTile;
}