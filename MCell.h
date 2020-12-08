#pragma once

class MCell
{
	friend class Maze;

public:
	bool down() const { return m_down; }
	bool right() const { return  m_right; }

private:
	MCell(){ }
	
	bool m_down = false;
	bool m_right = false;
};
