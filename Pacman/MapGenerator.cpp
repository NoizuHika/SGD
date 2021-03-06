#include "MapGenerator.h"

MapGenerator::MapGenerator(TileGraph* tileGraph, TextureManager* textureManager)
{
	pTileGraph = tileGraph;
	pTextureManager = textureManager;
}

bool MapGenerator::Load(std::string path)
{
	std::fstream file;

	file.open(path.c_str(), std::ios::in);

	if (file.is_open() == false)
		return false;

	std::string line;

	int x = 0;
	int y = 0;

	//odczytanie linijami
	while (std::getline(file, line)) {
		// linija w vector
		std::vector<char> chars(line.begin(), line.end());

		for (unsigned int x = 0; x < chars.size(); x++) {
			GameObject* newObject = NULL;
			Tile* tile = pTileGraph->GetTileAt(x, y);

			//objekty
			switch (chars[x])
			{
			case 'x':
				newObject = new Wall(tile, pTextureManager->Get("wall"));
				break;
			case '.':
				newObject = new Point(tile, pTextureManager->Get("point"));
				break;
			case 'p':
				newObject = new Pacman(tile, pTextureManager->Get("pacman"));
				break;
			case 'b':
				newObject = new Blinky(tile, pTextureManager->Get("blinky"));
				break;
			case 'h':
				newObject = new Cherry(tile, pTextureManager->Get("cherry"));
				break;
			}
		

			if (newObject != NULL)
				objectVector.push_back(newObject);
		}

		y++;
	}

	file.close();

	return true;
}

void MapGenerator::Populate(std::vector<GameObject*>& vector)
{
	for (unsigned int i = 0; i < objectVector.size(); i++) {
		vector.push_back(objectVector[i]);
	}
}
