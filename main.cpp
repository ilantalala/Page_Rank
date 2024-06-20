#include <iostream>
#include "graph.hpp"
#include "pageRank.hpp"

// Function to print the adjacency lists of the graph
void printGraph(Graph* graph) {
    unsigned int numVertices = graph->getNumVertices();
    for (unsigned int i = 0; i < numVertices; ++i) {
        std::cout << "Node " << i << " neighbors:";
        Node* adjList = graph->getAdjacencyLists()[i];
        while (adjList != nullptr) {
            std::cout << " " << adjList->v;
            adjList = adjList->next;
        }
        std::cout << std::endl;
    }
}

int main() {
    Graph* graph = createGraph(4);

    // Add edges to the graph
    graph->addEdge(0, 1);
    graph->addEdge(0, 2);
    graph->addEdge(2, 0);
    graph->addEdge(2, 3);
    graph->addEdge(3, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 1);

    // Print the graph structure (adjacency lists)
    std::cout << "Graph structure:" << std::endl;
    printGraph(graph);
    std::cout << std::endl;

    // Perform PageRank
    const unsigned int numVertices = graph->getNumVertices();
    float rank[numVertices];  // Allocate an array for ranks
    PageRank(graph, 1, rank);  // 100 iterations

    // Print the rank of each node
    std::cout << "PageRank results after 1 iteration:" << std::endl;
    for (unsigned int i = 0; i < numVertices; ++i) {
        std::cout << "Rank of node " << i << ": " << rank[i] << std::endl;
    }

    // Clean up
    delete graph;

    return 0;
}
