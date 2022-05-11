#include "utils.h"
#include "algorithms.h"

Graph* makeGraphFromFile(const std::string& fileName, Edge& edge) {
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

	Graph* graph = new Graph(numOfVertexes);
	int to, from, weight;

	for (int i = 0; i < numOfEdges; i++) {
		std::getline(file, buffer);
		std::istringstream iss(buffer);
		
		if (!(iss >> to >> from >> weight))
			throw std::runtime_error("invalid input");

		(*graph).addEdge(to, from, weight);
		
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

void runAlgorithms(std::string inputFile, std::ofstream& outputFile) {
	std::string str(inputFile);
	Edge edgeToRemove(0, 0, 0);
	Graph* graph = makeGraphFromFile(str, edgeToRemove);

	if (!isConnected(*graph))
		throw std::runtime_error("invalid input");
	
	int res = Kruskal(*graph);
	std::cout << "Kruskal: <" << res << ">" << std::endl;
	outputFile << "Kruskal: <" << res << ">" << std::endl;

	res = Prim(*graph);
	std::cout << "Prim: <" << res << ">" << std::endl;
	outputFile << "Prim: <" << res << ">" << std::endl;

	(*graph).removeEdge(edgeToRemove.fromVertex, edgeToRemove.toVertex);

	if (isConnected(*graph)) {
		res = Kruskal(*graph);
		std::cout << "Kruskal2: <" << res << ">" << std::endl;
		outputFile << "Kruskal2: <" << res << ">" << std::endl;
	}
	else {
		std::cout << "Kruskal2: No MST" << std::endl;
		outputFile << "Kruskal2: <" << res << ">" << std::endl;
	}

	delete graph;
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

void runTests(std::ofstream& outputFile) {
	auto fileList = getAllTextFilesInFolder();
	for (auto& file : fileList) {
		std::cout << "Test Name: " << file << std::endl;
		outputFile << "Test Name: " << file << std::endl;

		try {
			runAlgorithms(file, outputFile);
		}
		catch (std::exception excp) {
			std::cout << excp.what() << std::endl;
			outputFile << excp.what() << std::endl;
		}

		std::cout << "---------------------------------------------" << std::endl;
		outputFile << "---------------------------------------------" << std::endl;
	}
}

const std::string& isDigits(const std::string& str) {
	if (std::all_of(str.begin(), str.end(), ::isdigit))
		return str;
	else
		throw std::invalid_argument("invalid input");
}