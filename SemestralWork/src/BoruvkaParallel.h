#ifndef BORUVKA_PARALLEL_HPP
#define BORUVKA_PARALLEL_HPP

#include "Graph.h"
#include <vector>
#include <thread>
#include <mutex>

class BoruvkaParallel {
public:
    BoruvkaParallel(const Graph &g, int numThreads = 2) : graph(g), threadsCount(numThreads) {}
    int run();

private:
    const Graph &graph;
    int threadsCount;
};

#endif
