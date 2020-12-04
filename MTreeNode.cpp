#include "MTreeNode.h"

#include <algorithm>
#include <cassert>
#include <vector>

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

bool MTreeNode::addChild(int i, int j)
{
	if (!isIndexesCorrect(i, j) || m_child_count >= max_children || hasChild(i, j) != nullptr)
		return false;
	
	MTreeNode* child = new MTreeNode(this, i, j, m_distance + 1);
	addChildToArray(child);
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	return findChild(i, j, false);
}

MTreeNode* MTreeNode::findChild(int i, int j, bool isFullSeek)
{
	std::vector<MTreeNode*> children(m_child_count);

	for (int k = 0; k < m_child_count; ++k)
	{
		
		MTreeNode* child = *(m_children_array + k);
		assert(child != nullptr);
		if (child->m_i == i && child->m_j == j)
			return child;
		children[k] = child;
	}

	if (isFullSeek)
		for (MTreeNode* child : children)
		{
			MTreeNode* childByChild = child->findChild(i, j);
			if (childByChild != nullptr)
				return childByChild;
		}

	return nullptr;
}

MTreeNode* MTreeNode::searchNode(const MTreeNode& tree, const int i, const int j)
{
	MTreeNode* child = const_cast<MTreeNode*>(&tree)->hasChild(i, j);
	
	return child;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* node = new MTreeNode(nullptr, i, j, 0);
	return node;
}

void MTreeNode::addChildToArray(MTreeNode* child)
{
	m_children_array[m_child_count] = child;
	m_child_count++;
}

MTreeNode::MTreeNode(MTreeNode* parent, int i, int j, int distance) :
	m_parent(parent),
	m_children_array(new MTreeNode*[max_children]),
	m_i(i),
	m_j(j),
	m_distance(distance)
{ }

MTreeNode::~MTreeNode()
{
	delete[] m_children_array;
}

bool MTreeNode::isIndexesCorrect(int i, int j) const
{
	return abs(i - m_i) + abs(j - m_j) == 1;
}
