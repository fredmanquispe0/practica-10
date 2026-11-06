#pragma once
#include <memory>
#include <algorithm>
#include <string>

template<typename K, typename V = K>
struct NodoBST {
    K  clave; V valor;
    std::unique_ptr<NodoBST> izq, der;
    int altura;
    explicit NodoBST(K k, V v=V{})
        : clave(std::move(k)), valor(std::move(v)),
          izq(nullptr), der(nullptr), altura(1) {}
};

template<typename K,typename V>
int altura(const std::unique_ptr<NodoBST<K,V>>& n)
    { return n ? n->altura : 0; }

template<typename K,typename V>
int factor_balance(const std::unique_ptr<NodoBST<K,V>>& n)
    { return n ? altura(n->der)-altura(n->izq) : 0; }

template<typename K,typename V>
void actualizar_altura(std::unique_ptr<NodoBST<K,V>>& n)
    { if(n) n->altura=1+std::max(altura(n->izq),altura(n->der)); }

template<typename K,typename V>
void rotar_derecha(std::unique_ptr<NodoBST<K,V>>& z) {
    auto y = std::move(z->izq);
    z->izq = std::move(y->der);
    actualizar_altura(z);
    y->der = std::move(z);
    actualizar_altura(y);
    z = std::move(y);
}

template<typename K,typename V>
void rotar_izquierda(std::unique_ptr<NodoBST<K,V>>& z) {
    auto y = std::move(z->der);
    z->der = std::move(y->izq);
    actualizar_altura(z);
    y->izq = std::move(z);
    actualizar_altura(y);
    z = std::move(y);
}

template<typename K,typename V>
void balancear(std::unique_ptr<NodoBST<K,V>>& n) {
    actualizar_altura(n);
    int fb = factor_balance(n);
    if (fb == -2) {
        if (factor_balance(n->izq) > 0)
            rotar_izquierda(n->izq);
        rotar_derecha(n);
    } else if (fb == 2) {
        if (factor_balance(n->der) < 0)
            rotar_derecha(n->der);
        rotar_izquierda(n);
    }
}

template<typename K,typename V>
void insertar_avl(std::unique_ptr<NodoBST<K,V>>& raiz,
                  K clave, V valor=V{}) {
    if (!raiz) {
        raiz = std::make_unique<NodoBST<K,V>>(clave, valor);
        return;
    }
    if (clave < raiz->clave)
        insertar_avl(raiz->izq, clave, valor);
    else if (clave > raiz->clave)
        insertar_avl(raiz->der, clave, valor);
    else
        return;
    balancear(raiz);
}

template<typename K,typename V>
NodoBST<K,V>* buscar(const std::unique_ptr<NodoBST<K,V>>& raiz,
                     const K& clave) {
    if (!raiz) return nullptr;
    if (clave==raiz->clave) return raiz.get();
    if (clave<raiz->clave) return buscar(raiz->izq,clave);
    return buscar(raiz->der,clave);
}

template<typename K,typename V>
NodoBST<K,V>* minimo(const std::unique_ptr<NodoBST<K,V>>& n) {
    return n->izq ? minimo(n->izq) : n.get();
}

template<typename K,typename V>
void eliminar_avl(std::unique_ptr<NodoBST<K,V>>& raiz,
                  const K& clave) {
    if (!raiz) return;
    if (clave < raiz->clave)
        eliminar_avl(raiz->izq, clave);
    else if (clave > raiz->clave)
        eliminar_avl(raiz->der, clave);
    else {
        if (!raiz->izq && !raiz->der)
            raiz = nullptr;
        else if (!raiz->izq)
            raiz = std::move(raiz->der);
        else if (!raiz->der)
            raiz = std::move(raiz->izq);
        else {
            NodoBST<K,V>* sucesor = minimo(raiz->der);
            raiz->clave = sucesor->clave;
            raiz->valor = sucesor->valor;
            eliminar_avl(raiz->der, raiz->clave);
        }
    }
    if (raiz) balancear(raiz);
}
