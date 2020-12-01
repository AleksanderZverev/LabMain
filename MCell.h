#pragma once

class MCell
{
public:
	bool getDown() const { return m_down; }
	bool getRight() const { return  m_right; }

	friend class Maze;
	
private:
	bool m_down = false;
	bool m_right = false;
};
