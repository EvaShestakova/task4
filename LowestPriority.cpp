#include "LowestPriority.h"
#include "Node.h"

bool LowestPriority::operator()(const Node::pointer& left, const Node::pointer& right) const
{
	return left->getfreq() > right->getfreq();
}
