#include <iostream>
#include "Arbol.hpp"
using namespace std;

int main() {
  int opcion, dato;
  ArbolNegroRojo arbol;
  do{
    cout<<"MENU DE OPCIONES"<<endl;
    cout<<"1. Insertar datos en el arbol"<<endl;
    cout<<"2. Eliminar datos del arbol"<<endl;
    cout<<"3. Imprimir arbol"<<endl;
    cout<<"4. Salir"<<endl;
    cout<<"Digite una opcion: ";
    cin>>opcion;
    switch(opcion){
      case 1:
  		  cout<<"Inserte un dato"<<endl;
  		   cin>>dato;
  		   arbol.insertar(dato);
  		   system("pause");
  		   break;

      case 2:
  		   cout<<"Inserte numero a eliminar en el arbol"<<endl;
  		   cin>>dato;
  		   arbol.eliminarNodo(dato);
  		   system("pause");
  		   break;

  	   case 3:
  		   cout<<"ARBOL ROJO NEGRO"<<endl;
  		   arbol.imprimirArbol();
  	     system("pause");
  		   break;
    }
  }while(opcion!=4);
}
