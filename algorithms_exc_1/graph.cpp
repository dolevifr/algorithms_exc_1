#include "graph.h"

// checks if an edge exists between vertex u and v
bool Graph::isAdjacent(int u, int v) const {
	if (!isVertexInRange(u))
		throw std::out_of_range("invalid input");

	auto res = findVertex(u, v);

	return res != nullptr;
}


void Graph::addEdge(int u, int v, int c) {
	if (!isVertexInRange(u) || !isVertexInRange(v))
		throw std::out_of_range("invalid input");

	Edge edge1(u, v, c);
	Edge edge2(v, u, c);
	vertexList[u - 1].append(edge1);
	vertexList[v - 1].append(edge2);
	edgeList.push_back(&vertexList[u - 1].getTail());
}


// checks if a given vertex exists in graph
bool Graph::isVertexInRange(size_t vertex) const {
	return size >= vertex;
}


void Graph::removeEdge(int u, int v) {
	auto res = findVertex(u, v);
	edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), &res.getItem()->data), edgeList.end());
	
	if (res != nullptr) {
		vertexList[u - 1].remove(res.getItem());

		auto res = findVertex(v, u);
		vertexList[v - 1].remove(res.getItem());
		edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), &res.getItem()->data), edgeList.end());
	}
	else
		throw std::out_of_range("invalid input");

}

// returns iterator of vertex if found in graph
Vertex::Iterator Graph::findVertex(int u, int v) const {
	auto matchData = [&v](const Edge& edge) { return edge.toVertex == v; };
	auto res = std::find_if(vertexList[u - 1].begin(), vertexList[u - 1].end(), matchData);

	return res;
}
