#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool Graph::loadFromFile(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error: File can't be opened: " << filename << "\n";
        return false;
    }

    std::string firstLine;
    if (!std::getline(in, firstLine)) {
        std::cerr << "Error: File is empty or missing the first line.\n";
        return false;
    }

    std::istringstream firstLineStream(firstLine);
    if (!(firstLineStream >> V >> E) || !(firstLineStream >> std::ws).eof() || V <= 0 || E <= 0) {
        std::cerr << "Error: First line must contain exactly two positive integers (V and E).\n";
        return false;
    }

    edges.resize(E);

    std::string line;
    for (int i = 0; i < E; i++) {
        if (!std::getline(in, line)) {
            std::cerr << "Error: File does not contain enough lines for the specified number of edges.\n";
            return false;
        }

        std::istringstream edgeStream(line);
        int u, v, w;
        if (!(edgeStream >> u >> v >> w) || !(edgeStream >> std::ws).eof()) {
            std::cerr << "Error: Wrong format of edge on line " << i + 2 << ": " << line << "\n";
            return false;
        }

        if (u < 0 || v < 0 || w < 0) {
            std::cerr << "Error: Edge contains a negative value on line " << i + 2 << ": " << line << "\n";
            return false;
        }

        edges[i] = {u, v, w};
    }

    if (std::getline(in, line)) {
        std::cerr << "Error: File contains more lines than expected.\n";
        return false;
    }

    return true;
}
