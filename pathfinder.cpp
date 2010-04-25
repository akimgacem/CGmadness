/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck <sreinck@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "path/NoiseWorld.hpp"
#include "path/NodeAStar.hpp"
#include "path/WorldGraph.hpp"
#include "path/DijkstraHeuristic.hpp"

#include "macros.hpp"

#include <cstdio>

int main(int argc, char* argv[])
{
	NoiseWorld noiseworld;
	World& world = noiseworld;

	WorldGraph graph(world);
	DijkstraHeuristic heuristic;

	NodeAStar pathfinder(graph, heuristic);

	NodeID origin(0, 0);
	NodeID destination(WORLD_SIZE_X - 1, WORLD_SIZE_X - 1);
	std::list<NodeID> route;
	pathfinder.execute(origin, destination, route);

	NodeMap<bool> map;
	FOREACH(route, iter)
	{
		const NodeID& nid = *iter;
		map.put(nid, true);
	}

	map.put(origin, true);

	for (int y = 0; y < WORLD_SIZE_Y; y++)
	{
		for (int x = 0; x < WORLD_SIZE_X; x++)
		{
			NodeID nid(x, y);
			int height = world.getHeight(x, y);
			if (height > 0)
			{
				printf(" %d ", height);
			}
			else if (map.exists(nid))
			{
				printf(" # ");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}

	return 0;
}
