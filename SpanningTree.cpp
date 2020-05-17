#include "SpanningTree.h"


using namespace std;

SpanningTree::SpanningTree(int vertices, int kr) {
    T = new ElementsList *[vertices];
    for (int i = 0; i < vertices; i++) {
        T[i] = NULL;
    }
    SizeT = vertices - 1;
    weight = 0;
    vertices = kr;
    kk = new Edge[vertices];
    a = 0;
}

SpanningTree::~SpanningTree() {
    ElementsList *e1, *e2;
    for (int i = 0; i <= SizeT; i++) {
        e1 = T[i];
        while (e1) {
            e2 = e1;
            e1 = e1->next;
            delete e2;
        }
    }

    delete[]T;
}

void SpanningTree::addEdge(Edge k) {
    ElementsList *e;

    weight += k.weight;
    e = new ElementsList;
    e->w = k.wk;
    e->weight = k.weight;
    e->next = T[k.wp];
    T[k.wp] = e;

    e = new ElementsList;
    e->w = k.wp;
    e->weight = k.weight;
    e->next = T[k.wk];
    T[k.wk] = e;

    kk[a] = k;
    a++;
}

void SpanningTree::show() {
    cout << endl;
    for (int i = 0; i < a; i++) {
        cout << "Krawedz " << i + 1 << ": ";
        cout << kk[i].wp << "<-->" << kk[i].wk << " [" << kk[i].weight << "] ";
        cout << endl;
    }
    cout << endl << endl << "Waga minimalnego drzewa rozpinajacego: " << weight << endl << endl;
}