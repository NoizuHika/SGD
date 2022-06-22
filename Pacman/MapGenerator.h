#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "TileGraph.h"
#include "TextureManager.h"

#include "Wall.h"
#include "Point.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Cherry.h"
#include "Physic.h"

class GameObject;

class MapGenerator
{
public:
	MapGenerator(TileGraph* tileGraph, TextureManager* textureManager);

	bool Load(std::string path);

	void Populate(std::vector<GameObject*>& vector);

private:
	std::vector<GameObject*> objectVector;

	TileGraph* pTileGraph;
	TextureManager* pTextureManager;
};

