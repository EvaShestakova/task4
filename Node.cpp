#include "Node.h"

/*bool Node::operator<(const Node& oth) const
{
	return freq < oth.freq; 
}*/




string Node::getname() const
{
	if (ch == 0) {
		return name;
	}
	else {
		if (ch == 10) {
			return "\\n";
		}
		return string(1, static_cast<char>(ch));
	}
}
ostream& operator<<(ostream& os, const Node& node) {
	return os << "[" << node.getname() << "]=" << node.freq;
}