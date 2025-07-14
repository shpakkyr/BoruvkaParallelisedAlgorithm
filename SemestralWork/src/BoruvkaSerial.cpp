#include "BoruvkaSerial.h"
#include <algorithm>

// Implementation of the single-threaded Borůvka's algorithm
// Steps:
// 1. Initialize a forest with separate components (each vertex as its own component).
// 2. While the number of components > 1:
//    - Find the cheapest edge for each component that connects it to another component.
//    - Add these edges to the result and merge the corresponding components.
// The result is the MST, and the sum of MST weights is returned.

static int findSet(std::vector<int> &parent, int v) {
    // Find the root of the component for vertex v with path compression
    if(parent[v] == v) return v;
    return parent[v] = findSet(parent, parent[v]);
}

static void unionSet(std::vector<int> &parent, std::vector<int> &rank, int a, int b) {
    // Merge two sets (components) using union by rank
    a = findSet(parent, a);
    b = findSet(parent, b);
    if(a != b) {
        if(rank[a] < rank[b]) std::swap(a,b);
        parent[b] = a;
        if(rank[a] == rank[b]) rank[a]++;
    }
}

int BoruvkaSerial::run() {
    int V = graph.getV();
    const auto &edges = graph.getEdges();
    std::vector<int> parent(V), rank(V,0);
    for (int i = 0; i < V; i++) parent[i] = i;

    int numComponents = V;
    int mstWeight = 0;

    while (numComponents > 1) {
        // For each component, find the cheapest edge
        std::vector<int> cheapest(V, -1);

        for (size_t i = 0; i < edges.size(); i++) {
            int setU = findSet(parent, edges[i].u);
            int setV = findSet(parent, edges[i].v);
            if (setU == setV) continue;

            // The edge connects two components
            // If the component doesn't have the cheapest edge yet, or this edge is cheaper:
            if (cheapest[setU] == -1 || edges[i].w < edges[cheapest[setU]].w) {
                cheapest[setU] = (int)i;
            }
            if (cheapest[setV] == -1 || edges[i].w < edges[cheapest[setV]].w) {
                cheapest[setV] = (int)i;
            }
        }

        // Add found edges to MST
        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                int u = edges[cheapest[i]].u;
                int v = edges[cheapest[i]].v;
                int w = edges[cheapest[i]].w;

                int setU = findSet(parent, u);
                int setV = findSet(parent, v);
                if (setU != setV) {
                    mstWeight += w;
                    unionSet(parent, rank, setU, setV);
                    numComponents--;
                }
            }
        }
    }

    return mstWeight;
}
