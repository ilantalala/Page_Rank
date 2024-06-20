#include "graph.hpp"
#include <vector>
#include <iostream>

void PageRank(Graph* graph, int n, float* rank) {
    // Define damping factor
    float d = 0.15f;
    unsigned int N = graph->getNumVertices();

    // Initialize rank array with equal probability for all vertices
    float initial_rank = 1.0f / N;
    for (unsigned int i = 0; i < N; ++i) {
        rank[i] = initial_rank;
    }

    // Temporary array for new ranks
    float* new_rank = new float[N];

    // Identify nodes with no outlinks
    std::vector<int> noLink;
    for (unsigned int i = 0; i < N; ++i) {
        if (graph->getAdjacencyLists()[i] == nullptr) {
            noLink.push_back(i);
        }
    }

    // Perform PageRank iterations
    while (n > 0) {
        // Initialize new rank values to zero
        for (unsigned int i = 0; i < N; ++i) {
            new_rank[i] = 0.0f;
        }

        // Sum the rank of nodes with no outlinks
        float sum_noLink = 0;
        for (int uj : noLink) {
            sum_noLink += rank[uj] / N;
        }

        // Calculate new ranks based on old ranks and graph structure
        for (unsigned int v = 0; v < N; ++v) {
            // Traverse the entire graph to find nodes pointing to v
            for (unsigned int u = 0; u < N; ++u) {
                Node* adjList = graph->getAdjacencyLists()[u];
                while (adjList != nullptr) {
                    if (adjList->v == v) { // Check if u points to v
                        // Get number of outgoing links from u (numVisits)
                        int numOutLinks = graph->getNumVisits()[u];

                        // Update new_rank using PageRank formula
                        if (numOutLinks > 0) {
                            new_rank[v] += (rank[u] / numOutLinks);
                        }
                    }
                    adjList = adjList->next;
                }
            }
        }

        // Add the contribution from noLink nodes to each new_rank
        for (unsigned int i = 0; i < N; ++i) {
            new_rank[i] += sum_noLink;
        }

        // Update rank array with new ranks
        for (unsigned int i = 0; i < N; ++i) {
            rank[i] = new_rank[i];
        }

        // Decrement iteration count
        n--;
    }

    // Clean up
    delete[] new_rank;
}
