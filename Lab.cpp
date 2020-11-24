#include "Maze.h"
#include <iostream>

using namespace std;

void connect_diagonal(Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();
	
	for (int i = 0, j = 0; i < n && j < m; ++i, ++j)
	{
		if (j + 1 < m && !maze.makeConnection(i, j, i, j + 1))
			cout << "Can't connect!" << endl;

		if (j + 1 < m &&  i + 1 < n && !maze.makeConnection(i, j + 1, i + 1, j + 1))
			cout << "Can't connect!" << endl;
	}
}

int main()
{
	Maze maze(5, 5);
	connect_diagonal(maze);
	maze.printMaze();
}
