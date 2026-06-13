#pragma once
#include <string>

using std::string;

class GraphNode {
public:
	float x;
	float y;
	string label;
};

ostream& operator <<(ostream& os, const GraphNode node) {
	os << "(" << node.label << ", " << node.x << ", " << node.y << ")";
	return os;
}

