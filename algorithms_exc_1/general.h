#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>


struct Edge {
	int fromVertex;
	int toVertex;
	int weight;

	Edge(int from, int to, int weight) : fromVertex(from), toVertex(to), weight(weight) {};
	inline bool operator>(const Edge& edge) { return this->weight > edge.weight;}
};
enum class Color { WHITE, GREY, BLACK };

const int INF = std::numeric_limits<int>::max();
const int DEFAULT_MAX_CONTAINER_SIZE = 100;
#endif