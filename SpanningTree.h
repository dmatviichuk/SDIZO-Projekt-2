#ifndef SDIZO_PROJEKT_2_SPANNINGTREE_H
#define SDIZO_PROJEKT_2_SPANNINGTREE_H



#include "Edge.h"
#include "ElementsList.h"
#include <iostream>
#include <cstdio>

class SpanningTree {
private:

    ElementsList **T;
    Edge *kk;
    int SizeT;
    int weight, vertices;
    int a;

public:

    SpanningTree(int vertices, int edge);
    ~SpanningTree();
    void addEdge(Edge k);
    void show();
};


#endif //SDIZO_PROJEKT_2_SPANNINGTREE_H
