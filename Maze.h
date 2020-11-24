#pragma once

#include "MCell.h"
#include <iostream>
#include <cassert>

using namespace std;

class Maze
{
public:
	Maze(int n, int m);
	~Maze();

	int getN() const { return m_n; }
	int getM() const { return m_m; }

	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;

protected:
	static bool isRight(int i1, int j1, int i2, int j2);
	static bool isDown(int i1, int j1, int i2, int j2);
	static void sortArgs(int& i1, int& j1, int& i2, int& j2);
	static void swap(int& first, int& second) noexcept;

	bool isArgsCorrectForConnection(int i1, int j1, int i2, int j2) const;
	char getConnectionSymbol(int i, int j) const;
	bool isInRange(int i, int j) const;
	
private:
	MCell* get_cell(int i, int j) const;

	MCell* m_field;
	int m_n;
	int m_m;
};
