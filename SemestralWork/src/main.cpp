#include <iostream>
#include <string>
#include "Graph.h"
#include "BoruvkaSerial.h"
#include "BoruvkaParallel.h"
#include "Utils.h"

bool isValidNumber(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

int main(int argc, char **argv) {
    StringHolder name;

    if (argc < 2) {
        std::cerr << "Use --help for instructions.\n";
        return 1;
    }

    std::string inputFile = "../data/";
    std::string algo = "serial";
    int threadsCount = 2;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--help") {
            std::cout << name.getString();
            return 0;
        } else if (arg == "-f") {
            if (i+1 < argc) {
                inputFile += argv[++i];
            } else {
                std::cerr << "Missing argument (filename) after -f\n";
                return 1;
            }
        } else if (arg == "-a") {
            if (i+1 < argc) {
                algo = argv[++i];
                if (algo != "serial" && algo != "parallel") {
                    std::cerr << "Unknown algorithm: " << algo << "\n";
                    return 1;
                }
            } else {
                std::cerr << "Missing argument (algorithm) after -a\n";
                return 1;
            }
        } else if (arg == "-t") {
            if (i+1 < argc) {
                std::string threadArg = argv[++i];
                if (isValidNumber(threadArg)) {
                    threadsCount = std::stoi(threadArg);
                } else {
                    std::cerr << "Invalid number of threads: must be a positive integer.\n";
                    return 1;
                }
            } else {
                std::cerr << "Missing argument (number of threads) after -t\n";
                return 1;
            }
        } else {
            std::cerr << "Unknown switch: " << arg << "\n";
            return 1;
        }
    }

    if (inputFile.empty()) {
        std::cerr << "Input data missing. Use -f <filename>\n";
        return 1;
    }

    Graph g;
    if(!g.loadFromFile(inputFile)) {
        return 1;
    }

    if (algo == "serial") {
        BoruvkaSerial solver(g);
        Timer timer;
        int mstWeight = solver.run();
        double ms = timer.elapsedMilliseconds();
        std::cout << "MST weight (serial): " << mstWeight << "\n";
        std::cout << "Runtime: " << ms << " ms\n";
    } else {
        BoruvkaParallel solver(g, threadsCount);
        Timer timer;
        int mstWeight = solver.run();
        double ms = timer.elapsedMilliseconds();
        std::cout << "MST weight (parallel, " << threadsCount << " threads): " << mstWeight << "\n";
        std::cout << "Runtime: " << ms << " ms\n";
    }

    return 0;
}
