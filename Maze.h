#pragma once

#include "MCell.h"


class Maze
{
public:
	Maze(int n, int m);
	~Maze();

	int getN() const { return m_n; }
	int getM() const { return m_m; }

	const MCell& cell(int i, int j) const;
	bool defineConnectionAndReturn(int i1, int j1, int i2, int j2,
	                              bool (*returnForRightConnection)(MCell* minCell),
	                              bool (*returnForDownConnection)(MCell* minCell)) const;
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;

protected:
	char getConnectionSymbol(int i, int j) const;
	bool isInRange(int i, int j) const;
	
private:
	static bool hasConnectionLeftCell(MCell* leftCell) { return leftCell->right(); }
	static bool hasConnectionUpCell(MCell* upCell) { return upCell->down(); }
	static bool makeConnectionLeftCell(MCell* leftCell) { leftCell->m_right = true; return true; }
	static bool makeConnectionUpCell(MCell* upCell) { upCell->m_down = true; return true; }
	static bool removeConnectionLeftCell(MCell* leftCell) { leftCell->m_right = false; return true; }
	static bool removeConnectionUpCell(MCell* upCell) { upCell->m_down = false; return true; }
	
	MCell* get_cell(int i, int j) const;

	MCell* m_field = nullptr;
	const int m_n = 0;
	const int m_m = 0;
};
