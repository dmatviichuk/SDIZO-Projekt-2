#ifndef SDIZO_PROJEKT_2_USERINTERFACE_H
#define SDIZO_PROJEKT_2_USERINTERFACE_H

#include <fstream>
#include <math.h>
#include <iomanip>
#include <queue>
#include "Edge.h"
#include "Stack.h"
#include "Graph.h"

class UserInterface {
public:
    Graph *graph;
    bool onStart = true;
    int input, w, g, b;
    void ChoiceOfGraphGenerationMethod();
    void RandomGraph();
    void inputFunction();
    void graphFromFile();
};

#endif //SDIZO_PROJEKT_2_USERINTERFACE_H
