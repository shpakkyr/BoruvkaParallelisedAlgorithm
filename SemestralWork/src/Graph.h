#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

struct Edge {
    int u;
    int v;
    int w;
};

class Graph {
public:
    Graph() : V(0), E(0) {}
    bool loadFromFile(const std::string &filename);

    int getV() const { return V; }
    int getE() const { return E; }
    const std::vector<Edge> &getEdges() const { return edges; }

private:
    int V;
    int E;
    std::vector<Edge> edges;
};

#endif
