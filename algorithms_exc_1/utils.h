#ifndef _UTILS_H_
#define _UTILS_H_

#include "graph.h"
#include "general.h"

Graph* makeGraphFromFile(const std::string& fileName, Edge& edge);
std::vector<std::string> getAllTextFilesInFolder();

void runAlgorithms(std::string inputFile, std::ofstream& outputFile);
void runTests(std::ofstream& outputFile);
#endif