#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define MAX_VOLUMEN 1001
#define MAX_ELEMENTOS 500
#define CANT_CARACTERES_ASCII 255
#define LARGO_VEC 10

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno(){
    pila_t* pila = pila_crear();

    //----------------------PRUEBA CREAR PILA------------------------------------
    print_test("La pila fue creada exitosamente", pila != NULL);
    print_test("La pila está vacía inicialmente", pila_esta_vacia(pila));
    print_test("La pila no tiene tope inicialmente", pila_ver_tope(pila) == NULL);
    print_test("No se puede desapilar una pila vacia", pila_desapilar(pila) == NULL);


    //----------------------PRUEBA DE VOLUMEN-------------------------------------
    int vector_enteros[MAX_ELEMENTOS];
    char vector_caracteres[MAX_ELEMENTOS];
    void* valor_prueba;
    void* n1 = NULL;
    bool ok = true;

    //Lleno el vector con enteros
    for (int i = 0; i < MAX_ELEMENTOS; i++){
        vector_enteros[i] = i;
    }

    //Lleno el vector con cadenas
    for (int i = 0; i < MAX_ELEMENTOS; i++){
        vector_caracteres[i] = (char)(i % CANT_CARACTERES_ASCII);
    }

    //Apilo los elementos de vector_enteros y de vector_caracteres
    //Valido en todo momento que el tope sea igual al valor agregado
    //Esto confirma que el invariante aumenta
    ok = true;
    for (int i = 0; ok && i < MAX_ELEMENTOS * 2; i++){    

        if (i < MAX_ELEMENTOS){
            pila_apilar(pila,&vector_enteros[i]);
            valor_prueba = pila_ver_tope(pila);
            ok = valor_prueba == &vector_enteros[i];
            continue;
        }

        pila_apilar(pila,&vector_caracteres[i]);
        valor_prueba = pila_ver_tope(pila);
        ok = valor_prueba == &vector_caracteres[i];
    }

    print_test("¿Guardó correctamente los valores?",ok);

    //Apilo NULL en la pila
    print_test("¿Apila correctamente NULL1?", pila_apilar(pila,&n1));

    //Desapilo todos valores
    //Esto confirma que el invariante disminuye
    while (!pila_esta_vacia(pila)){
        pila_desapilar(pila);
    }

    //Compruebo que la pila quede vacía
    //Compruebo que no tenga tope
    print_test("La pila esta vacia nuevamente", pila_esta_vacia(pila));
    print_test("La pila no tiene tope", pila_ver_tope(pila) == NULL);

//-------------------------------------------------------------------------

    int vector_enteros2[] = {0,-1,2,5,-29,100,7,20,-150,50};
    char vector_caracteres2[] = "riverplate";

    //Apilo vector_enteros2
    for (int i = 0; i < LARGO_VEC; i++){
        pila_apilar(pila,&vector_enteros2[i]);
    }

    //Apilo vector_caracteres2
    for (int i = 0; i < LARGO_VEC; i++){
        pila_apilar(pila,&vector_caracteres2[i]);
    }

    // Desapilo y comparo si coinciden con los valores uno por uno

    int i = 0;
    ok = true;
    while (ok && !pila_esta_vacia(pila)){
        i++;
        valor_prueba = pila_ver_tope(pila);
        pila_desapilar(pila);
        if(i <= LARGO_VEC){
            ok = valor_prueba == &vector_caracteres2[LARGO_VEC - i];
            continue;
        }
        ok = valor_prueba == &vector_enteros2[2*LARGO_VEC - i];
    }
    
    print_test("Desapiló correctamente", ok);
    print_test("La pila esta vacia nuevamente", pila_esta_vacia(pila));
    print_test("Si desapilo devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("La pila no tiene tope", pila_ver_tope(pila) == NULL);

    //Valido liberar la memoria
    pila_destruir(pila);
    print_test("La pila fue destruida", true);
}