#include "MTreeNode.h"

const MTreeNode* MTreeNode::parent() const
{
	return m_parent;
}

const MTreeNode* MTreeNode::child(int i) const
{
	if (i > 0 && i < m_child_count)
	{
		MTreeNode* child = *(m_childrens_array + i);
		assert(child != nullptr);
		return child;
	}
	
	return nullptr;
}

int MTreeNode::childCount() const
{
	return m_child_count;
}

int MTreeNode::distance() const
{
	return m_distance;
}

bool MTreeNode::addChild(int i, int j)
{
	if (!isIndexesCorrect(i, j) || m_child_count >= max_children)
		return false;
	
	MTreeNode* child = new MTreeNode(this, i, j, m_distance + 1);
	addChildToArray(child);
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	if (i < 0 || j < 0)
		return nullptr;
	
	for (int k = 0; k < m_child_count; ++k)
	{
		MTreeNode* child = *(m_childrens_array + k);
		assert(child != nullptr);
		if (child->m_i == i && child->m_j == j)
			return child;

		MTreeNode* childByChild = child->hasChild(i, j);
		if (childByChild != nullptr)
			return childByChild;
	}
	
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* node = new MTreeNode(nullptr, i, j, 0);
	return node;
}

void MTreeNode::addChildToArray(MTreeNode* child)
{
	m_childrens_array[m_child_count] = child;
	m_child_count++;
}

MTreeNode::MTreeNode(MTreeNode* parent, int i, int j, int distance) :
	m_parent(parent),
	m_childrens_array(new MTreeNode*[max_children]),
	m_distance(distance),
	m_i(i),
	m_j(j),
	m_child_count(0)
{ }

MTreeNode::~MTreeNode()
{
	delete[] m_childrens_array;
}

bool MTreeNode::isIndexesCorrect(int i, int j) const
{
	return abs(i - m_i) == 1 && m_j == j
		|| abs(j - m_j) == 1 && i == m_i;
}
