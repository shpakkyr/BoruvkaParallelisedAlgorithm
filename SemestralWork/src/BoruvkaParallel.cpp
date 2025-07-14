#include "BoruvkaParallel.h"
#include <algorithm>
#include <atomic>
#include <functional>

// Similar implementation as the single threaded version, but we divide edges into chunks
// and process them in parallel using threads.

static int p_findSet(std::vector<int> &parent, int v) {
    // Find the root of the component for vertex v with path compression
    if(parent[v] == v) return v;
    return parent[v] = p_findSet(parent, parent[v]);
}

static void p_unionSet(std::vector<int> &parent, std::vector<int> &rank, int a, int b) {
    // Merge two sets (components) using union by rank
    a = p_findSet(parent, a);
    b = p_findSet(parent, b);
    if(a != b) {
        if(rank[a] < rank[b]) std::swap(a,b);
        parent[b] = a;
        if(rank[a] == rank[b]) rank[a]++;
    }
}

int BoruvkaParallel::run() {
    // Number of vertices
    int V = graph.getV();
    // List of edges
    const auto &edges = graph.getEdges();
    std::vector<int> parent(V), rank(V,0);
    for (int i = 0; i < V; i++) parent[i] = i;

    //Number of components
    int numComponents = V;
    // Total weight of MST
    int mstWeight = 0;

    // Loop until we have only one component left
    while (numComponents > 1) {
        std::vector<int> cheapest(V, -1);
        int E = (int)edges.size();

        // Divide edges into chunks for threads
        std::vector<std::thread> workers;
        int chunkSize = (E + threadsCount - 1)/threadsCount;
        std::mutex mtx;

        auto worker = [&](int start, int end) {
            // Local array to store cheapest edges for this thread
            std::vector<int> localCheapest(V, -1);
            for (int i = start; i < end && i < E; i++) {
                int setU = p_findSet(parent, edges[i].u);
                int setV = p_findSet(parent, edges[i].v);
                // Skip edges within the same component
                if (setU == setV) continue;
                // Update the cheapest edge for each component
                if (localCheapest[setU] == -1 || edges[i].w < edges[localCheapest[setU]].w) {
                    localCheapest[setU] = i;
                }
                if (localCheapest[setV] == -1 || edges[i].w < edges[localCheapest[setV]].w) {
                    localCheapest[setV] = i;
                }
            }

            // Merge local results into the global cheapest array
            std::lock_guard<std::mutex> lk(mtx);
            for (int v = 0; v < V; v++) {
                if(localCheapest[v] != -1) {
                    if (cheapest[v] == -1 || edges[localCheapest[v]].w < edges[cheapest[v]].w) {
                        cheapest[v] = localCheapest[v];
                    }
                }
            }
        };

        // Launch threads to process edge chunks
        for (int t = 0; t < threadsCount; t++) {
            int start = t * chunkSize;
            int end = start + chunkSize;
            workers.emplace_back(worker, start, end);
        }

        // Wait for all threads to finish
        for (auto &w : workers) w.join();

        int oldComponents = numComponents;

        // Merge components based on the cheapest edges found
        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                int u = edges[cheapest[i]].u;
                int v = edges[cheapest[i]].v;
                int w = edges[cheapest[i]].w;

                int setU = p_findSet(parent, u);
                int setV = p_findSet(parent, v);
                if (setU != setV) {
                    mstWeight += w;
                    p_unionSet(parent, rank, setU, setV);
                    numComponents--;
                    if(numComponents == 1) break;
                }
            }
        }

        // If the number of components didn't change, it means we can't improve the MST further
        // This could happen if the graph is disconnected, but we assume a connected graph for MST
        if(numComponents == oldComponents) {
            break;
        }
    }

    return mstWeight;
}
