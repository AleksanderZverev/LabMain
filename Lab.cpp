#include <iostream>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

void connectLadder(Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();
	
	for (int i = 0; i < n && i < m; ++i)
	{
		maze.makeConnection(i, i, i, i + 1);
		maze.makeConnection(i, i + 1, i + 1, i + 1);
	}
}

void connect_unreachable(Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (j >= i && j + 1 < m)
			{
				maze.makeConnection(i, j, i, j + 1);
			}

			if (j <= i + 1 && i + 1 < n)
			{
				maze.makeConnection(i, j, i + 1, j);
			}
		}
	}
}

void calculate_distances(MTreeNode* baseNode, Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();

	int i = baseNode->i(), j = baseNode->j();
	
	if (i + 1 < n && maze.hasConnection(i,j, i + 1, j))
	{
		if (baseNode->addChild(i + 1, j))
		{
			MTreeNode* child = baseNode->hasChild(i + 1, j);
			assert(child != nullptr);
			calculate_distances(child, maze);
		}
	}

	if (j + 1 < m && maze.hasConnection(i,j,i, j+1))
	{
		if (baseNode->addChild(i,j+1))
		{
			MTreeNode* child = baseNode->hasChild(i, j+1);
			assert(child != nullptr);
			calculate_distances(child, maze);
		}
	}
}

void print_tree(MTreeNode* base, int n, int m)
{
	cout << base->distance() << " ";
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			
			MTreeNode* child = base->hasChild(i, j);
			if (child == nullptr)
				cout << 'X' << ' ';
			else
				cout << child->distance() << " ";
		}
		cout << endl;
	}
}

int main()
{
	Maze diagonalMaze(5, 5);
	connectLadder(diagonalMaze);
	diagonalMaze.printMaze();

	cout << endl;
	
	Maze mazeUnreachable(5, 5);
	connect_unreachable(mazeUnreachable);
	mazeUnreachable.printMaze();

	cout << endl;

	MTreeNode* baseNode = MTreeNode::beginTree(0, 0);
	calculate_distances(baseNode, mazeUnreachable);
	print_tree(baseNode, mazeUnreachable.getN(), mazeUnreachable.getM());
}
