#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <list>
using namespace std;


template<typename T>
class arbolAVL {
public:
    arbolAVL();
    ~arbolAVL();

    bool insert(const T& clave);
    bool erase(const T& clave);
    bool contiene(const T& clave) const;
    void inordenEnLista(list<T>& salida) const;
    void limpiar();

private:
    struct Nodo {
        T clave;
        int altura;
        Nodo* izq;
        Nodo* der;
        Nodo(const T& c) : clave(c), altura(1), izq(NULL), der(NULL) {}
    };

    Nodo* raiz;

    void limpiarRec(Nodo* actual);
    int alturaDe(Nodo* actual) const;
    int factorBalance(Nodo* actual) const;
    void actualizarAltura(Nodo* actual);

    typename arbolAVL<T>::Nodo* rotacionDerecha(Nodo* y);
    typename arbolAVL<T>::Nodo* rotacionIzquierda(Nodo* x);

    bool contieneRec(Nodo* actual, const T& clave) const;
    void inordenRec(Nodo* actual, list<T>& salida) const;

    typename arbolAVL<T>::Nodo* insertarRec(Nodo* actual, const T& clave, bool& cambiado);
    typename arbolAVL<T>::Nodo* eliminarRec(Nodo* actual, const T& clave, bool& cambiado);
    typename arbolAVL<T>::Nodo* nodoMinimo(Nodo* actual) const;
};

#include "arbolAVL.hxx" 

#endif
