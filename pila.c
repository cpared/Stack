#include "pila.h"
#include <stdlib.h>

#define CANT_INICIAL 0
#define CAPACIDAD_INICIAL 10
#define CANT_AMPLIAR_MEMORIA 2
#define CANT_REDUCE_MEMORIA 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }

    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = CANT_INICIAL; 

    pila->datos = malloc(pila->capacidad * sizeof(pila->datos));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == CANT_INICIAL;
}

//------------------------PRIMITIVAS AUXILIARES----------------------------



bool redimensionar(pila_t *pila){
    void* datos_nuevos;
    size_t valor_redimension;

    if (pila->cantidad < pila->capacidad){
        valor_redimension = pila->capacidad / CANT_REDUCE_MEMORIA;
    }
    else {
        valor_redimension = pila->capacidad * CANT_AMPLIAR_MEMORIA;
    }

    datos_nuevos = realloc(pila->datos, valor_redimension * sizeof(pila->datos));

    if (datos_nuevos == NULL){
        return false;
    }
    
    pila->capacidad = valor_redimension;
    pila->datos = datos_nuevos;
    return true;
}

//---------------------------------------------------------------------

bool pila_apilar(pila_t *pila, void* valor){
    if (pila->cantidad == pila->capacidad && !redimensionar(pila)){
        return false;
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad ++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }

    if (pila->cantidad <= (pila->capacidad / CANT_REDUCE_MEMORIA) && !redimensionar(pila)){
        return false;
    }

    void* p_valor = pila->datos[pila->cantidad -1];
    pila->cantidad --; 
    return p_valor;
}
