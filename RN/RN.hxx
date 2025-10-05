#ifndef ARBOLRN_HXX
#define ARBOLRN_HXX

using namespace std;

template<typename T>
void arbolRN<T>::insert(const T& v) {
    arbol.insert(v);
}

template<typename T>
void arbolRN<T>::erase(const T& v) {
    arbol.erase(v);
}

template<typename T>
void arbolRN<T>::inordenEnLista(list<T>& ordenado) {
    typename set<T>::const_iterator it=arbol.begin();
    for (; it != arbol.end(); ++it) {
        ordenado.push_back(*it);
    }
}

#endif