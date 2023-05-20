#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Atleta {
    string nombre;
    int numero;
    double promedio_tiempo;
};

struct ArbolNodo {

    Atleta atleta;
    int altura;
    ArbolNodo* izquierda;
    ArbolNodo* derecha;

    ArbolNodo(const Atleta& atleta) : atleta(atleta), altura(1), izquierda(nullptr), derecha(nullptr) {}
};

int altura(ArbolNodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

int balance(ArbolNodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

ArbolNodo* rotar_derecha(ArbolNodo* y) {
    ArbolNodo* x = y->izquierda;
    ArbolNodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

ArbolNodo* rotar_izquierda(ArbolNodo* x) {
    ArbolNodo* y = x->derecha;
    ArbolNodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

ArbolNodo* insertar(ArbolNodo* nodo, const Atleta& atleta) {
    if (nodo == NULL) {
        return new ArbolNodo(atleta);
    }

    if (atleta.promedio_tiempo < nodo->atleta.promedio_tiempo) {
        nodo->izquierda = insertar(nodo->izquierda, atleta);
    } else {
        nodo->derecha = insertar(nodo->derecha, atleta);
    }

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;

    int balance_factor = balance(nodo);

    if (balance_factor > 1) {
        if (atleta.promedio_tiempo < nodo->izquierda->atleta.promedio_tiempo) {
            return rotar_derecha(nodo);
        } else {
            nodo->izquierda = rotar_izquierda(nodo->izquierda);
            return rotar_derecha(nodo);
        }
    }

    if (balance_factor < -1) {
        if (atleta.promedio_tiempo > nodo->derecha->atleta.promedio_tiempo) {
            return rotar_izquierda(nodo);
        } else {
            nodo->derecha = rotar_derecha(nodo->derecha);
            return rotar_izquierda(nodo);
        }
    }

    return nodo;
}

void recorrer_enorden(ArbolNodo* nodo) {
    if (nodo == NULL) {
        return;
    }
    recorrer_enorden(nodo->izquierda);
    cout << "Nombre: " << nodo->atleta.nombre << ", Numero: " << nodo->atleta.numero
         << ", Promedio de tiempo: " << nodo->atleta.promedio_tiempo << endl;
    recorrer_enorden(nodo->derecha);
}

int main() {
    ArbolNodo* raiz = NULL;
    int opcion, numero_vueltas;
    double tiempo, promedio_tiempo;
    Atleta atleta;

    while (true) {
        cout << "*******REGISTRO DE ATLETAS*******\n\n";
        cout << "1. Ingresar atleta\n2. Mostrar atletas ordenados por promedio de tiempo\n3. Salir\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del atleta: ";
                cin, atleta.nombre;

                cout << "Numero del atleta: ";
                cin >> atleta.numero;

                cout << "Cantidad de vueltas del atleta: ";
                cin >> numero_vueltas;

                promedio_tiempo = 0;
                for (int i = 0; i < numero_vueltas; i++) {
                    cout << "Tiempo vuelta del atleta " << i + 1 << ": ";
                    cin >> tiempo;
                    promedio_tiempo += tiempo;
                }

                if (numero_vueltas >= 2) {
                    atleta.promedio_tiempo = promedio_tiempo / numero_vueltas;
                }

                raiz = insertar(raiz, atleta);
                cout << "\n ";
                break;

            case 2:
                recorrer_enorden(raiz);
                break;

            case 3:
                return 0;

            default:
                cout << "Opcion invalida, intenta nuevamente." << endl;
        }
    }

    return 0;
}
