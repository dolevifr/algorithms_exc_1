#include "algorithms.h"
#include "utils.h"

int main(int argc, char** argv) {
	auto fileList = getAllTextFilesInFolder();
	for (auto& file : fileList) {
		std::cout << "Test Name: " << file << std::endl;

		try {
			runAlgorithms(file);
		}
		catch (std::exception excp) {
			std::cout << excp.what() << std::endl;
		}

		std::cout << "-----------------------" << std::endl;
	}
}