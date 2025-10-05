#ifndef MONTICULO_H
#define MONTICULO_H

#include <algorithm>
#include <deque>
#include <list>
#include <string>

using namespace std;

template<typename T>
struct monticulo {
    private:
    deque<T> datos;

    public:
    void insert(const T& v);
    void erase(const T& v);
    void inordenEnLista(list<T>& ordenado);
};

#include "monticulo.hxx"

#endif
