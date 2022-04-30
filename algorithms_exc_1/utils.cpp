#include "utils.h"
#include "algorithms.h"

Graph makeGraphFromFile(const std::string& fileName, Edge& edge) {

	std::fstream file(fileName);
	//TODO: add file check
	std::string buffer;
	int numOfVertexes;
	int numOfEdges;

	std::getline(file, buffer);
	numOfVertexes = std::stoi(buffer);
	std::getline(file, buffer);
	numOfEdges = std::stoi(buffer);

	Graph graph(numOfVertexes);
	int to, from, weight;

	for (int i = 0; i < numOfEdges; i++) {
		std::getline(file, buffer);
		std::istringstream iss(buffer);
		iss >> to >> from >> weight;
		graph.addEdge(to, from, weight);
		
		if (file.eof()) 
			throw std::runtime_error("too few edges given");
	}
	
	if (std::getline(file, buffer)) {
		std::istringstream iss(buffer);
		iss >> edge.fromVertex >> edge.toVertex;

		if (!iss.eof()) {
			throw std::runtime_error("too many edges given");
		}
	}



	return graph;
}

void temp(char* fileName) {
	std::string str(fileName);
	Edge edgeToRemove(0, 0, 0);
	Graph graph = makeGraphFromFile(str, edgeToRemove);

	if (!isConnected(graph)) {
		throw std::invalid_argument("No MST");
	}

	int res = Kruskal(graph);
	std::cout << "Kruskal: " << res << std::endl;
	res = Prim(graph);
	std::cout << "Prim: " << res << std::endl;

	graph.removeEdge(edgeToRemove.fromVertex, edgeToRemove.toVertex);

	if (isConnected(graph)) {
		res = Kruskal(graph);
		std::cout << "Kruskal2: " << res << std::endl;
	}
	else
		std::cout << "No MST";
}