#include "utils.h"
#include "algorithms.h"

Graph makeGraphFromFile(const std::string& fileName, Edge& edge) {
	std::fstream file(fileName);
	std::string buffer;
	int numOfVertexes;
	int numOfEdges;

	if (file.fail())
		throw std::runtime_error("invalid input");
	
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
			throw std::runtime_error("invalid input");
	}
	
	if (std::getline(file, buffer)) {
		std::istringstream iss(buffer);
		iss >> edge.fromVertex >> edge.toVertex;

		if (!iss.eof()) {
			throw std::runtime_error("invalid input");
		}
	}

	return graph;
}

void runAlgorithms(std::string fileName) {
	std::string str(fileName);
	Edge edgeToRemove(0, 0, 0);
	Graph graph = makeGraphFromFile(str, edgeToRemove);

	if (!isConnected(graph))
		throw std::invalid_argument("invalid input");
	
	int res = Kruskal(graph);
	std::cout << "Kruskal: <" << res << ">" << std::endl;
	res = Prim(graph);
	std::cout << "Prim: <" << res << ">" << std::endl;

	graph.removeEdge(edgeToRemove.fromVertex, edgeToRemove.toVertex);

	if (isConnected(graph)) {
		res = Kruskal(graph);
		std::cout << "Kruskal2: <" << res << ">" << std::endl;
	}
	else
		std::cout << "No MST" << std::endl;
}

std::vector<std::string> getAllTextFilesInFolder() {
	fs::path path = fs::current_path();
	std::string ext(".txt");
	std::vector<std::string> fileList;

	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == ext)
			fileList.push_back(p.path().stem().string() + ext);
	}

	return fileList;
}

void runTests() {
	auto fileList = getAllTextFilesInFolder();
	for (auto& file : fileList) {
		std::cout << "Test Name: " << file << std::endl;

		try {
			runAlgorithms(file);
		}
		catch (std::exception excp) {
			std::cout << excp.what() << std::endl;
			exit(1);
		}

		std::cout << "-----------------------" << std::endl;
	}
}