#ifndef ARBOLRN_H
#define ARBOLRN_H

#include <set>
#include <list>
#include <string>

using namespace std;

template<typename T>
struct arbolRN {

  set<T> arbol;

  void insert(const T& v);
  void erase (const T& v);
  void inordenEnLista(list<T>& ordenado);
};

#include "arbolRN.hxx"

#endif 