#include "UserInterface.h"
#include <iostream>
using namespace std;

void UserInterface::ChoiceOfGraphGenerationMethod() {

    while (onStart) {
        cout << "Generowanie grafu:" << endl;
        cout << "1. Wygeneruj losowy graph programowo" << endl;
        cout  << "2. Wygeneruj graph z pliku" << endl;
        cin >> input;
        switch (input) {
            case 1: {
                RandomGraph();
                inputFunction();
            }
                break;
            case 2: {
                graphFromFile();
                inputFunction();
            }
                break;
        }
    }
}

void UserInterface::inputFunction() {
    while (!onStart) {

        cout << endl << "Analiza grafu za pomacą algorytmów:" << endl
             << "1. Wyświetl macierz incydencji i reprezentację listową" << endl
             << "2. Algorytm DFS " << endl
             << "3. Algorytm Dijkstry" << endl
             << "4. Algorytm Prima" << endl
             << "5. Powrót do menu" << endl;
        cin >> input;
        switch (input) {
            case 1: {
                graph->show();
                cout << endl;
            }
                break;
            case 2: {
                while (true) {
                    cout << "Zdefiniuj wierzchołek początkowy: ";
                    cin >> b;
                    if (b < graph->vertices) break;
                    else cout << "Graf nie zawiera wierzchołka o tym numerze." << endl;
                }

                while (true) {
                    int checkRepresentation;
                    cout << "Jakiej reprezentacji użyć w algorytmie?" << endl << "1. Macierz Incydecji" << endl
                         << "2. Lista poprzedników i następników" << endl;
                    cin >> checkRepresentation;
                    if (checkRepresentation == 1) {
                        graph->array_DFS(b);
                        break;
                    } else if (checkRepresentation == 2) {
                        graph->list_DFS(b);
                        break;
                    }
                }
            }
                break;

            case 3: {
                while (true) {
                    cout << "Zdefiniuj wierzchołek początkowy: ";
                    cin >> b;
                    if (b < graph->vertices) break;
                    else cout << "Podaj prawidlowy numer wierzcholka!" << endl;
                }

                while (true) {
                    int checkRepresentation;
                    cout << "Jakiej reprezentacji użyć w algorytmie?" << endl << "1. Macierz Incydecji" << endl
                         << "2. Lista poprzedników i następników" << endl;
                    cin >> checkRepresentation;
                    if (checkRepresentation == 1) {
                        graph->array_Dijkstra(b);
                        break;
                    } else if (checkRepresentation == 2) {
                        graph->list_Dijkstra(b);
                        break;
                    }
                }
            }
                break;


            case 4: {
                while (true) {
                    int checkRepresentation;
                    cout << "Jakiej reprezentacji użyć w algorytmie?" << endl << "1. Macierz Incydecji" << endl
                         << "2. Lista poprzedników i następników" << endl;
                    cin >> checkRepresentation;
                    if (checkRepresentation == 1) {
                        graph->array_Prim();
                        break;
                    } else if (checkRepresentation == 2) {
                        graph->list_Prim();
                        break;
                    }
                }

            }
                break;

            case 5: {
                delete graph;
                onStart = true;
            }
                break;
        }
    }
}

void UserInterface::RandomGraph() {
    onStart = false;
    while (true) {
        cout << "Zdefiniuj ilość wierzchołków grafu: ";
        cin >> w;
        if (w > 1) break;
        else cout << "Liczba wierzchołków nie może być mniejsza lub równa 1." << endl;
    }


    int maxK = w * (w - 1);
    double minG = ceil((((double) w - 1) * 100) / (double) maxK);

    while (true) {

        cout << "Zdefiniuj gęstość grafu (minimum " << minG << "%): ";
        cin >> g;
        if (g < minG || g > 100)
            cout << "Podana gęstość nie pozwala na stworzenie grafu." << endl;
        else
            break;
    }
    double edge = ceil((maxK * g) / 100);
    graph = new Graph(w, edge);
    graph->randomGraph();
}

void UserInterface::graphFromFile() {
    onStart = false;
    ElementsList *e1;
    string s, name;
    int a = 0;
    int edge, vertices;
    cout << "Nazwa pliku bez .txt: ";
    cin >> name;
    name = name + ".txt";
    ifstream plik(name);
    if (!plik) {
        cout << "Nie udało się otworzyć pliku, spróbuj ponownie." << endl;
        onStart = true;

    } else {

        {
            plik >> edge >> vertices;
            if (!plik || edge < vertices - 1 || vertices <= 1 ||
                edge > (vertices * (vertices - 1))) {
                cout << "File error! Ops!" << endl;

                onStart = true;
            } else {
                graph = new Graph(vertices, edge);
                while (!plik.eof()) {

                    plik >> graph->K[a].wp >> graph->K[a].wk >> graph->K[a].weight;
                    if (graph->K[a].wp >= vertices || graph->K[a].wk >= vertices ||
                        graph->K[a].weight < 1) {
                        cout << "Krawędzie w pliku są nieprawidłowo określone." << endl;
                        onStart = true;
                        break;
                    }

                    if (plik) {
                        a++;
                    } else {
                        cout << "Krawędzie w pliku są nieprawidłowo określone." << endl;
                        onStart = true;
                        break;
                    }
                }
                if (a == edge) {
                    for (int i = 0; i < vertices; i++)
                        graph->IncidenceMatrix[i] = new int[edge];
                    for (int i = 0; i < vertices; i++)
                        for (int j = 0; j < edge; j++) {
                            graph->IncidenceMatrix[i][j] = 0;
                        }

                    for (int i = 0; i < vertices; i++)
                        graph->NeighborhoodList[i] = NULL;

                    for (int i = 0; i < edge; i++) {
                        int wp = graph->K[i].wp;
                        int wk = graph->K[i].wk;
                        e1 = new ElementsList;
                        e1->w = wk;
                        e1->weight = graph->K[i].weight;
                        e1->next = graph->NeighborhoodList[wp];
                        graph->NeighborhoodList[wp] = e1;
                        graph->IncidenceMatrix[wp][i] = 1;
                        graph->IncidenceMatrix[wk][i] = -1;
                    }
                    plik.close();
                    graph->replaceToNonDirectedGraph();
                    if (!(graph->checkCohesion())) {
                        cout << "Zawarty w pliku graph jest niespójny, nie można wykonać algorytmów!" << endl;
                        onStart = true;
                        delete graph;
                    } else {
                        inputFunction();
                    }

                } else if (!onStart) {
                    onStart = true;
                    cout << "W pliku brakuje danych dotyczących krawędzi grafu." << endl;
                }
            }
        }
    }
}