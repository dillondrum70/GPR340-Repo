#include "Agent.h"
#include "World.h"

Path Agent::FindCatShortestPath(World* world) {

	PriorityQueue frontier = PriorityQueue(); //next to explore
	frontier.push(std::make_pair(0, world->getCat()));

	WeightMap weights = WeightMap();  // store weights of each node
    weights[frontier.top().second.x][frontier.top().second.y] = 0;

	ParentMap parents = ParentMap();  // store parents of each node

	Path solution = Path();

	while (!frontier.empty()) 
	{
        Point2D current = frontier.top().second;
		Point2D next = Point2D(0, 0);

		for (int i = 0; i < 6; i++)
		{
			switch (i)
			{
			case 0:
				next = World::NE(next);
				break;
			case 1:
				next = World::NW(next);
				break;
			case 2:
				next = World::W(next);
				break;
			case 3:
				next = World::SW(next);
				break;
			case 4:
				next = World::SE(next);
				break;
			case 5:
				next = World::E(next);
				break;
			}

			//if x coord is 0 or max x value or if y coord is 0 or max y value, return that path
			if (!world->isValidPosition(next))
			{
				//only executed once so algorithm time is O(n)
				//the loop that iterates over the 6 directions is constant at 6 so it's complexity is technically O(1)
				solution.push_front(next); //next move cat should take will be at the top
				Point2D evaluate = current;

				//trace back through parents to get path, if parent is cat, stop, break, and return path
				while (evaluate != world->getCat())
				{
					solution.push_front(evaluate);
                    evaluate = parents[evaluate.x][evaluate.y];
				}
				break;
			}

			//if weight of next is null, it hasn't been explored yet, or if it is greater than the new path, we need to explore it
			//and if cat can move to position, position should be explored.  Otherwise, we skip this position
			if ((weights[next.x][next.y] != 0 || weights[next.x][next.y] > weights[current.x][current.y] + 1) && world->catCanMoveToPosition(next))
			{
                weights[next.x][next.y] = weights[current.x][current.y] + 1;
                parents[next.x][next.y] = current;
                frontier.push(std::make_pair(weights[next.x][next.y], next));
			}
		}

		frontier.pop();
	}

	//return empty path, no path to exit exists
	return solution;
}