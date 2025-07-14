#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <string>

class Timer {
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    double elapsedMilliseconds() {
        auto end = std::chrono::high_resolution_clock::now();
        return (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    std::string getString();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

class StringHolder {
public:
    StringHolder();
    [[nodiscard]] std::string getString() const;

private:
    const std::string rules = "\n--help                                                                   Show how to use the algorithm\n"
                              " -f <filename>                                                           Indicator for reading the file name\n"
                              " -a serial|parallel                                                      Indicator for reading the type of program which should be run (eg. serial or parallel)\n"
                              " -t <count>                                                              Indicator of how many threads must be used within program running in parallel config\n"
                              "./SemestralWork -f <inputfile> -a <serial|parallel> [-t <threads>]       Format which is used to start the program\n\n"
                              "Example of running:\n"
                              "./SemestralWork -f test_simple.txt -a serial                             Run serial algorithm in 1 thread\n"
                              "./SemestralWork -f test_simple.txt -a parallel -t 4                      Run parallel algorithm in 4 threads\n";
};

#endif
