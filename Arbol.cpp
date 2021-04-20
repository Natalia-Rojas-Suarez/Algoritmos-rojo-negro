#include <iostream>
#include "Arbol.hpp"
using namespace std;


/*void ArbolNegroRojo::eliminarArreglar(NodoP x) {
}*/


void ArbolNegroRojo::eliminar(NodoP nodo, int key) {
  NodoP z = Null;
  NodoP x, y;
  while (nodo != Null) {
    if (nodo->dato == key) {
      z = nodo;
    }

    if (nodo->dato <= key) {
      nodo = nodo->derecho;
    } else {
      nodo = nodo->izquierdo;
    }
  }

  if (z == Null) {
    cout << "Dato no encontrado" << endl;
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->izquierdo == Null) {
    x = z->derecho;
    nrTransplantar(z, z->derecho);
  } else if (z->derecho == Null) {
    x = z->izquierdo;
    nrTransplantar(z, z->izquierdo);
  } else {
    y = minimo(z->derecho);
    y_original_color = y->color;
    x = y->derecho;
    if (y->padre == z) {
      x->padre = y;
    } else {
      nrTransplantar(y, y->derecho);
      y->derecho = z->derecho;
      y->derecho->padre = y;
    }

    nrTransplantar(z, y);
    y->izquierdo = z->izquierdo;
    y->izquierdo->padre = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0) {
    eliminarArreglar(x);
  }
}


void ArbolNegroRojo::balancear(NodoP k) {
  NodoP u;
  while (k->padre->color == 1) {
    if (k->padre == k->padre->padre->derecho) {
      u = k->padre->padre->izquierdo;
      if (u->color == 1) {
        u->color = 0;
        k->padre->color = 0;
        k->padre->padre->color = 1;
        k = k->padre->padre;
      } else {
        if (k == k->padre->izquierdo) {
          k = k->padre;
          rotarDerecha(k);
        }
        k->padre->color = 0;
        k->padre->padre->color = 1;
        rotarIzquierda(k->padre->padre);
      }
    } else {
      u = k->padre->padre->derecho;

      if (u->color == 1) {
        u->color = 0;
        k->padre->color = 0;
        k->padre->padre->color = 1;
        k = k->padre->padre;
      } else {
        if (k == k->padre->derecho) {
          k = k->padre;
          rotarIzquierda(k);
        }
        k->padre->color = 0;
        k->padre->padre->color = 1;
        rotarDerecha(k->padre->padre);
      }
    }
    if (k == raiz) {
      break;
    }
  }
  raiz->color = 0;
}


void ArbolNegroRojo::imprimir(NodoP root, string indent, bool last) {
  if (root != Null) {
    cout << indent;
    if (last) {
      cout << "Derecha------";
      indent += "   ";
    } else {
      cout << "Izquierda----";
      indent += "|  ";
    }

    string sColor = root->color ? "ROJO" : "NEGRO";
    cout << root->dato << "(" << sColor << ")" << endl;
    imprimir(root->izquierdo, indent, false);
    imprimir(root->derecho, indent, true);
  }
}


ArbolNegroRojo::ArbolNegroRojo() {
  Null = new Nodo;
  Null->color = 0;
  Null->izquierdo = 0;
  Null->derecho = 0;
  raiz = Null;
}


NodoP ArbolNegroRojo::minimo(NodoP nodo) {
  while (nodo->izquierdo != Null) {
    nodo = nodo->izquierdo;
  }
  return nodo;
}


/*void ArbolNegroRojo::rotarIzquierda(NodoP x) {
}*/


/*void ArbolNegroRojo::rotarDerecha(NodoP x) {
}*/


/*void ArbolNegroRojo::insertar(int numero) {
}*/


void ArbolNegroRojo::eliminarNodo(int data) {
  eliminar(this->raiz, data);
}


void ArbolNegroRojo::imprimirArbol() {
  if (raiz) {
    imprimir(this->raiz, "", true);
  }
}
