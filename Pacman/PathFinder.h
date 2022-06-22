#pragma once

#include <queue>
#include <unordered_map>
#include <functional>

#include "TileGraph.h"
#include "PriorityQueue.h"

class PathFinder
{
public:
	PathFinder(TileGraph* tileGraph);

	std::vector<Tile*> CalculateRoute(Tile* start, Tile* goal);

	void SetAvoidFunction(function<bool(Tile*)> newFunction);

private:
	static inline float Heuristic(Tile* a, Tile* b);

	TileGraph* pTileGraph;
	function<bool(Tile*)> avoidFunction;
};

