#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Pacman.h"
#include "Wall.h"
#include "Point.h"
#include "Cherry.h"
#include "Misc.h"
#include "TileGraph.h"
#include "MapGenerator.h"
#include "TextureManager.h"
#include "Physic.h"

// rozmiar
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//render
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TextureManager gTextureManager;

std::vector<GameObject*> gGameObjectList;

TileGraph gTileGraph(20, 20);

MapGenerator gMapGenerator(&gTileGraph, &gTextureManager);

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	gWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		// stabilizacja
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);

		if (gRenderer == NULL)
		{
			return false;
		}
	}

	//Liniowe filtrowanie tekstur
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
	}

	if (TTF_Init() == -1) {
		return false;
	}

	Texture::Renderer = gRenderer;

	return true;
}

bool loadMedia()
{
	Texture* wallTexture = new Texture();
	if (!wallTexture->LoadFromImage("./Resources/wall_sprite.bmp"))
		return false;

	Texture* pointTexture = new Texture();
	if (!pointTexture->LoadFromImage("./Resources/point2.bmp"))
		return false;

	Texture* pacmanTexture = new Texture();
	if (!pacmanTexture->LoadFromImage("./Resources/PacMan.bmp"))
		return false;

	Texture* blinkyTexture = new Texture();
	if (!blinkyTexture->LoadFromImage("./Resources/blinky.bmp"))
		return false;

	Texture* cherryTexture = new Texture();
	if (!cherryTexture->LoadFromImage("./Resources/Cherry.bmp"))
		return false;

	Texture* physicTexture = new Texture();
	if (!physicTexture->LoadFromImage("./Resources/Cherry1.bmp"))
		return false;

	GameObject::tileGraph = &gTileGraph;

	gTextureManager.Add("wall", wallTexture);
	gTextureManager.Add("point", pointTexture);
	gTextureManager.Add("pacman", pacmanTexture);
	gTextureManager.Add("blinky", blinkyTexture);
	gTextureManager.Add("cherry", cherryTexture);
	gTextureManager.Add("physic", physicTexture);

	Wall::CreateClips();

	if (!gMapGenerator.Load("./Resources/mapa.txt"))
		return false;

	gMapGenerator.Populate(gGameObjectList);

	return true;
}


void close()
{
	for (unsigned int i = 0; i < gGameObjectList.size(); i++)
		delete gGameObjectList[i];
}

int main(int argc, char* args[])
{
	// Start
	if (!init()) {
		return -1;
	}

	if (!loadMedia()) {
		close();

		return -2;
	}

	bool quit = false;

	SDL_Event e;

	while (!quit)
	{
		// usuwanie ciąstek do usuniecia
		for (unsigned int i = 0; i < gGameObjectList.size(); i++) {
			if (gGameObjectList[i]->ToDelete()) {
				delete gGameObjectList[i];
				removeFromVector(gGameObjectList, *gGameObjectList[i]);
			}
		}

		while (SDL_PollEvent(&e) != 0)
		{
			//wyjscie
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// aktualizacja objektow
			for (unsigned int i = 0; i < gGameObjectList.size(); i++)
				gGameObjectList[i]->HandleEvents(&e);
		}

		// logika
		for (unsigned int i = 0; i < gGameObjectList.size(); i++)
			gGameObjectList[i]->Update();

		// black screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render
		for (unsigned int i = 0; i < gGameObjectList.size(); i++)
			gGameObjectList[i]->Render();

		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}