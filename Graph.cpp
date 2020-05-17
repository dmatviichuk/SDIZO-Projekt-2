#include "Graph.h"
#include "Time.h"

using namespace std;

Graph::Graph(int w, int m) {
    edge = m;
    vertices = w;
    IncidenceMatrix = new int *[vertices];
    nonDirectedGraphM = new int *[vertices];
    NeighborhoodList = new ElementsList *[vertices];
    nonDirectedGraphL = new ElementsList *[vertices];
    K = new Edge[edge];
    KO = new Edge[edge];
    edgeReverse = 0;
}

Graph::~Graph() {
    int i;
    for (int i = 0; i < vertices; i++) {
        e1 = NeighborhoodList[i];
        while (e1) {
            e2 = e1;
            e1 = e1->next;
            delete e2;
        }
    }
    delete[] NeighborhoodList;


    for (i = 0; i < vertices; i++) delete[] IncidenceMatrix[i];
    delete[] IncidenceMatrix;


}

void Graph::replaceToNonDirectedGraph() {
    int i, j;
    for (i = 0; i < vertices; i++)
        nonDirectedGraphM[i] = new int[edge];
    for (i = 0; i < vertices; i++)
        for (j = 0; j < edge; j++) {
            nonDirectedGraphM[i][j] = 0;
        }

    for (i = 0; i < vertices; i++)
        nonDirectedGraphL[i] = NULL;

    for (i = 0; i < edge; i++) {
        j = 0;
        while (j < edgeReverse) {

            if (KO[j].wp == K[i].wp && KO[j].wk == K[i].wk) {
                break;
            } else j++;
        }
        if (j == edgeReverse) {
            KO[edgeReverse].wp = K[i].wk;
            KO[edgeReverse].wk = K[i].wp;
            KO[edgeReverse].weight = K[i].weight;
            edgeReverse++;
        }
    }

    int wp, wk, weight;
    for (int i = 0; i < edgeReverse; i++) {
        wp = KO[i].wp;
        wk = KO[i].wk;
        weight = KO[i].weight;
        e1 = new ElementsList;
        e1->w = wk;
        e1->weight = weight;
        e1->next = nonDirectedGraphL[wp];
        nonDirectedGraphL[wp] = e1;
        e2 = new ElementsList;
        wp = KO[i].wk;
        wk = KO[i].wp;
        weight = KO[i].weight;
        e2->w = wk;
        e2->weight = weight;
        e2->next = nonDirectedGraphL[wp];
        nonDirectedGraphL[wp] = e2;

        nonDirectedGraphM[KO[i].wp][i] = 1;
        nonDirectedGraphM[KO[i].wk][i] = 1;
    }

}

void Graph::randomEdge() {
    int c = 0;
    int *T;
    int b, ADD1, ADD2, a, i, j;
    int computeDegree = 0;
    int *InTree;
    int *noInTree;
    a = vertices;
    noInTree = new int[a];
    for (i = 0; i < a; i++) {
        noInTree[i] = i;
    }
    InTree = new int[a];
    b = rand() % a;
    ADD1 = noInTree[b];
    noInTree[b] = noInTree[a - 1];
    a--;
    InTree[c] = ADD1;
    c++;

    for (i = 0; i < (vertices - 1); i++) {
        b = rand() % c;
        ADD1 = InTree[b];

        b = rand() % a;
        ADD2 = noInTree[b];
        noInTree[b] = noInTree[a - 1];
        a--;
        InTree[c] = ADD2;
        c++;
        K[i].wp = ADD1;
        K[i].wk = ADD2;
    }
    for (i = 0; i < (vertices - 1); i++) {

        b = rand() % vertices;
        swap(K[b].wk, K[b].wp);

    }

    for (i = vertices - 1; i < edge; i++) {
        a = vertices;
        T = new int[a];
        for (int k = 0; k < a; k++) {
            T[k] = k;
        }

        b = rand() % a;
        ADD1 = T[b];
        T[b] = T[a - 1];
        a--;
        while (true) {

            computeDegree = 0;
            for (j = 0; j < i; j++) {
                if (K[j].wp == ADD1)
                    computeDegree++;
                if (computeDegree == vertices - 1) break;
            }

            if (computeDegree == vertices - 1) {
                b = rand() % a;
                ADD1 = T[b];
                T[b] = T[a - 1];
                a--;
            } else break;
        }

        a = vertices;
        for (int k = 0; k < a; k++) {
            T[k] = k;
        }

        T[ADD1] = T[a - 1];
        a--;

        b = rand() % a;
        ADD2 = T[b];
        T[b] = T[a - 1];
        a--;

        for (j = 0; j < i; j++) {
            while (ADD1 == K[j].wp && ADD2 == K[j].wk) {
                b = rand() % a;
                ADD2 = T[b];
                T[b] = T[a - 1];
                a--;
                j = 0;
            }
        }
        K[i].wp = ADD1;
        K[i].wk = ADD2;
        delete[]T;
    }

    for (i = 0; i < edge; i++)
        K[i].weight = (rand() % 9) + 1;

    delete[] noInTree;
    delete[] InTree;
}

void Graph::randomGraph() {
    int i, j;
    for (i = 0; i < vertices; i++)
        IncidenceMatrix[i] = new int[edge];
    for (i = 0; i < vertices; i++)
        for (j = 0; j < edge; j++) {
            IncidenceMatrix[i][j] = 0;
        }

    for (i = 0; i < vertices; i++)
        NeighborhoodList[i] = NULL;

    randomEdge();
    replaceToNonDirectedGraph();
    for (i = 0; i < edge; i++) {
        int wp = K[i].wp;
        int wk = K[i].wk;
        int weight = K[i].weight;
        e1 = new ElementsList;
        e1->w = wk;
        e1->weight = weight;
        e1->next = NeighborhoodList[wp];
        NeighborhoodList[wp] = e1;

        IncidenceMatrix[wp][i] = 1;
        IncidenceMatrix[wk][i] = -1;
    }

}

bool Graph::checkCohesion() {
    Stack stack;
    int w, u, i;
    int compute = 0;

    visited = new bool[vertices];
    for (i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    stack.push(0);
    visited[0] = true;

    while (!stack.empty()) {
        w = stack.top();
        stack.pop();
        compute++;
        for (e1 = nonDirectedGraphL[w]; e1; e1 = e1->next) {
            u = e1->w;
            if (!visited[u]) {
                visited[u] = true;
                stack.push(u);
            }
        }
    }
    delete[]visited;
    if (compute == vertices)
        return true;

    else return false;
}

void Graph::array_DFS(int w) {
    int i, j;
    Time time;
    Stack stack;
    visited = new bool[vertices];
    for (i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    cout << "Graf nieskierowany:" << endl;

    cout << "      ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << i;

    }
    cout << endl << "      ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < vertices; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < edgeReverse; j++)
            cout << setw(3) << nonDirectedGraphM[i][j];
        cout << endl;
    }
    cout << endl;
    cout << "Wagi: ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << KO[i].weight;
    }
    cout << endl << endl;
    cout << "Odwiedziono wierzchołki:" << endl;
    time.TimeStart();
    stack.push(w);
    while (!stack.empty()) {

        w = stack.top();
        stack.pop();

        if (!visited[w]) {
            visited[w] = true;
            for (i = edge - 1; i >= 0; i--) {
                if (nonDirectedGraphM[w][i] != 0)
                    for (j = 0; j < vertices; j++)
                        if (j != w && nonDirectedGraphM[j][i] != 0) {
                            if (!visited[j]) {
                                stack.push(j);
                            }
                        }

            }
            cout << w << ", ";
        }
    }
    cout << endl << endl;

    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    delete[]visited;
    stack.~Stack();
}

void Graph::list_DFS(int w) {
    Time time;
    Stack stack;
    int u, i;

    visited = new bool[vertices];
    for (i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    cout << endl << "Graf nieskierowany: " << endl;
    for (i = 0; i < vertices; i++) {
        cout << "[" << i << "] =";
        e1 = nonDirectedGraphL[i];
        while (e1) {
            cout << setw(3) << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "Odwiedziono wierzchołki:" << endl << endl;
    time.TimeStart();
    stack.push(w);

    while (!stack.empty()) {
        w = stack.top();
        stack.pop();

        if (!visited[w]) {
            visited[w] = true;
            for (e1 = nonDirectedGraphL[w]; e1; e1 = e1->next) {
                u = e1->w;
                if (!visited[u]) {
                    stack.push(u);
                }
            }
            cout << w << ", ";
        }

    }
    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    delete[]visited;
    stack.~Stack();
}

void Graph::array_Dijkstra(int w) {
    int root, node, sizeHeap, procreator, leftSon, rightSon, costMin, sonMin, son, *costs, *predecessors, *heap, *positionHeap;
    Time time;
    Stack stack;
    int width, i, j, l;
    costs = new int[vertices];
    predecessors = new int[vertices];
    visited = new bool[vertices];
    heap = new int[vertices];
    positionHeap = new int[vertices];

    for (i = 0; i < vertices; i++) {
        costs[i] = MAXINT;
        predecessors[i] = -1;
        visited[i] = false;
        heap[i] = positionHeap[i] = i;
    }


    time.TimeStart();
    sizeHeap = vertices;

    costs[w] = 0;
    node = heap[0];
    heap[0] = heap[w];
    heap[w] = node;
    positionHeap[w] = 0;
    positionHeap[0] = w;

    for (i = 0; i < vertices; i++) {
        root = heap[0];

        heap[0] = heap[--sizeHeap];
        positionHeap[heap[0]] = procreator = 0;
        while (true) {
            leftSon = procreator + procreator + 1;
            rightSon = leftSon + 1;
            if (leftSon >= sizeHeap) break;
            costMin = costs[heap[leftSon]];
            sonMin = leftSon;
            if ((rightSon < sizeHeap) && (costMin > costs[heap[rightSon]])) {
                costMin = costs[heap[rightSon]];
                sonMin = rightSon;
            }
            if (costs[heap[procreator]] <= costMin)
                break;
            node = heap[procreator];
            heap[procreator] = heap[sonMin];
            heap[sonMin] = node;
            positionHeap[heap[procreator]] = procreator;
            positionHeap[heap[sonMin]] = sonMin;
            procreator = sonMin;
        }

        visited[root] = true;

        for (l = 0; l < edge; l++) {
            if (IncidenceMatrix[root][l] != 0)
                for (j = 0; j < vertices; j++)
                    if (j != root && IncidenceMatrix[j][l] == -1 && !visited[j] &&
                        (costs[j] > costs[root] + K[l].weight)) {
                        costs[j] = costs[root] + K[l].weight;
                        predecessors[j] = root;

                        for (son = positionHeap[j]; son; son = procreator) {
                            procreator = son / 2;
                            if (costs[heap[procreator]] <= costs[heap[son]])
                                break;
                            node = heap[procreator];
                            heap[procreator] = heap[son];
                            heap[son] = node;
                            positionHeap[heap[procreator]] = procreator;
                            positionHeap[heap[son]] = son;
                        }
                    }
        }
    }
    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    cout << endl;

    cout << "Najkrótsza ścieżka z wierzchołka " << w << ":" << endl;
    for (i = 0; i < vertices; i++) {
        width = -2;

        cout << i << ": ";


        if (costs[i] == MAXINT || costs[i] < 0)
            cout << "Brak" << endl;
        else {
            for (j = i; j > -1; j = predecessors[j]) {
                stack.push(j);
                width = width + 2;
            }

            while (!stack.empty()) {
                cout << stack.top() << " ";
                stack.pop();
            }
            for (j = 0; j < vertices - width; j++)
                cout << " ";
            cout << setw(5) << "(" << costs[i] << ")" << endl;
        }
    }
    cout << endl << endl;
}

void Graph::list_Dijkstra(int w) {
    int root, node, sizeHeap, procreator, leftSon, rightSon, costMin, sonMin, son, *costs, *predecessors, *heap, *positionHeap;
    Time time;
    Stack stack;
    int width, i, j;
    costs = new int[vertices];
    predecessors = new int[vertices];
    visited = new bool[vertices];
    heap = new int[vertices];
    positionHeap = new int[vertices];

    for (i = 0; i < vertices; i++) {
        costs[i] = MAXINT;
        predecessors[i] = -1;
        visited[i] = false;
        heap[i] = positionHeap[i] = i;
    }
    time.TimeStart();
    sizeHeap = vertices;

    costs[w] = 0;
    node = heap[0];
    heap[0] = heap[w];
    heap[w] = node;
    positionHeap[w] = 0;
    positionHeap[0] = w;

    for (i = 0; i < vertices; i++) {
        root = heap[0];

        heap[0] = heap[--sizeHeap];
        positionHeap[heap[0]] = procreator = 0;
        while (true) {
            leftSon = procreator + procreator + 1;
            rightSon = leftSon + 1;
            if (leftSon >= sizeHeap) break;
            costMin = costs[heap[leftSon]];
            sonMin = leftSon;
            if ((rightSon < sizeHeap) && (costMin > costs[heap[rightSon]])) {
                costMin = costs[heap[rightSon]];
                sonMin = rightSon;
            }
            if (costs[heap[procreator]] <= costMin)
                break;
            node = heap[procreator];
            heap[procreator] = heap[sonMin];
            heap[sonMin] = node;
            positionHeap[heap[procreator]] = procreator;
            positionHeap[heap[sonMin]] = sonMin;
            procreator = sonMin;
        }

        visited[root] = true;

        if (NeighborhoodList[root] != NULL)
            for (e1 = NeighborhoodList[root]; e1; e1 = e1->next)
                if (!visited[e1->w] && (costs[e1->w] > costs[root] + e1->weight)) {
                    costs[e1->w] = costs[root] + e1->weight;
                    predecessors[e1->w] = root;

                    for (son = positionHeap[e1->w]; son; son = procreator) {
                        procreator = son / 2;
                        if (costs[heap[procreator]] <= costs[heap[son]])
                            break;
                        node = heap[procreator];
                        heap[procreator] = heap[son];
                        heap[son] = node;
                        positionHeap[heap[procreator]] = procreator;
                        positionHeap[heap[son]] = son;
                    }
                }
    }
    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    cout << endl;

    cout << "Najkrótsza ścieżka z wierzchołka " << w << ":" << endl;
    for (i = 0; i < vertices; i++) {
        width = -2;

        cout << i << ": ";


        if (costs[i] == MAXINT || costs[i] < 0)
            cout << "Brak" << endl;
        else {
            for (j = i; j > -1; j = predecessors[j]) {
                stack.push(j);
                width = width + 2;
            }

            while (!stack.empty()) {
                cout << stack.top() << " ";
                stack.pop();
            }
            for (j = 0; j < vertices - width; j++)
                cout << " ";
            cout << setw(5) << "(" << costs[i] << ")" << endl;
        }
    }
    cout << endl << endl;
}

void Graph::array_Prim() {
    int w, i, j, g;
    Time time;
    Edge edge;
    priority_queue<Edge, vector<Edge>, Edge> queue;
    //SpanningTree *tree = new SpanningTree(vertices, edge);
    visited = new bool[vertices];
    for (i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    cout << "Graf nieskierowany:" << endl;

    cout << "      ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << i;

    }
    cout << endl << "      ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < vertices; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < edgeReverse; j++)
            cout << setw(3) << nonDirectedGraphM[i][j];
        cout << endl;
    }
    cout << endl;
    cout << "Wagi: ";
    for (i = 0; i < edgeReverse; i++) {
        cout << setw(3) << KO[i].weight;
    }
    cout << endl << endl;
    time.TimeStart();

    w = 0;
    visited[w] = true;
    for (i = 1; i < vertices; i++) {
        for (g = 0; g < edgeReverse; g++) {

            if (nonDirectedGraphM[w][g] != 0)
                for (j = 0; j < vertices; j++)
                    if (j != w && nonDirectedGraphM[j][g] != 0 && !visited[j]) {
                        edge.wp = w;
                        edge.wk = j;
                        edge.weight = KO[g].weight;
                        queue.push(edge);

                    }
        }
        do {
            edge = queue.top();
            queue.pop();

        } while (visited[edge.wk]);

       // tree->addEdge(edge);
        visited[edge.wk] = true;
        w = edge.wk;

    }
    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    cout << "Minimalne drzewo rozpinające:";
    //tree->show();
    //delete tree;
}

void Graph::list_Prim() {
    int w, i;
    Time time;
    Edge k;
    priority_queue<Edge, vector<Edge>, Edge> queue;
    SpanningTree *tree = new SpanningTree(vertices, edge);
    visited = new bool[vertices];
    for (i = 0; i < vertices; i++) {
        visited[i] = false;
    }
    cout << endl << "Graf nieskierowany: " << endl << endl;
    for (i = 0; i < vertices; i++) {
        cout << "[" << i << "] =";
        e1 = nonDirectedGraphL[i];
        while (e1) {
            cout << setw(3) << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << endl;
    }
    cout << endl;
    time.TimeStart();
    w = 0;
    visited[w] = true;

    for (i = 1; i < vertices; i++) {

        for (e1 = nonDirectedGraphL[w]; e1; e1 = e1->next) {
            if (!visited[e1->w]) {
                k.wp = w;
                k.wk = e1->w;
                k.weight = e1->weight;
                queue.push(k);
            }
        }
        do {
            k = queue.top();
            queue.pop();

        } while (visited[k.wk]);

        tree->addEdge(k);
        visited[k.wk] = true;
        w = k.wk;

    }

    time.TimeEnd();
    cout << endl << "Czas: " << time.TimeExecution() << endl;
    cout << endl;
    cout << "Minimalne drzewo rozpinające:";
    tree->show();
    delete tree;
}

void Graph::show() {
    cout << "matrix incydencji:" << endl;
    int i;
    cout << "      ";
    for (i = 0; i < edge; i++) {
        cout << setw(3) << i;

    }

    cout << endl << "      ";
    for (i = 0; i < edge; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < vertices; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < edge; j++)
            cout << setw(3) << IncidenceMatrix[i][j];
        cout << endl;
    }
    cout << endl;
    cout << "Wagi: ";
    for (i = 0; i < edge; i++) {
        cout << setw(3) << K[i].weight;
    }

    cout << endl << endl << "Lista poprzedników i następników:" << endl;
    for (i = 0; i < vertices; i++) {
        cout << "[" << i << "] =";
        e1 = NeighborhoodList[i];
        while (e1) {
            cout << setw(3) << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << endl;
    }
}