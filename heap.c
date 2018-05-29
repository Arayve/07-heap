#include "heap.h"
#include <stdlib.h>

#define CANTIDAD_INICIAL 0
#define CAPACIDAD_INICIAL 50

struct heap{
	void** tabla;
	cmp_func_t cmp;
	size_t cantidad;
	size_t capacidad;
};
heap_t* heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->cantidad = CANTIDAD_INICIAL;
	heap->capacidad = CAPACIDAD_INICIAL;
	heap->cmp = cmp;
	heap->tabla = malloc((heap->capacidad)*sizeof(void*));
	if(!heap->tabla){
        free(heap);
        return NULL;
    }
    return heap;
}
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	if(!heap) return NULL;
	/*Falta agregar elemento del arreglo*/
	return heap;
}














