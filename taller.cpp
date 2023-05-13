#include <iostream>
#include <string>
using namespace std;

// Estructura de un nodo del árbol AVL
struct Nodo {
    string nombre;
    int numero;
    int vueltas;
    double tiempo_total;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

// Función para obtener la altura de un nodo
int altura(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

// Función para obtener el máximo de dos números
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Función para crear un nuevo nodo
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

// Función para rotar a la derecha un subárbol
Nodo* rotarDerecha(Nodo* nodo) {
    Nodo* nodo_izquierda = nodo->izquierda;
    Nodo* nodo_derecha = nodo_izquierda->derecha;

    nodo_izquierda->derecha = nodo;
    nodo->izquierda = nodo_derecha;

    nodo->altura = maximo(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodo_izquierda->altura = maximo(altura(nodo_izquierda->izquierda), altura(nodo_izquierda->derecha)) + 1;

    return nodo_izquierda;
}

// Función para rotar a la izquierda un subárbol
Nodo* rotarIzquierda(Nodo* nodo) {
    Nodo* nodo_derecha = nodo->derecha;
    Nodo* nodo_izquierda = nodo_derecha->izquierda;

    nodo_derecha->izquierda = nodo;
    nodo->derecha = nodo_izquierda;

    nodo->altura = maximo(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodo_derecha->altura = maximo(altura(nodo_derecha->izquierda), altura(nodo_derecha->derecha)) + 1;

    return nodo_derecha;
}

// Función para obtener la diferencia de altura entre los subárboles izquierdo y derecho de un nodo
int balance(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// Función para insertar un nuevo nodo en el árbol AVL
Nodo* insertar(Nodo* nodo, string nombre, int numero, int vueltas, double tiempo_total) {
    // Si el árbol está vacío, se crea un nuevo nodo
    if (nodo == NULL) {
        return nuevoNodo(nombre, numero, vueltas, tiempo_total);
    }

    // Se inserta el nodo en el subárbol izquierdo
    if (tiempo_total < nodo->tiempo_total) {
        nodo->izquierda = insertar(nodo->izquierda, nombre, numero, vueltas, tiempo_total);
    }

    // Se inserta el nodo en el subárbol derecho
    else if (tiempo_total > nodo->tiempo_total) {
        nodo->derecha = insertar(nodo->derecha, nombre, numero, vueltas, tiempo_total);
    }

    // Si los tiempos son iguales, se inserta el nodo en el subárbol izquierdo
    else {
        nodo->izquierda = insertar(nodo->izquierda, nombre, numero, vueltas, tiempo_total);
    }

    // Se actualiza la altura del nodo
    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));

    // Se verifica si el árbol está balanceado
    int factor_balance = balance(nodo);

    // Si el árbol está desbalanceado, se realizan las rotaciones necesarias
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

    // Se retorna el nodo
    return nodo;
}

// Función para recorrer el árbol en orden y mostrar los tiempos de menor a mayor
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

    // Se solicita el ingreso de los datos del atleta
    string nombre;
    int numero;
    int vueltas;
    double tiempo_total;
    char respuesta;

    do {
        cout << "Ingrese el nombre del atleta: ";
        cin >> nombre;
        cout << "Ingrese el numero del atleta: ";
        cin >> numero;
        cout << "Ingrese el numero de vueltas del atleta: ";
        cin >> vueltas;
        cout << "Ingrese el tiempo total del atleta: ";
        cin >> tiempo_total;

        // Se inserta el nodo en el árbol AVL
        raiz = insertar(raiz, nombre, numero, vueltas, tiempo_total);

        cout << "¿Desea ingresar otro atleta? (S/N): ";
        cin >> respuesta;
    } while (respuesta == 'S' || respuesta == 's');

    // Se recorre el árbol y se muestran los tiempos de menor a mayor
    recorrerArbol(raiz);

    return 0;
}