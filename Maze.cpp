#include "Maze.h"

Maze::Maze(int n, int m)
{
	m_n = n;
	m_m = m;
	m_field = new MCell[m_n * m_m];
}

Maze::~Maze()
{
	delete[] m_field;
}

bool Maze::isCorrect(int i, int j) const
{
	return i < m_n && j < m_m && i >= 0 && j >= 0;
}

const MCell& Maze::cell(int i, int j) const
{
	return *get_cell(i, j);
}

MCell* Maze::get_cell(int i, int j) const
{
	if (!isCorrect(i, j))
		return nullptr;
	
	return m_field + (i * m_n + j);
}

bool Maze::isRight(int i1, int j1, int i2, int j2)
{
	return i1 == i2 && j1 < j2;
}

bool Maze::isDown(int i1, int j1, int i2, int j2)
{
	return i1 < i2 && j1 == j2;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	auto& cell1 = *get_cell(i1, j1);

	if (isRight(i1, j1, i2, j2))
	{
		cell1.m_right = true;
		return true;
	}
	
	if (isDown(i1, j1, i2, j2))
	{
		cell1.m_down = true;
		return true;
	}
	
	return false;
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const
{
	auto cell1 = cell(i1, j1);
	
	if (isRight(i1, j1, i2, j2))
		return cell1.getRight();

	if (isDown(i1, j1, i2, j2))
		return cell1.getDown();
	
	return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	auto& cell1 = *get_cell(i1, j1);

	if (isRight(i1, j1, i2, j2) && cell1.getRight())
	{
		cell1.m_right = false;
		return true;
	}

	if (isDown(i1, j1, i2, j2) && cell1.getDown())
	{
		cell1.m_down = false;
		return true;
	}
	
	return false;
}

void Maze::printMaze() const
{
	using namespace std;
	
	for (int i = 0; i < m_n; ++i)
	{
		for (int j = 0; j < m_m; ++j)
		{
			auto sym = getConnectionSymbol(i, j);
			sym = sym == '_' ? '0' : sym;
			cout << sym;
		}
		cout << endl;
	}
}

char Maze::getConnectionSymbol(int i, int j) const
{
	if (!isCorrect(i, j))
		return '_';

	const auto baseCell = *get_cell(i, j);
	const auto* topCell = get_cell(i - 1, j);
	const auto* leftCell = get_cell(i, j - 1);

	if (topCell != nullptr && leftCell != nullptr
		&& topCell->getDown() && leftCell->getRight())
	{
		if (baseCell.getRight() && baseCell.getDown()) return (char)197;
		if (baseCell.getRight()) return (char)193;
		if (baseCell.getDown()) return (char)180;
	}

	if (topCell != nullptr && topCell->getDown())
	{
		if (baseCell.getRight() && baseCell.getDown()) return (char)196;
		if (baseCell.getRight()) return (char)192;
		if (baseCell.getDown()) return (char)179;
	}

	if (leftCell != nullptr && leftCell->getRight())
	{
		if (baseCell.getRight() && baseCell.getDown()) return (char)194;
		if (baseCell.getRight()) return (char)196;
		if (baseCell.getDown()) return (char)191;
	}
	
	return '_';
}
