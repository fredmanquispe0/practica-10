#include <iostream>
#include <cassert>
#include "avl.h"
using namespace std;

template<typename K,typename V>
int h(const unique_ptr<NodoBST<K,V>>& r) { return r?r->altura:0; }

void test_P1_insercion_simple() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    insertar_avl(r,10,10);
    insertar_avl(r,20,20);
    insertar_avl(r,30,30);
    assert(h(r)==2 && "P1: altura debe ser 2 tras rotacion RR");
    assert(r->clave==20 && "P1: raiz debe ser 20");
    cout << "[P1 OK] insercion_simple" << endl;
}

void test_P2_caso_LR() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    insertar_avl(r,30,30);
    insertar_avl(r,10,10);
    insertar_avl(r,20,20);
    assert(r->clave==20 && "P2: raiz debe ser 20");
    assert(h(r)==2 && "P2: altura debe ser 2");
    cout << "[P2 OK] caso_LR" << endl;
}

void test_P3_insercion_ordenada_grande() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    for(int i=1;i<=15;i++) insertar_avl(r,i,i);
    assert(h(r)<=4 && "P3: altura debe ser <= 4 para 15 nodos AVL");
    assert(buscar(r,8) && "P3: nodo 8 debe existir");
    cout << "[P3 OK] insercion_ordenada_grande h=" << h(r) << endl;
}

void test_P4_eliminar_hoja() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    for(int x:{20,10,30}) insertar_avl(r,x,x);
    eliminar_avl(r,10);
    assert(!buscar(r,10) && "P4: nodo 10 debe haberse eliminado");
    assert(h(r)<=2 && "P4: arbol sigue balanceado");
    cout << "[P4 OK] eliminar_hoja" << endl;
}

void test_P5_eliminar_raiz_dos_hijos() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    for(int x:{20,10,30,25,35}) insertar_avl(r,x,x);
    eliminar_avl(r,20);
    assert(!buscar(r,20) && "P5: nodo 20 eliminado");
    assert(h(r)<=3 && "P5: arbol sigue balanceado");
    cout << "[P5 OK] eliminar_raiz_dos_hijos" << endl;
}

void test_P6_eliminar_con_rebalanceo() {
    unique_ptr<NodoBST<int,int>> r=nullptr;
    for(int i=1;i<=7;i++) insertar_avl(r,i,i);
    int h_antes = h(r);
    eliminar_avl(r,1);
    assert(h(r)<=h_antes && "P6: altura no aumento tras eliminacion");
    cout << "[P6 OK] eliminar_con_rebalanceo" << endl;
}

int main() {
    test_P1_insercion_simple();
    test_P2_caso_LR();
    test_P3_insercion_ordenada_grande();
    test_P4_eliminar_hoja();
    test_P5_eliminar_raiz_dos_hijos();
    test_P6_eliminar_con_rebalanceo();
    cout << "=== Todos los casos P1-P6 pasaron ===" << endl;
    return 0;
}
