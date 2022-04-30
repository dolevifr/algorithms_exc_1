#include "algorithms.h"
#include "utils.h"

int main(int argc, char** argv) {
	/*
	try {
		temp(argv[1]);
	}
	catch (std::exception excp) {
		std::cout << excp.what() << std::endl;
	}
	*/

	auto fileList = getAllTextFilesInFolder();

	for (auto& file : fileList) {
		std::cout << "Test name: " << file << std::endl;
		try {
			temp(file);
		}
		catch (std::exception excp) {
			std::cout << excp.what() << std::endl;
		}
		std::cout << "###################" << std::endl;
	}
}