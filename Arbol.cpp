#include <iostream>
#include "Arbol.hpp"
using namespace std;


void ArbolNegroRojo::eliminarArreglar(NodoP x) {
  NodoP s;
  while (x != raiz && x->color == 0) {
    if (x == x->padre->izquierdo) {
      s = x->padre->derecho;
      if (s->color == 1) {
        s->color = 0;
        x->padre->color = 1;
        rotarIzquierda(x->padre);
        s = x->padre->derecho;
      }

      if (s->izquierdo->color == 0 && s->derecho->color == 0) {
        s->color = 1;
        x = x->padre;
      } else {
        if (s->derecho->color == 0) {
          s->izquierdo->color = 0;
          s->color = 1;
          rotarDerecha(s);
          s = x->padre->derecho;
        }

        s->color = x->padre->color;
        x->padre->color = 0;
        s->derecho->color = 0;
        rotarIzquierda(x->padre);
        x = raiz;
      }
    } else {
      s = x->padre->izquierdo;
      if (s->color == 1) {
        s->color = 0;
        x->padre->color = 1;
        rotarDerecha(x->padre);
        s = x->padre->izquierdo;
      }

      if (s->derecho->color == 0 && s->derecho->color == 0) {
        s->color = 1;
        x = x->padre;
      } else {
        if (s->izquierdo->color == 0) {
          s->derecho->color = 0;
          s->color = 1;
          rotarIzquierda(s);
          s = x->padre->izquierdo;
        }

        s->color = x->padre->color;
        x->padre->color = 0;
        s->izquierdo->color = 0;
        rotarDerecha(x->padre);
        x = raiz;
      }
    }
  }
  x->color = 0;
}


void ArbolNegroRojo::nrTransplantar(NodoP u, NodoP v) {
  if (u->padre == 0) {
    raiz = v;
  } else if (u == u->padre->izquierdo) {
    u->padre->izquierdo = v;
  } else {
    u->padre->derecho = v;
  }
  v->padre = u->padre;
}


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


void ArbolNegroRojo::rotarIzquierda(NodoP x) {
  NodoP y = x->derecho;
  x->derecho = y->izquierdo;
  if (y->izquierdo != Null) {
    y->izquierdo->padre = x;
  }
  y->padre = x->padre;
  if (x->padre == 0) {
    this->raiz = y;
  } else if (x == x->padre->izquierdo) {
    x->padre->izquierdo = y;
  } else {
    x->padre->derecho = y;
  }
  y->izquierdo = x;
  x->padre = y;
}


void ArbolNegroRojo::rotarDerecha(NodoP x) {
  NodoP y = x->izquierdo;
  x->izquierdo = y->derecho;
  if (y->derecho != Null) {
    y->derecho->padre = x;
  }
  y->padre = x->padre;
  if (x->padre == 0) {
    this->raiz = y;
  } else if (x == x->padre->derecho) {
    x->padre->derecho = y;
  } else {
    x->padre->izquierdo = y;
  }
  y->derecho = x;
  x->padre = y;
}


void ArbolNegroRojo::insertar(int numero) {
  NodoP nodo = new Nodo;
  nodo->padre = Null;
  nodo->dato = numero;
  nodo->izquierdo = Null;
  nodo->derecho = Null;
  nodo->color = 1;

  NodoP y = 0;
  NodoP x = this->raiz;

  while (x != Null) {
    y = x;
    if (nodo->dato < x->dato) {
      x = x->izquierdo;
    } else {
      x = x->derecho;
    }
  }

  nodo->padre = y;
  if (y == 0) {
    raiz = nodo;
  } else if (nodo->dato < y->dato) {
    y->izquierdo = nodo;
  } else {
    y->derecho = nodo;
  }

  if (nodo->padre == 0) {
    nodo->color = 0;
    return;
  }

  if (nodo->padre->padre == 0) {
    return;
  }

  balancear(nodo);
}


void ArbolNegroRojo::eliminarNodo(int data) {
  eliminar(this->raiz, data);
}


void ArbolNegroRojo::imprimirArbol() {
  if (raiz) {
    imprimir(this->raiz, "", true);
  }
}
