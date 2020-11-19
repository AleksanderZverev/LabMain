#pragma once

class MCell
{

public:
	bool getDown() const { return m_down; }
	bool getRight() const { return  m_right; }

	friend class Maze;
private:
	MCell();
	
	bool m_down;
	bool m_right;
};
