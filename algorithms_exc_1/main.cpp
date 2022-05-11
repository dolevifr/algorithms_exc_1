#include "algorithms.h"
#include "utils.h"

int main(int argc, char** argv) {
	
	std::ofstream outputFile(argv[2]);

	try {
		runAlgorithms(argv[1], outputFile);
	}
	catch (std::exception excp) {
		std::cout << excp.what() << std::endl;
		outputFile << excp.what() << std::endl;
		exit(1);
	}
}