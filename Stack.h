#ifndef SDIZO_PROJEKT_2_STACK_H
#define SDIZO_PROJEKT_2_STACK_H

#include "ElementsList.h"

class Stack {

private:
    ElementsList *s;

public:
    Stack();
    ~Stack();
    bool empty();
    int top();
    void pop();
    void push(int w);
};


#endif //SDIZO_PROJEKT_2_STACK_H
