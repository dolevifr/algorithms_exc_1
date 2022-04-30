#include "general2.h"

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
			throw std::runtime_error("invalid number of edges given");
	}
	
	if (std::getline(file, buffer)) {
		std::istringstream iss(buffer);
		iss >> edge.fromVertex >> edge.toVertex;
	}

	return graph;
}