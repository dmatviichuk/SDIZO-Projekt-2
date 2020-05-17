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

    Edge *K, *KO;
    int **IncidenceMatrix, **nonDirectedGraphM;
    ElementsList **NeighborhoodList, **nonDirectedGraphL;
    int vertices, edge, density, edgeReverse;
    ElementsList *e1, *e2;
    bool *visited;

public:

    void array_Prim();
    void show();
    void list_Prim();
    void array_Dijkstra(int w);
    void list_Dijkstra(int w);
    void list_DFS(int w);
    void array_DFS(int w);
    bool checkCohesion();
    void randomGraph();
    void randomEdge();
    void replaceToNonDirectedGraph();
};

#endif //SDIZO_PROJEKT_2_GRAPH_H
