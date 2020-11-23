#pragma once
#include "Node.h"
class Node;
class LowestPriority
{
public:
	bool operator()(const Node::pointer& left, const Node::pointer& right) const;
};

