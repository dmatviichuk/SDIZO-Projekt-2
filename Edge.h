#ifndef SDIZO_PROJEKT_2_EDGE_H
#define SDIZO_PROJEKT_2_EDGE_H

class Edge {
public:
    int wk, wp, weight;

    bool operator()(const Edge &k1, const Edge &k2) {
        if (k1.weight > k2.weight) return true;
        if (k1.weight < k2.weight) return false;
        return false;
    }
};




#endif //SDIZO_PROJEKT_2_EDGE_H
