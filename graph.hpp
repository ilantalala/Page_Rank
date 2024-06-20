#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <mutex>
#include <list>
// Use a type alias for vertex and mutex
using vertex = int;
using mutex = std::mutex;

class Node {
public:
    vertex v;
    Node* next;
    std::list<int> myNeighbors;
    Node(vertex v) : v(v), next(nullptr) {}
};

class Graph {
public:
    Graph(unsigned int numVertices);
    ~Graph();

    void addEdge(vertex source, vertex destination);

    unsigned int getNumVertices() const { return numVertices; } 
    Node** getAdjacencyLists() const { return adjacencyLists; }
    int* getNumVisits() const { return numVisits; }//number of outlinks
    mutex* getNumVisitsMutexes() const { return num_visits_mutexes; }

private:
    unsigned int numVertices;
    Node** adjacencyLists;
    int* numVisits; // Number of times a vertex has been visited
    mutex* num_visits_mutexes; // Mutex for each vertex
};


Node* createNode(vertex v);
void addEdge(Graph* graph, vertex source, vertex destination);
Graph* createGraph(int vertices);

#endif
