#include <iostream>
#include "Maze.h"

using namespace std;

void connectLadder(Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();
	
	for (int i = 0; i < n && i < m; ++i)
	{
		if (i + 1 < m)
		{
			maze.makeConnection(i, i, i, i + 1);
		}

		if (i + 1 < m &&  i + 1 < n)
		{
			maze.makeConnection(i, i + 1, i + 1, i + 1);
		}
	}
}

int main()
{
	Maze maze(5, 5);
	connectLadder(maze);
	maze.printMaze();
}
