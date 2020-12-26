#include "Maze.h"

void connectLadder(Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();
	
	for (int i = 0; i < n && i < m; ++i)
	{
		maze.makeConnection(i, i, i, i + 1);
		maze.makeConnection(i, i + 1, i + 1, i + 1);
	}
}

int main()
{
	Maze maze(5, 5);
	connectLadder(maze);
	maze.printMaze();
}
