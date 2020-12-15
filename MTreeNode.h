#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

class MTreeNode
{
public:
	int i() const { return m_i; }
	int j() const { return m_j; }

	const MTreeNode* parent() const { return m_parent; }
	const MTreeNode* child(int i) const;
	int childCount() const { return m_child_count; }
	int distance() const { return m_distance; }

	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	MTreeNode* findChild(int i, int j, bool isFullSeek = true);

	static MTreeNode* beginTree(int i, int j);

protected:
	void addChildToArray(MTreeNode* child);
	
private:
	MTreeNode(MTreeNode* parent, int i, int j, int distance);
	~MTreeNode();

	bool isIndexesCorrect(int i, int j) const;

	MTreeNode* const m_parent;
	MTreeNode** const m_children_array;
	
	int m_i;
	int m_j;
	const int m_distance;
	int m_child_count;
	
	static const int max_children = 4;
};
