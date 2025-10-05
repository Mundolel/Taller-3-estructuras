    #ifndef MONTICULO_HXX
    #define MONTICULO_HXX
    
    #include <algorithm>
    #include <deque>
    #include <list>
    #include <string>

    using namespace std;


    template<typename T>
    void monticulo<T>::insert(const T& v){
        typename deque<T>::iterator it = find(datos.begin(), datos.end(), v);
        //si no lo encontro retorna el apuntador al final del deque
        if(it ==datos.end()){
            datos.push_back(v);
            push_heap(datos.begin(), datos.end());
        }
    }

    template<typename T>
    void monticulo<T>:: erase(const T& v){
        typename deque<T>::iterator it = find(datos.begin(), datos.end(), v);
        //lo encontro, y lo elimina 
        if (it != datos.end()) {
            datos.erase(it);
            make_heap(datos.begin(), datos.end());
        }
    }

    template<typename T>
    void monticulo<T>::inordenEnLista(list<T>& ordenado){
        deque<T> copia = datos;
        make_heap(copia.begin(), copia.end());
        sort_heap(copia.begin(), copia.end()); 

        typename deque<T>::const_iterator it= copia.begin();
        for (; it != copia.end(); ++it) {
            ordenado.push_back(*it);
        }
    }

#endif