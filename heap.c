#include "heap.h"
#include <stdlib.h>

#define CANTIDAD_INICIAL 0
#define CAPACIDAD_INICIAL 50
//hujo izquierdo = 2*pos+1
//hijo derecho = 2*pos+2
//padre = (pos -1 )/2
// ult padre = (largo/2)-1
struct heap{
	void** tabla;
	cmp_func_t cmp;
	size_t cantidad;
	size_t capacidad;
};
void _swap(void* arreglo1,void* arreglo2){
	void* aux = arreglo1;
	arreglo1 = arreglo2;
	arreglo2 = aux;
}
void _upheap(void *arreglo[],size_t pos ,cmp_func_t cmp){
	if(pos == 0) return;
	size_t padre = (pos-1)/2;
	int comparacion cmp(arreglo[pos],arreglo[padre]);
	if(comparacion < 0)return;
	_swap(arreglo[pos],arreglo[padre]);
	_upheap(arreglo,padre,cmp);
}
void _downheap(void *arreglo[],size_t n ,size_t pos ,cmp_func_t cmp){// n creo es donde termina el arreglo
	if(pos >= n) return;
	size_t = pos_hijo_izq =  2*pos+1;
	size_t = pos_hijo_der =  2*pos+1;
	size_t = pos_max = pos;
	if(pos_hijo_izq < n && cmp(arreglo[pos_hijo_izq],arreglo[pos_max])){
		pos_max = pos_hijo_izq;
	}
	if(pos_hijo_der < n && cmp(arreglo[pos_hijo_der],arreglo[pos_max])){
		pos_max = pos_hijo_der;
	}
}
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














