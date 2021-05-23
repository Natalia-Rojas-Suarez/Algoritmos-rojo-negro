#ifndef _Arbol_hpp
#define _Arbol_hpp

#include <iostream>
using namespace std;

struct Nodo {
  int dato;
  Nodo *padre;
  Nodo *izquierdo;
  Nodo *derecho;
  int color;
};

typedef Nodo *NodoP;

class ArbolNegroRojo {
  private:
    NodoP raiz;
    NodoP Null;

    // Balancear arbol despues de la eliminacion
    void eliminarArreglar(NodoP x);
    void nrTransplantar(NodoP u, NodoP v);
    void eliminar(NodoP nodo, int key);

    //Balancear el arbol despues de la insercion
    void balancear(NodoP k);
    void imprimir(NodoP root, string indent, bool last);

  public:
    ArbolNegroRojo();
    NodoP minimo(NodoP nodo);
    void rotarIzquierda(NodoP x);
    void rotarDerecha(NodoP x);

    // Insercion de un nodo
    void insertar(int numero);
    void eliminarNodo(int data);
    void imprimirArbol();
};

#endif
