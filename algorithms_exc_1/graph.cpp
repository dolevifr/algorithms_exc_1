#include "graph.h"

bool Graph::isAdjacent(int u, int v) const {
	if (!isVertexInRange(u))
		throw std::out_of_range("vertex does not exist");

	auto res = findVertex(u, v);

	return res != nullptr;
}


void Graph::addEdge(int u, int v, int c) {
	if (!isVertexInRange(u))
		throw std::out_of_range("vertex does not exist");

	Edge edge1(u, v, c);
	Edge edge2(v, u, c);
	vertexList[u - 1].append(edge1);
	vertexList[v - 1].append(edge2);
	edgeList.push_back(&vertexList[u - 1].getTail());
}



bool Graph::isVertexInRange(size_t vertexList) const {
	return size >= vertexList;
}


void Graph::removeEdge(int u, int v) {
	auto res = findVertex(u, v);

	if (res != nullptr) {
		vertexList[u - 1].remove(res.getItem());

		auto res = findVertex(v, u);
		vertexList[v - 1].remove(res.getItem());
	}
	else
		throw std::out_of_range("edge to remove was not found in graph");
}


Vertex::Iterator Graph::findVertex(int u, int v) const {
	auto matchData = [&v](const Edge& edge) { return edge.toVertex == v; };
	auto res = std::find_if(vertexList[u - 1].begin(), vertexList[u - 1].end(), matchData);

	return res;
}
