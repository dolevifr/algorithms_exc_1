#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "general.h"
#include "graph.h"
#include "disjoint_sets.h"
#include "priority_queue.h"
#include "quick_sort.h"

struct vertexStatus {
	bool	isInTree = false;
	int		min = INF;
	size_t	parent = 0;
	size_t	vertexLabel;
	size_t	queueInd;

	vertexStatus(int i) : vertexLabel(i), queueInd(i - 1) { };
};

struct Weight_Queue : public Priority_Queue<vertexStatus*> {
	Weight_Queue() : Priority_Queue(
		[](const vertexStatus* ver1, const vertexStatus* ver2) { return ver1->min < ver2->min; },
		[](vertexStatus* ver, int newKey) {ver->min = newKey; },
		[](vertexStatus* ver1, vertexStatus* ver2) { std::swap(ver1->queueInd, ver2->queueInd); }
	) {}

	vertexStatus* deleteMin() { return Priority_Queue::deleteRoot(); }
	void decreaseKey(int index, int newKey) { return Priority_Queue::fixUpwards(index, newKey); };
};

int Kruskal(const Graph& weightedGraph);
int Prim(const Graph& weightedGraph);
bool isConnected(const Graph& graph);
void visit(const Graph& graph, std::vector<Color>& color, int vertexNum, int& counter);

#endif