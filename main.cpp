#include <iostream>
#include <ctime>
#include "UserInterface.h"

using namespace std;

int main() {
    srand(time(NULL));
    cout << "=======================================================================================================================" << endl
         << "===                                                                                                                 ===" << endl
         << "===                                                     Projekt-2                                                   ===" << endl
         << "===                                                    Dmytro Matviichuk 240545                                     ===" << endl
         << "===                                                                                                                 ===" << endl
         << "=======================================================================================================================" << endl << endl << endl;
    UserInterface ui;
    ui.ChoiceOfGraphGenerationMethod();
}