#ifndef __POLINOMIO_H__
#define __POLINOMIO_H__

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Termino {
    float coeficiente;
    int exponente;
} Term;

typedef struct Nodo {
    Term termino;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* cabeza;
    Nodo* cola;
    int numTerminos;
} Polinomio;

//Firmas de las funciones a emplear

Polinomio* crearPolinomio();
void insertarTermino(Polinomio *p, float coeficiente, int exponente);
void eliminarTermino(Polinomio *p, int exponente);
float evaluacionPolinomio(Polinomio *p, float x);
float potencia(float base, int exp);
Polinomio* sumaPolinomios(Polinomio *p1, Polinomio *p2);
Polinomio* multiplicacionPolinomios(Polinomio *p1, Polinomio *p2);
void mostrarPolinomio(Polinomio *p);
char* polinomioACadena(Polinomio* p);

#endif
