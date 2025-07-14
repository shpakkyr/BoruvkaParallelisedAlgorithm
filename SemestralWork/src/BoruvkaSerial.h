#ifndef BORUVKA_SERIAL_HPP
#define BORUVKA_SERIAL_HPP

#include "Graph.h"
#include <vector>

class BoruvkaSerial {
public:
    BoruvkaSerial(const Graph &g) : graph(g) {}
    int run();

private:
    const Graph &graph;
};

#endif
