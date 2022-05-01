#include "algorithms.h"
#include "utils.h"

int main(int argc, char** argv) {
	try {
		runAlgorithms(std::string(argv[1]));
	}
	catch (std::exception excp) {
		std::cout << excp.what() << std::endl;
		exit(1);
	}
}