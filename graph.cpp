#include "graph.hpp"

Node* createNode(vertex v) {
    return new Node(v);
}

Graph::Graph(unsigned int vertices) : numVertices(vertices) {
    adjacencyLists = new Node*[vertices];
    numVisits = new int[vertices];
    num_visits_mutexes = new mutex[vertices];

    for (unsigned int i = 0; i < vertices; ++i) {
        adjacencyLists[i] = nullptr;
        numVisits[i] = 0;
        // std::mutex does not require explicit initialization
    }
}

Graph::~Graph() {
    for (unsigned int i = 0; i < numVertices; ++i) {
        Node* node = adjacencyLists[i];
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete[] adjacencyLists;
    delete[] numVisits;
    delete[] num_visits_mutexes;
}

void Graph::addEdge(vertex source, vertex destination) {
    // Check if nodes exist, create if they don't
    if (source >= numVertices) {
        // Expand adjacencyLists array if needed
        Node** newAdjacencyLists = new Node*[source + 1];
        int* newNumVisits = new int[source + 1];
        std::copy(adjacencyLists, adjacencyLists + numVertices, newAdjacencyLists);
        std::copy(numVisits, numVisits + numVertices, newNumVisits);

        // Initialize new elements to nullptr
        for (unsigned int i = numVertices; i <= source; ++i) {
            newAdjacencyLists[i] = nullptr;
            newNumVisits[i] = 0;
        }

        // Delete old arrays and update pointers
        delete[] adjacencyLists;
        delete[] numVisits;
        adjacencyLists = newAdjacencyLists;
        numVisits = newNumVisits;

        // Update numVertices
        numVertices = source + 1;
    }
    if (destination >= numVertices) {
        // Expand adjacencyLists array if needed
        Node** newAdjacencyLists = new Node*[destination + 1];
        int* newNumVisits = new int[destination + 1];
        std::copy(adjacencyLists, adjacencyLists + numVertices, newAdjacencyLists);
        std::copy(numVisits, numVisits + numVertices, newNumVisits);

        // Initialize new elements to nullptr
        for (unsigned int i = numVertices; i <= destination; ++i) {
            newAdjacencyLists[i] = nullptr;
            newNumVisits[i] = 0;
        }

        // Delete old arrays and update pointers
        delete[] adjacencyLists;
        delete[] numVisits;
        adjacencyLists = newAdjacencyLists;
        numVisits = newNumVisits;

        // Update numVertices
        numVertices = destination + 1;
    }

    // Check if edge already exists
    Node* currentNode = adjacencyLists[source];
    while (currentNode != nullptr) {
        if (currentNode->v == destination) {
            // Edge already exists, increment numVisits and return
            numVisits[source]++;
            return;
        }
        currentNode = currentNode->next;
    }

    // Edge doesn't exist, create new node for destination
    Node* node = createNode(destination);
    node->next = adjacencyLists[source];
    adjacencyLists[source] = node;
    numVisits[source]++;
    node->myNeighbors.push_back(source);
}



// Optional utility function to create a Graph object
Graph* createGraph(int vertices) {
    return new Graph(vertices);
}
