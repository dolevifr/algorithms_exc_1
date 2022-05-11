#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "linked_list.h"

// a simple directed graph class
class Graph {
private:
	std::vector<Edge*>	edgeList;
	Vertex*				vertexList;
	size_t				size;

	Vertex::Iterator findVertex(int u, int v) const;
	bool isVertexInRange(size_t vertexList) const;

public:
	Graph(int num) : vertexList(new Vertex[num]), size(num) {};

	std::vector<Edge*> getEdgeList() const { return edgeList; }; // returns copy of internal edge list
	size_t getSize() const { return size; };

	static Graph MakeEmptyGraph(int n) { return Graph(n); };

	bool isAdjacent(int u, int v) const;
	void addEdge(int u, int v, int c);
	void removeEdge(int u, int v);
	void clear() { delete vertexList; size = 0; };

	Vertex& operator[](int i) const { return vertexList[i - 1]; };
};
#endif