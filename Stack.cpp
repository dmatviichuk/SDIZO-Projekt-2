#include <cstdio>
#include "Stack.h"

Stack::Stack() {
    s = NULL;
}

Stack::~Stack() {
    while (s) pop();
}

bool Stack::empty() {
    return !s;
}

int Stack::top() {
    return s->w;
}

void Stack::pop() {
    if (s) {
        ElementsList *e = s;
        s = s->next;
        delete e;
    }
}

void Stack::push(int w) {
    ElementsList *e = new ElementsList;
    e->w = w;
    e->next = s;
    s = e;
}