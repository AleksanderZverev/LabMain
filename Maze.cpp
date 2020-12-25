#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <cassert>

Maze::Maze(int n, int m) : m_n(n), m_m(m)
{
	m_field = new MCell[m_n * m_m];
}

Maze::~Maze()
{
	delete[] m_field;
}

const MCell& Maze::cell(int i, int j) const
{
	assert(isInRange(i, j));
	const auto cell1 = get_cell(i, j);
	assert(cell1 != nullptr);
	return *cell1;
}

MCell* Maze::get_cell(int i, int j) const
{
	if(!isInRange(i, j))
		return nullptr;
	
	return m_field + (i * m_m + j);
}

bool Maze::isInRange(int i, int j) const
{
	return i < m_n && j < m_m && i >= 0 && j >= 0;
}

bool Maze::defineConnectionAndReturn(int i1, int j1, int i2, int j2, 
	bool (*returnForRightConnection)(MCell* minCell),
	bool (*returnForDownConnection)(MCell* minCell)) const
{
	const int iAbsDifference = abs(i1 - i2);
	const int jAbsDifference = abs(j1 - j2);

	if (iAbsDifference + jAbsDifference != 1
		|| !isInRange(i1, j1)
		|| !isInRange(i2, j2))
		return false;

	auto cell1 = get_cell(std::min(i1, i2), std::min(j1, j2));
	assert(cell1 != nullptr);

	if (jAbsDifference == 1)
		return returnForRightConnection(cell1);

	if (iAbsDifference == 1)
		return returnForDownConnection(cell1);

	return false;
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const
{
	auto rightF = [](MCell* leftCell) -> bool { return leftCell->right();  };
	auto downF = [](MCell* upCell) -> bool { return upCell->down(); };
	
	return defineConnectionAndReturn(i1, j1, i2, j2, rightF, downF);
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	auto rightF = [](MCell* leftCell) -> bool { leftCell->m_right = true; return true;  };
	auto downF = [](MCell* upCell) -> bool { upCell->m_down = true; return true; };

	return defineConnectionAndReturn(i1, j1, i2, j2, rightF, downF);
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	auto rightF = [](MCell* leftCell) -> bool { leftCell->m_right = false; return true;  };
	auto downF = [](MCell* upCell) -> bool { upCell->m_down = false; return true; };

	return defineConnectionAndReturn(i1, j1, i2, j2, rightF, downF);
}

void Maze::printMaze() const
{
	for (int i = 0; i < m_n; ++i)
	{
		for (int j = 0; j < m_m; ++j)
		{
			std::cout << getConnectionSymbol(i, j);
		}
		std::cout << std::endl;
	}
}

char Maze::getConnectionSymbol(int i, int j) const
{
	assert(isInRange(i, j));

	const auto baseCell = *get_cell(i, j);
	const auto* topCell = get_cell(i - 1, j);
	const auto* leftCell = get_cell(i, j - 1);

	if (topCell != nullptr && leftCell != nullptr
		&& topCell->down() && leftCell->right())
	{
		if (baseCell.right() && baseCell.down()) return (char)197;
		if (baseCell.right()) return (char)193;
		if (baseCell.down()) return (char)180;
		return (char)217;
	}

	if (topCell != nullptr && topCell->down())
	{
		if (baseCell.right() && baseCell.down()) return (char)195;
		if (baseCell.right()) return (char)192;
		if (baseCell.down()) return (char)179;
	}

	if (leftCell != nullptr && leftCell->right())
	{
		if (baseCell.right() && baseCell.down()) return (char)194;
		if (baseCell.right()) return (char)196;
		if (baseCell.down()) return (char)191;
	}

	if (baseCell.right() && baseCell.down())
		return (char)218;

	return (char)248;
}
