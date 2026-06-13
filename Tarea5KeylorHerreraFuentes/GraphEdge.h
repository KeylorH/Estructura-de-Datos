#pragma once

class GraphEdge {
public:
	int source;
	int target;
	float weight;

	bool operator==(const GraphEdge& other) {
		return weight == other.weight;
	}
	bool operator<(const GraphEdge& other) {
		return weight < other.weight;
	}
	bool operator<=(const GraphEdge& other) {
		return weight <= other.weight;
	}
	bool operator>(const GraphEdge& other) {
		return weight > other.weight;
	}
	bool operator>=(const GraphEdge& other) {
		return weight >= other.weight;
	}
	bool operator!=(const GraphEdge& other) {
		return weight != other.weight;
	}
};

ostream& operator <<(ostream& os, const GraphEdge edge) {
	os << "(" << edge.source << ", " << edge.target << ", " << edge.weight << ")";
	return os;
}
