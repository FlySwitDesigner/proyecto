#include <iostream>
#include <string>
using namespace std;


struct Nodo {
    string nombre;
    int numero;
    int vueltas;
    double tiempo_total;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};


int altura(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}


int maximo(int a, int b) {
    return (a > b) ? a : b;
}


Nodo* nuevoNodo(string nombre, int numero, int vueltas, double tiempo_total) {
    Nodo* nodo = new Nodo();
    nodo->nombre = nombre;
    nodo->numero = numero;
    nodo->vueltas = vueltas;
    nodo->tiempo_total = tiempo_total;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    nodo->altura = 1;
    return nodo;
}


Nodo* rotarDerecha(Nodo* nodo) {
    Nodo* nodo_izquierda = nodo->izquierda;
    Nodo* nodo_derecha = nodo_izquierda->derecha;

    nodo_izquierda->derecha = nodo;
    nodo->izquierda = nodo_derecha;

    nodo->altura = maximo(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodo_izquierda->altura = maximo(altura(nodo_izquierda->izquierda), altura(nodo_izquierda->derecha)) + 1;

    return nodo_izquierda;
}


Nodo* rotarIzquierda(Nodo* nodo) {
    Nodo* nodo_derecha = nodo->derecha;
    Nodo* nodo_izquierda = nodo_derecha->izquierda;

    nodo_derecha->izquierda = nodo;
    nodo->derecha = nodo_izquierda;

    nodo->altura = maximo(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodo_derecha->altura = maximo(altura(nodo_derecha->izquierda), altura(nodo_derecha->derecha)) + 1;

    return nodo_derecha;
}


int balance(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}


Nodo* insertar(Nodo* nodo, string nombre, int numero, int vueltas, double tiempo_total) {

    if (nodo == NULL) {
        return nuevoNodo(nombre, numero, vueltas, tiempo_total);
    }


    if (tiempo_total < nodo->tiempo_total) {
        nodo->izquierda = insertar(nodo->izquierda, nombre, numero, vueltas, tiempo_total);
    }


    else if (tiempo_total > nodo->tiempo_total) {
        nodo->derecha = insertar(nodo->derecha, nombre, numero, vueltas, tiempo_total);
    }


    else {
        nodo->izquierda = insertar(nodo->izquierda, nombre, numero, vueltas, tiempo_total);
    }


    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));


    int factor_balance = balance(nodo);


    if (factor_balance > 1 && tiempo_total < nodo->izquierda->tiempo_total) {
        return rotarDerecha(nodo);
    }
    if (factor_balance < -1 && tiempo_total > nodo->derecha->tiempo_total) {
        return rotarIzquierda(nodo);
    }
    if (factor_balance > 1 && tiempo_total > nodo->izquierda->tiempo_total) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (factor_balance < -1 && tiempo_total < nodo->derecha->tiempo_total) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }


    return nodo;
}


void recorrerArbol(Nodo* nodo) {
    if (nodo != NULL) {
        recorrerArbol(nodo->izquierda);
        if (nodo->vueltas >= 2) {
            cout << "Nombre: " << nodo->nombre << ", Numero: " << nodo->numero << ", Tiempo promedio: " << nodo->tiempo_total / nodo->vueltas << endl;
        }
        recorrerArbol(nodo->derecha);
    }
}

int main() {
    Nodo* raiz = NULL;


    string nombre;
    int numero;
    int vueltas;
    double tiempo_total;
    char respuesta;
    int op;

    do {
        cout<<"1. REGISTRAR UN ATLETA"<<endl;
        cin>>op;
        switch(op){
            case 1: 
            
                    do{

                    cout<<"Registrar un atleta"<<endl;


                    cout << "Ingrese el nombre del atleta: ";
                    cin >> nombre;
                    cout << "Ingrese el numero del atleta: ";
                    cin >> numero;
                    cout << "Ingrese el numero de vueltas del atleta: ";
                    cin >> vueltas;
                    cout << "Ingrese el tiempo total del atleta: ";
                    cin >> tiempo_total;


                    raiz = insertar(raiz, nombre, numero, vueltas, tiempo_total);

                    cout << "¿Desea ingresar otro atleta? (S/N): ";
                    cin >> respuesta;


                    } while (respuesta == 'S' || respuesta == 's');
                    

        }


        
    } while (op<2);


    recorrerArbol(raiz);

    return 0;
}
