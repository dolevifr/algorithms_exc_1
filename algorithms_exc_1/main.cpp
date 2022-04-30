#include "algorithms.h"
#include "general2.h"

int main(int argc, char** argv) {
	std::string str(argv[1]);
	Edge edge(0, 0, 0);
	Graph graph = makeGraphFromFile(str, edge);
	std::cout << isConnected(graph);
	auto res = Kruskal(graph);
	auto res2 = Prim(graph);
	graph.removeEdge(edge.fromVertex, edge.toVertex);
	if (isConnected(graph)) {
		auto res3 = Kruskal(graph);
	}
	else
		std::cout << "graph is not connected";
	//Graph graph(6);

	//graph.addEdge(1, 2, 4);
	//graph.addEdge(1, 3, 4);
	//graph.addEdge(2, 3, 2);
	//graph.addEdge(3, 4, 3);
	//graph.addEdge(3, 5, 2);
	//graph.addEdge(3, 6, 4);
	//graph.addEdge(5, 6, 3);
	//graph.addEdge(4, 6, 3);


	
}