#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 5000
#define TAM_ARREGLO 10

int cmp_str(const void* a, const void* b){

	return strcmp(a, b);
}

int cmp_int(const void* A, const void* B){

	const int* a = A, *b = B;

	if(*a < *b) return -1;
	if(*a > *b) return 1;

	return 0;
}

void prueba_heap_vacio() {

 	printf("~~~ PRUEBA HEAP VACIO ~~~\n" );
 	heap_t* heap = heap_crear(NULL);

 	print_test("Se creó heap", heap != NULL);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    print_test("Heap cantidad es 0", heap_cantidad(heap) == 0);
    print_test("heap_desencolar devuelve NULL",heap_desencolar(heap) == NULL);
    print_test("heap_ver_max devuelve NULL", heap_ver_max(heap) == NULL);
    heap_destruir(heap,NULL);
    print_test("heap fue destruido",true);
}

void prueba_heap_1_elemento(){

	printf("\n~~~ PRUEBA HEAP 1 ELEMENTO ~~~\n");

	heap_t* heap = heap_crear(cmp_str);

	char* palabra = "Hola mundo";

	print_test("Se encoló palabra", heap_encolar(heap, palabra));
	print_test("Ver max es palabra", heap_ver_max(heap) == palabra);
	print_test("Heap cantidad es 1", heap_cantidad(heap) == 1);
	print_test("Se desencoló palabra", heap_desencolar(heap) == palabra);
	print_test("Heap está vacio", heap_esta_vacio(heap));

	heap_destruir(heap, NULL);

	printf("\n~~~ PRUEBA HEAP 1 ELEMENTO (DYNAMIC)\n");

	heap = heap_crear(cmp_str);

	char* palabra2 = malloc(10*sizeof(char));

	print_test("Se encoló palabra2", heap_encolar(heap, palabra2));
	print_test("Ver max es palabra", heap_ver_max(heap) == palabra2);
	print_test("Heap cantidad es 1", heap_cantidad(heap) == 1);

	heap_destruir(heap, free);
}

void pruebas_heap_5_elementos(){
	printf("\n~~~ PRUEBAS 5 elemento ~~~\n" );
 	heap_t* heap = heap_crear(cmp_str);
 	char* elem1 = "Arg";
	char* elem2 = "Bra";
	char* elem3 = "Ale";
	char* elem4 = "Nig";
	char* elem5 = "Jap";

	print_test("Se encoló elem1",heap_encolar(heap,elem1));
	print_test("heap_cantidad es 1", heap_cantidad(heap) == 1);
	print_test("Se encoló elem2",heap_encolar(heap,elem2));
	print_test("heap_cantidad es 2", heap_cantidad(heap) == 2);
	print_test("Se encoló elem3",heap_encolar(heap,elem3));
	print_test("heap_cantidad es 3", heap_cantidad(heap) == 3);
	print_test("Se encoló elem4",heap_encolar(heap,elem4));
	print_test("heap_cantidad es 4", heap_cantidad(heap) == 4);
	print_test("Se encoló elem5",heap_encolar(heap,elem5));
	print_test("heap_cantidad es 5", heap_cantidad(heap) == 5);

	print_test("elem4 es maximo", heap_ver_max(heap) == elem4);
	print_test("Se desencoló elem4", heap_desencolar(heap) == elem4);
	print_test("heap_cantidad es 4", heap_cantidad(heap) == 4);
	print_test("elem5 es maximo", heap_ver_max(heap) == elem5);
	print_test("Se desencoló elem5", heap_desencolar(heap) == elem5);
	print_test("heap_cantidad es 3", heap_cantidad(heap) == 3);
	print_test("elem2 es maximo", heap_ver_max(heap) == elem2);
	print_test("Se desencoló elem2", heap_desencolar(heap) == elem2);
	print_test("heap_cantidad es 2", heap_cantidad(heap) == 2);
	print_test("elem1 es maximo", heap_ver_max(heap) == elem1);
	print_test("Se desencoló elem1", heap_desencolar(heap) == elem1);
	print_test("heap_cantidad es 1", heap_cantidad(heap) == 1);
	print_test("elem3 es maximo", heap_ver_max(heap) == elem3);
	print_test("Se desencoló elem3", heap_desencolar(heap) == elem3);
	print_test("Heap está vacio", heap_esta_vacio(heap));

	heap_destruir(heap,NULL);
}
/*
void prueba_heap_sort(){

	printf("\n");

	void** numeros;

	int num = 1, num2 = 4, num3 = 2, num4 = 100, num5 = 92, num6 = 22, num7 = 7, num8 = 80, num9 = 0, num10 = 42;

	numeros[0] = &num;
	numeros[1] = &num2;
	numeros[2] = &num3;
	numeros[3] = &num4;
	numeros[4] = &num5;
	numeros[5] = &num6;
	numeros[6] = &num7;
	numeros[7] = &num8;
	numeros[8] = &num9;
	numeros[9] = &num10;

	heap_sort(numeros, 10, cmp_int);

	for(size_t i = 0; i < 10; i++){
		printf("| %d |", numeros[i]);
	}

	printf("\n");
}
*/
void prueba_heap_volumen(){

	printf("\n~~~ PRUEBA HEAP VOLUMEN~~~\n");

	heap_t* heap = heap_crear(cmp_int);

	int numeros[TAM], tope = TAM;

	for(int i = 0; i < tope; i++) numeros[i] = i;

	for(size_t i = 0; i < tope; i++){
		if(!heap_encolar(heap, &numeros[i])){
			print_test("NO se pudieron encolar los elementos", false);
			break;
		}
		if(!(heap_ver_max(heap) == &numeros[i])){
			print_test("NO es el maximo", false);
			break;
		}
		if(heap_cantidad(heap) != i+1){
			print_test("heap_cantidad en volumen", false);
			break;
		}
	}

	print_test("Se pudieron encolar los elementos", true);
	print_test("heap_cantidad en volumen (5000)", heap_cantidad(heap) == tope);

	for(size_t i = tope; i > 0; i--){
		if(!(heap_ver_max(heap) == &numeros[i-1])){
			print_test("NO es el maximo", false);
			break;
		}
		if(!(heap_desencolar(heap) == &numeros[i-1])){
			print_test("NO se pudieron desencolar los elementos", false);
			break;
		}
		if(!(heap_cantidad(heap) == i-1)){
			print_test("heap_cantidad en volumen", false);
			break;
		}
	}

	print_test("Se desencolaron todos los elementos", heap_cantidad(heap) == 0);
	print_test("Heap está vacio", heap_esta_vacio(heap));

	heap_destruir(heap, NULL);
}

void prueba_heap_crear_arreglo(){

	printf("\n~~~ PRUEBA HEAP CREAR ARREGLO ~~~\n");

	void* arreglo[TAM_ARREGLO];

	arreglo[0] = "Argentina";
	arreglo[1] = "Uruguay";
	arreglo[2] = "Paraguay";
	arreglo[3] = "Peru";
	arreglo[4] = "Brasil";
	arreglo[5] = "Mexico";
	arreglo[6] = "Cuba";
	arreglo[7] = "Colombia";
	arreglo[8] = "Venezuela";
	arreglo[9] = "Nicaragua";

	heap_t* heap = heap_crear_arr(arreglo, TAM_ARREGLO, cmp_str);

	print_test("Se creó heap", heap != NULL);

	print_test("Heap ver maximo (Venezuela)", heap_ver_max(heap) == arreglo[8]);
	print_test("Se desencoló (Venezuela)", heap_desencolar(heap) == arreglo[8]);
	print_test("Heap ver maximo (Uruguay)", heap_ver_max(heap) == arreglo[1]);

	char* extra = "Yugoslavia";

	print_test("Se encoló extra", heap_encolar(heap, extra));
	print_test("Heap ver maximo (Yugoslavia)", heap_ver_max(heap) == extra);

	heap_destruir(heap, NULL);
}

void pruebas_heap_alumno(){
	prueba_heap_vacio();
	prueba_heap_1_elemento();
	pruebas_heap_5_elementos();
//	prueba_heap_sort();
	prueba_heap_volumen();
	prueba_heap_crear_arreglo();
}