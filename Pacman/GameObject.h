#pragma once

#include <SDL.h>
#include <vector>

class TileGraph;

class GameObject
{
public:
	static TileGraph* tileGraph;

	virtual void HandleEvents(SDL_Event* event);
	virtual void Update();
	virtual void Render();
	virtual void Free();
	virtual SDL_Rect GetCollider();

	virtual ~GameObject();

	virtual void Delete();

	bool ToDelete() const;

private:
	bool toDelete;
};

