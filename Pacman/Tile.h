#pragma once

#include <SDL.h>

class Pacman;
class Wall;
class Point;
class Blinky;
class Cherry;
class Physic;

class Tile
{
public:
	const static int Width = 25;
	const static int Height = 25;

	Tile();
	Tile(int x, int y);

	void SetPacman(Pacman* pacman);

	void SetWall(Wall* wall);

	void SetPoint(Point* wall);

	void SetBlinky(Blinky* blinky);

	void SetCherry(Cherry* cherry);

	void SetPhysic(Physic* physic);

	void SetPos(int x, int y);

	Pacman* GetPacman();
	
	Wall* GetWall();

	Point* GetPoint();

	Blinky* GetBlinky();

	Cherry* GetCherry();

	Physic* GetPhysic();

	SDL_Point GetPosition();

private:
	SDL_Point position;
	
	Pacman* pPacman;
	Wall* pWall;
	Point* pPoint;
	Blinky* pBlinky;
	Cherry* pCherry;
	Physic* pPhysic;
};

