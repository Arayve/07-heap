#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>

void pruebas_heap_0_elementos() {

 	printf("~~~ PRUEBAS 0 elemento ~~~\n" );
 	heap_t* heap = heap_crear(NULL);

 	print_test("Heap disntinto a NULL", heap != NULL);
    print_test("Heap debe estar vacia", heap_esta_vacio(heap));
    print_test("El puntero eliminado debe ser NULL",heap_desencolar(heap) == NULL);
    heap_destruir(heap,NULL);
    print_test("La Heap fue destruido",true);

}
void pruebas_heap_5_elementos(){
	printf("~~~ PRUEBAS 5 elemento ~~~\n" );
 	heap_t* heap = heap_crear(strcmp);
 	char* elem1 = "A";
	char* elem2 = "B";
	char* elem3 = "C";
	char* elem4 = "D";
	char* elem5 = "E";
	print_test("El Encolo elemento",heap_encolar(heap,elem1));
	print_test("El Encolo elemento",heap_encolar(heap,elem2));
	print_test("El Encolo elemento",heap_encolar(heap,elem3));
	print_test("El Encolo elemento",heap_encolar(heap,elem4));
	print_test("El Encolo elemento",heap_encolar(heap,elem5));
	print_test("El Desencolar , debe ser 5", heap_desencolar(heap) == elem5);
	heap_destruir(heap,NULL);
}

void pruebas_heap_alumno(){
	pruebas_heap_0_elementos();
	pruebas_heap_5_elementos();
}