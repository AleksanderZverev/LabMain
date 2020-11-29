#pragma once

#include <algorithm>
#include <cassert>

class MTreeNode
{
public:
	int i() const { return m_i; }
	int j() const { return m_j; }

	const MTreeNode* parent() const;
	const MTreeNode* child(int i) const;
	int childCount() const;
	int distance() const;

	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);

	static MTreeNode* beginTree(int i, int j);

protected:
	void addChildToArray(MTreeNode* child);
	
	
private:
	MTreeNode(MTreeNode* parent, int i, int j, int distance);
	~MTreeNode();

	bool isIndexesCorrect(int i, int j) const;
	
	int m_i;
	int m_j;
	MTreeNode* const m_parent;
	MTreeNode** const m_childrens_array;
	const int m_distance;
	int m_child_count;
	
	static const int max_children = 4;
};
