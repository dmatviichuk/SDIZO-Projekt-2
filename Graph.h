#ifndef SDIZO_PROJEKT_2_GRAPH_H
#define SDIZO_PROJEKT_2_GRAPH_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <queue>
#include <values.h>
#include "Edge.h"
#include "ElementsList.h"
#include "Stack.h"
#include "SpanningTree.h"

class Graph {
public:
    Graph(int w, int m);
    ~Graph();

    int **IncidenceMatrix, **nonDirectedGraphM;
    int vertices, edge, density, edgeReverse;
    bool *visited;

    Edge *K, *KO;
    ElementsList **NeighborhoodList, **nonDirectedGraphL;
    ElementsList *e1, *e2;

public:
    void show();
    void array_Dijkstra(int w);
    void list_Dijkstra(int w);
    void array_Ford(int w, int end);
    void list_Ford(int start, int end);
    void list_DFS(int w);
    void array_DFS(int w);
    void array_Prim();
    void list_Prim();
    bool checkCohesion();
    void randomGraph();
    void randomEdge();
    void replaceToNonDirectedGraph();
};

#endif //SDIZO_PROJEKT_2_GRAPH_H
