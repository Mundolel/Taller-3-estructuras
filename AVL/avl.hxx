#ifndef ARBOLAVL_HXX
#define ARBOLAVL_HXX

#include "arbolAVL.h"
using namespace std;

template<typename T>
arbolAVL<T>::arbolAVL() : raiz(NULL) {}
template<typename T>
arbolAVL<T>::~arbolAVL() { limpiar(); }

// Limpiamos todo el árbol
template<typename T>
void arbolAVL<T>::limpiar() {
    limpiarRec(raiz);
    raiz = NULL;
}

// Recorremos y liberamos nodos
template<typename T>
void arbolAVL<T>::limpiarRec(Nodo* actual) {
    if (actual == NULL) return;
    limpiarRec(actual->izq);
    limpiarRec(actual->der);
    delete actual;
}

// Obtenemos la altura de un nodo
template<typename T>
int arbolAVL<T>::alturaDe(Nodo* actual) const {
    if (actual == NULL) return 0;
    return actual->altura;
}

// Actualizamos la altura después de insertar o eliminar
template<typename T>
void arbolAVL<T>::actualizarAltura(Nodo* actual) {
    if (actual == NULL) return;
    int hIzq = alturaDe(actual->izq);
    int hDer = alturaDe(actual->der);
    if (hIzq > hDer){
        actual->altura = hIzq + 1;
    }
    else{
        actual->altura = hDer + 1;
    }
}

// Calculamos el factor de balance
template<typename T>
int arbolAVL<T>::factorBalance(Nodo* actual) const {
    if (actual == NULL) return 0;
    return alturaDe(actual->izq) - alturaDe(actual->der);
}

template<typename T>
// Realizamos una rotación simple a la derecha
typename arbolAVL<T>::Nodo* arbolAVL<T>::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;

    x->der = y;
    y->izq = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

// Realizamos una rotación simple a la izquierda
template<typename T>
typename arbolAVL<T>::Nodo* arbolAVL<T>::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

// Insertamos una clave en el AVL y balanceamos si es necesario
template<typename T>
bool arbolAVL<T>::insert(const T& clave) {
    bool cambiado = false;
    raiz = insertarRec(raiz, clave, cambiado);
    return cambiado;
}

template<typename T>
typename arbolAVL<T>::Nodo* arbolAVL<T>::insertarRec(Nodo* actual, const T& clave, bool& cambiado) {
    if (actual == NULL) {
        cambiado = true;
        return new Nodo(clave);
    }
    if (clave < actual->clave) {
        actual->izq = insertarRec(actual->izq, clave, cambiado);
    } else if (clave > actual->clave) {
        actual->der = insertarRec(actual->der, clave, cambiado);
    } else {
        return actual; // ya existe
    }

    actualizarAltura(actual);
    int bf = factorBalance(actual);

    // Revisamos y aplicamos rotaciones
    if (bf > 1 && clave < actual->izq->clave) return rotacionDerecha(actual); 
    if (bf < -1 && clave > actual->der->clave) return rotacionIzquierda(actual); 
    if (bf > 1 && clave > actual->izq->clave) { 
        actual->izq = rotacionIzquierda(actual->izq);
        return rotacionDerecha(actual);
    }
    if (bf < -1 && clave < actual->der->clave) { 
        actual->der = rotacionDerecha(actual->der);
        return rotacionIzquierda(actual);
    }

    return actual;
}

// Verificamos si una clave está en el árbol
template<typename T>
bool arbolAVL<T>::contiene(const T& clave) const {
    return contieneRec(raiz, clave);
}

template<typename T>
bool arbolAVL<T>::contieneRec(Nodo* actual, const T& clave) const {
    if (actual == NULL) return false;
    if (clave < actual->clave) return contieneRec(actual->izq, clave);
    if (clave > actual->clave) return contieneRec(actual->der, clave);
    return true;
}

// Buscamos el nodo mínimo
template<typename T>
typename arbolAVL<T>::Nodo* arbolAVL<T>::nodoMinimo(Nodo* actual) const {
    Nodo* p = actual;
    while (p != NULL && p->izq != NULL) p = p->izq;
    return p;
}

// Eliminamos una clave y balanceamos si es necesario
template<typename T>
bool arbolAVL<T>::erase(const T& clave) {
    bool cambiado = false;
    raiz = eliminarRec(raiz, clave, cambiado);
    return cambiado;
}

template<typename T>
typename arbolAVL<T>::Nodo* arbolAVL<T>::eliminarRec(Nodo* actual, const T& clave, bool& cambiado) {
    if (actual == NULL) {
        cambiado = false;
        return actual;
    }

    if (clave < actual->clave) {
        actual->izq = eliminarRec(actual->izq, clave, cambiado);
    } else if (clave > actual->clave) {
        actual->der = eliminarRec(actual->der, clave, cambiado);
    } else {
        cambiado = true;
        if (actual->izq == NULL || actual->der == NULL) { 
            Nodo* tmp = actual->izq ? actual->izq : actual->der;
            if (tmp == NULL) {
                delete actual;
                actual = NULL;
            } else {
                *actual = *tmp;
                delete tmp;
            }
        } else {
            Nodo* sucesor = nodoMinimo(actual->der);
            actual->clave = sucesor->clave;
            actual->der = eliminarRec(actual->der, sucesor->clave, cambiado);
        }
    }

    if (actual == NULL) return actual;

    actualizarAltura(actual);
    int bf = factorBalance(actual);

    // Rebalanceamos tras eliminar
    if (bf > 1 && factorBalance(actual->izq) >= 0) return rotacionDerecha(actual); 
    if (bf > 1 && factorBalance(actual->izq) < 0) { 
        actual->izq = rotacionIzquierda(actual->izq);
        return rotacionDerecha(actual);
    }
    if (bf < -1 && factorBalance(actual->der) <= 0) return rotacionIzquierda(actual); 
    if (bf < -1 && factorBalance(actual->der) > 0) { 
        actual->der = rotacionDerecha(actual->der);
        return rotacionIzquierda(actual);
    }

    return actual;
}

// Recorremos en inorden y guardamos las claves
template<typename T>
void arbolAVL<T>::inordenEnLista(list<T>& salida) const {
    salida.clear();
    inordenRec(raiz, salida);
}

template<typename T>
void arbolAVL<T>::inordenRec(Nodo* actual, list<T>& salida) const {
    if (actual == NULL) return;
    inordenRec(actual->izq, salida);
    salida.push_back(actual->clave);
    inordenRec(actual->der, salida);
}

#endif 