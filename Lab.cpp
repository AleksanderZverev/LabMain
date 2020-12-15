#include <iostream>
#include <cassert>

#include "Maze.h"
#include "MTreeNode.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <queue>

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

void connectUnreachableLines(Maze& maze)
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

void calculateDistances(MTreeNode* baseNode, Maze& maze)
{
	const int n = maze.getN(), m = maze.getM();

	int i = baseNode->i(), j = baseNode->j();
	
	if (i + 1 < n && maze.hasConnection(i,j, i + 1, j))
	{
		if (baseNode->addChild(i + 1, j))
		{
			MTreeNode* child = baseNode->hasChild(i + 1, j);
			assert(child != nullptr);
			calculateDistances(child, maze);
		}
	}

	if (j + 1 < m && maze.hasConnection(i,j,i, j+1))
	{
		if (baseNode->addChild(i,j+1))
		{
			MTreeNode* child = baseNode->hasChild(i, j+1);
			assert(child != nullptr);
			calculateDistances(child, maze);
		}
	}
}

int getMaxIndex(const MTreeNode* base, int max)
{
	if (base->childCount() == 0)
		return  base->distance();

	for (int i = 0; i < base->childCount(); ++i)
	{
		const MTreeNode* child = base->child(i);
		int distance = getMaxIndex(child, max);
		if (distance > max)
			max = distance;
	}
	return max;
}

void calculateSumAndQuantity(const MTreeNode* base, int& sum, int& quantity)
{
	sum += base->distance();
	quantity++;
	
	if (base->childCount() == 0)
		return;

	for (int i = 0; i < base->childCount(); ++i)
	{
		const MTreeNode* child = base->child(i);
		calculateSumAndQuantity(child, sum, quantity);
	}
}

void printTree(MTreeNode* base, int n, int m, int max = 9)
{
	int bI = base->i(), bJ = base->j();
	int space = 0;
	while(max > 0)
	{
		max = max / 10;
		space++;
	}
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (bI == i && bJ == j)
			{
				cout << setw(space) << '0' << ' ';
				continue;
			}
			
			MTreeNode* child = base->findChild(i, j);
			if (child == nullptr)
				cout << setw(space) << 'X' << ' ';
			else
				cout << setw(space) << child->distance() << " ";
		}
		cout << endl;
	}
}

MTreeNode* getNode(const vector<MTreeNode*>& mazeArray, const int m, const int i, const int j)
{
	const int index = i * m + j;
	if (index < 0 || index >= mazeArray.size())
		return nullptr;
	return mazeArray[index];
}

MTreeNode* pushNode(vector<MTreeNode*>& mazeArray, const int m, MTreeNode* node)
{
	const int i = node->i(), j = node->j();
	const int index = i * m + j;
	assert(index >= 0 && index < mazeArray.size());
	mazeArray[index] = node;
	return mazeArray[index];
}

bool hasFreeNeighbors(vector<MTreeNode*>& mazeArray, int n, int m, int i, int j)
{
	return i - 1 >= 0 && getNode(mazeArray, m, i - 1, j) == nullptr
		|| j - 1 >= 0 && getNode(mazeArray, m, i, j - 1) == nullptr
		|| i + 1 < n && getNode(mazeArray, m, i + 1, j) == nullptr
		|| j + 1 < m && getNode(mazeArray, m, i, j + 1) == nullptr;
}

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	srand(time(NULL));

	int n = iMaze.getN(), m = iMaze.getM();
	vector<MTreeNode*> mazeArray(n * m);

	queue<MTreeNode*> nodesQueue;
	queue<MTreeNode*> nextNodes;
	nextNodes.push(&tree);
	pushNode(mazeArray, m, &tree);

	while (nextNodes.size() > 0)
	{
		nodesQueue.swap(nextNodes);
		
		while (nodesQueue.size() > 0)
		{
			MTreeNode& currentNode = *nodesQueue.front();
			nodesQueue.pop();
			
			const int startI = currentNode.i(), startJ = currentNode.j();

			while (hasFreeNeighbors(mazeArray, n, m, startI, startJ))
			{
				const int nextI = startI + (rand() % 3 - 1);
				const int nextJ = startJ + (nextI == startI
					? rand() % 3 - 1
					: 0);
				
				const bool hasNode = getNode(mazeArray, m, nextI, nextJ) != nullptr;

				if (!hasNode && currentNode.addChild(nextI, nextJ) )
				{
					bool isAdded = iMaze.makeConnection(startI, startJ, nextI, nextJ);
					if (!isAdded)
						continue;
					
					if (hasFreeNeighbors(mazeArray, n, m, startI, startJ))
						nextNodes.push(&currentNode);
					
					MTreeNode* addedChild = MTreeNode::searchNode(tree, nextI, nextJ);
					pushNode(mazeArray, m, addedChild);
					nextNodes.push(addedChild);
					
					break;
				}
			}
		}
	}
}

int main()
{
	Maze diagonalMaze(5, 5);
	connectLadder(diagonalMaze);
	diagonalMaze.printMaze();

	cout << endl;
	
	Maze mazeUnreachable(5, 5);
	connectUnreachableLines(mazeUnreachable);
	mazeUnreachable.printMaze();

	cout << endl;

	MTreeNode* baseNode = MTreeNode::beginTree(0, 0);
	calculateDistances(baseNode, mazeUnreachable);
	printTree(baseNode, mazeUnreachable.getN(), mazeUnreachable.getM());

	cout << endl;
	
	Maze randomMaze(10, 10);
	
	srand(time(NULL));
	int i = rand() % randomMaze.getN(), j = rand() % randomMaze.getM();
	MTreeNode* start = MTreeNode::beginTree(i, j);
	
	buildFullMaze(randomMaze, *start);
	
	randomMaze.printMaze();
	cout << endl;
	int max = getMaxIndex(start, 0);
	printTree(start, randomMaze.getN(), randomMaze.getM(), max);
	cout << endl;

	cout << "Max: " << max << endl;
	int sum = 0, quantity = 0;
	calculateSumAndQuantity(start, sum, quantity);
	cout << "Middle: " << sum / quantity << endl;
}
