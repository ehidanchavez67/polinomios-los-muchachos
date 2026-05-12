#include "polinomio.h"

//Implementación de funciones

Polinomio* crearPolinomio() {
    Polinomio *p = (Polinomio*)malloc(sizeof(Polinomio));
    if(p==NULL) {
        printf("No se pudo reservar memoria para el polinomio xD\n");
        return NULL;
    }else{
        p->cabeza=NULL;
        p->cola=NULL;
        p->numTerminos=0;
    }
    return p;
}

void insertarTermino(Polinomio* p, float coeficiente, int exponente) {
    if (p == NULL) return;

    Nodo* actual = p->cabeza;

    while (actual != NULL) {
        if (actual->termino.exponente == exponente) {
            actual->termino.coeficiente += coeficiente;
            if (actual->termino.coeficiente == 0)
                eliminarTermino(p, exponente);
            return;
        }
        actual = actual->siguiente;
    }

    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevo == NULL) return;
    nuevo->termino.coeficiente = coeficiente;
    nuevo->termino.exponente   = exponente;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    p->numTerminos++;

    if (p->cabeza == NULL) {
        p->cabeza = nuevo;
        p->cola = nuevo;
        return;
    }

    if (exponente > p->cabeza->termino.exponente) {
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
        return;
    }

    actual = p->cabeza;
    while (actual->siguiente != NULL && actual->siguiente->termino.exponente > exponente) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    nuevo->anterior  = actual;

    if (actual->siguiente != NULL) {
        actual->siguiente->anterior = nuevo;
    }else{
        p->cola = nuevo;
    }
    actual->siguiente = nuevo;
}

void eliminarTermino(Polinomio* p, int exponente) {
    if (p == NULL || p->cabeza == NULL) return;

    Nodo* actual = p->cabeza;
    while (actual != NULL && actual->termino.exponente != exponente) {
        actual = actual->siguiente;
    }

    if (actual == NULL) return;

    if (actual->anterior != NULL) 
        actual->anterior->siguiente = actual->siguiente;
    else
        p->cabeza = actual->siguiente;

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = actual->anterior;
    else
        p->cola = actual->anterior;

    free(actual);
    p->numTerminos--;
}

float potencia(float base, int exp) {   // funcion que remplaza pow con la libreria math.h
    float resultado = 1.0;
    for (int i = 0; i < exp; i++)
        resultado *= base;
    return resultado;
}

float evaluacionPolinomio(Polinomio* p, float x) {
    if (p == NULL || p->cabeza == NULL) return 0.0f;

    float resultado = 0.0f;
    Nodo* actual = p->cabeza;

    while (actual != NULL) {
        resultado += actual->termino.coeficiente * potencia(x, actual->termino.exponente);
        actual = actual->siguiente;
    }

    return resultado;
}

Polinomio* sumaPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* resultado = crearPolinomio();
    if (resultado == NULL) return NULL;

    Nodo* actual = p1->cabeza;
    while (actual != NULL) {
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }

    actual = p2->cabeza;
    while (actual != NULL) {
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }

    return resultado;
}

Polinomio* multiplicacionPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* resultado = crearPolinomio();
    if (resultado == NULL) return NULL;

    Nodo* nodo1 = p1->cabeza;
    while (nodo1 != NULL) {
        Nodo* nodo2 = p2->cabeza;
        while (nodo2 != NULL) {
            insertarTermino(resultado, nodo1->termino.coeficiente *nodo2->termino.coeficiente, nodo1->termino.exponente  + nodo2->termino.exponente);
            nodo2 = nodo2->siguiente;
        }
        nodo1 = nodo1->siguiente;
    }

    return resultado;
}

void mostrarPolinomio(Polinomio* p) {
    if (p == NULL || p->cabeza == NULL) {
        printf("0\n");
        return;
    }

    Nodo* actual = p->cabeza;
    int primero = 1;

    while (actual != NULL) {
        float coef = actual->termino.coeficiente;
        int exp  = actual->termino.exponente;
        int esPositivo = (coef ==  1);
        int esNegativo = (coef == -1);

        if (!primero && coef > 0)
            printf("+");
        primero = 0;

        if (exp == 0) {
            printf("%.g", coef);
        } else if (exp == 1) {
            
            if(esPositivo) printf("x");
            else if (esNegativo) printf("-x");
            else printf("%.gx", coef);
        } else {

            if(esPositivo) printf("x^%d", exp);
            else if(esNegativo) printf("-x^%d", exp);
            else printf("%.gx^%d", coef, exp);
        }

        actual = actual->siguiente;
    }
    printf("\n");
}

char* polinomioACadena(Polinomio* p) {
    char* cadena = (char*) malloc(256);
    cadena[0] = '\0';

    if (p == NULL || p->cabeza == NULL) {
        strcat(cadena, "0");
        return cadena;
    }

    Nodo* actual = p->cabeza;
    int primero = 1;
    char temp[64];

    while (actual != NULL) {
        float coef = actual->termino.coeficiente;
        int exp = actual->termino.exponente;
        int esPositivo = (coef ==  1);
        int esNegativo = (coef == -1);

        if (!primero && coef > 0)
            strcat(cadena, "+");
        primero = 0;

        if (exp == 0) {
            sprintf(temp, "%.g", coef);
        } else if (exp == 1) {
            if(esPositivo) sprintf(temp, "x");
            else if (esNegativo) sprintf(temp, "-x");
            else sprintf(temp, "%.gx", coef);
        } else {
            if (esPositivo) sprintf(temp, "x^%d", exp);
            else if (esNegativo) sprintf(temp, "-x^%d", exp);
            else sprintf(temp, "%.gx^%d", coef, exp);
        }

        strcat(cadena, temp);
        actual = actual->siguiente;
    }

    return cadena;
}

// main.c - No habia archivo creado entonces se unio el polinomio.c el main.c

 int main() {

    printf("===CASO 1: Crear un polinomio vacio ===\n");
    Polinomio* p= crearPolinomio();
    printf("P: "); mostrarPolinomio(p);
    printf("Esperado: 0\n");

    printf("=== CASO 2: Suma de polinomios ===\n");
    Polinomio* p1 = crearPolinomio();
    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    Polinomio* p2 = crearPolinomio();
    insertarTermino(p2, 1, 2);
    insertarTermino(p2, 4, 0);

    printf("P1: "); mostrarPolinomio(p1);
    printf("P2: "); mostrarPolinomio(p2);

    Polinomio* suma = sumaPolinomios(p1, p2);
    printf("P1+P2: "); mostrarPolinomio(suma);
    printf("Esperado: 4x^2+2x+5\n");

    printf("\n=== CASO 3: Simplificacion ===\n");
    Polinomio* p3 = crearPolinomio();
    insertarTermino(p3,  3, 2);
    insertarTermino(p3, -3, 2);
    printf("Resultado: "); mostrarPolinomio(p3);
    printf("Esperado: 0\n");

    printf("\n=== CASO 4: Eliminacion de termino ===\n");
    Polinomio* p4 = crearPolinomio();
    insertarTermino(p4, 5, 3);
    insertarTermino(p4, 2, 1);
    insertarTermino(p4, 7, 0);
    printf("Antes: "); mostrarPolinomio(p4);
    eliminarTermino(p4, 1);
    printf("Despues: "); mostrarPolinomio(p4);
    printf("Esperado: 5x^3+7\n");

    printf("\n=== CASO 5: Multiplicacion ===\n");
    Polinomio* p5 = crearPolinomio();
    insertarTermino(p5, 1, 1);
    insertarTermino(p5, 1, 0);

    Polinomio* p6 = crearPolinomio();
    insertarTermino(p6,  1, 1);
    insertarTermino(p6, -1, 0);

    printf("P5: "); mostrarPolinomio(p5);
    printf("P6: "); mostrarPolinomio(p6);

    Polinomio* producto = multiplicacionPolinomios(p5, p6);
    printf("P5*P6: "); mostrarPolinomio(producto);
    printf("Esperado: x^2-1\n");

    printf("\n=== CASO 6: Evaluacion ===\n");
    Polinomio* p7 = crearPolinomio();
    insertarTermino(p7, 3, 2);
    insertarTermino(p7, 2, 1);
    insertarTermino(p7, 1, 0);
    printf("P7: "); mostrarPolinomio(p7);
    printf("P7(2) = %.2f\n", evaluacionPolinomio(p7, 2));
    printf("Esperado: 17\n");
    printf("\n");

    printf("=== Caso 7: Conversión de polinomio a cadena ===\n");
    char* cadena = polinomioACadena(p1);
    printf("Cadena: %s\n", cadena);
    free(cadena);
    printf("\n");

    printf("=== Los muchachos completaron el proyecto exitosamente ===\n");
    printf("=== Ponganos 10 profa :( ===\n");

    return 0;
}
