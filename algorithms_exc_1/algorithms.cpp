#include "algorithms.h"

int Kruskal(const Graph& weightedGraph) {
	std::vector<Edge*> promisingSet;
	size_t graphSize = weightedGraph.getSize();
	Disjoint_Sets components(graphSize);
	int edgesCounter = 0, weight = 0;
	 
	auto edgeList = weightedGraph.getEdgeList();
	Edge_Quick_Sort()(edgeList);
	
	for (int i = 1; i <= graphSize; i++)
		components.makeSet(i);

	for (Edge* edge : edgeList) {
		int repU = components.find(edge->fromVertex);
		int repV = components.find(edge->toVertex);

		if (repU != repV) {
			edgesCounter++;
			weight += edge->weight;
			promisingSet.push_back(edge);
			components.Union(repU, repV);
		}
	}
	
	if (edgesCounter != graphSize - 1)
		throw "no MST";

	return weight;
}


int Prim(const Graph& weightedGraph) {
	size_t graphSize = weightedGraph.getSize();
	std::vector<vertexStatus*> arr;
	Weight_Queue queue;
	int weight = 0;

	for (int i = 1; i <= graphSize; i++)
		arr.push_back(new vertexStatus(i));
	
	arr[0]->min = 0;
	queue.build(arr);

	while (!queue.isEmpty()) {
		vertexStatus* u = queue.deleteMin();
		u->isInTree = true;
		weight += u->min;

		for (auto& adjVertex : weightedGraph[u->vertexLabel]) {
			vertexStatus* adjVertexStatus = arr[adjVertex.toVertex - 1];   // get current adjacent vertex status

			if (!adjVertexStatus->isInTree && adjVertex.weight < adjVertexStatus->min) {
				adjVertexStatus->min = adjVertex.weight;
				adjVertexStatus->parent = u->vertexLabel;
				queue.decreaseKey(adjVertexStatus->queueInd, adjVertexStatus->min);
			}
		}
	}

	for (auto& vert : arr)
		delete vert;

	arr.clear();
	return weight;
}


bool isConnected(const Graph& graph) {
	std::vector<Color> colors;
	int counter = 1; //first vertex isnt called by visit so starts from 1
	int start = 1;

	for (int i = 0; i <= graph.getSize(); i++) {
		colors.push_back(Color::WHITE) ;
	}

	visit(graph, colors, start, counter);
	return counter == graph.getSize();
}

void visit(const Graph& graph, std::vector<Color>& color, int vertexNum, int& counter) {
	color[vertexNum] = Color::GREY;

	for (auto& vert : graph[vertexNum]) {
		if (color[vert.toVertex] == Color::WHITE) {
			counter++;
			visit(graph, color, vert.toVertex,counter);
		}
	}
	color[vertexNum] = Color::BLACK;
}