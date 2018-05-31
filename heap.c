#include "heap.h"
#include <stdlib.h>

#define POSICION_DEL_MAX 0
#define CANTIDAD_INICIAL 0
#define CAPACIDAD_INICIAL 24
#define REDIMENSIONADOR 2
#define TAMANIO_RELATIVO 4

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
	int comparacion = cmp(arreglo[pos],arreglo[padre]);
	if(comparacion < 0)return;
	_swap(arreglo[pos],arreglo[padre]);
	_upheap(arreglo,padre,cmp);
}
void _downheap(void *arreglo[],size_t n ,size_t pos ,cmp_func_t cmp){// n creo es donde termina el arreglo
	if(pos >= n) return;
	size_t  pos_hijo_izq =  2*pos+1;
	size_t  pos_hijo_der =  2*pos+1;
	size_t  pos_max = pos;
	if(pos_hijo_izq < n && cmp(arreglo[pos_hijo_izq],arreglo[pos_max])>0){
		pos_max = pos_hijo_izq;
	}
	if(pos_hijo_der < n && cmp(arreglo[pos_hijo_der],arreglo[pos_max])>0){
		pos_max = pos_hijo_der;
	}
	if(pos != pos_max){
		_swap(arreglo[pos],arreglo[pos_max]);
		_downheap(arreglo,n,pos_max,cmp);
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
	size_t pos_act = 0;
	while(pos_act < n){
		if(!heap_encolar(heap,arreglo[pos_act]))return NULL;
	}
	return heap;
}
bool _redimenzinar_heap(heap_t *heap, size_t tam_nuevo){
	void** tabla_nueva = realloc (heap->tabla, tam_nuevo*sizeof(void*));
	if(!tam_nuevo) return false;
	heap->tabla = tabla_nueva;
	heap->capacidad = tam_nuevo;
	return true;

}
bool heap_encolar(heap_t *heap, void *elem){
	if(heap->cantidad == heap->capacidad){
		size_t tam_nuevo = heap->capacidad * REDIMENSIONADOR;
		if(!_redimenzinar_heap(heap,tam_nuevo)){
			return false;
		}
	}
	heap->tabla[heap->cantidad]= elem;
	_upheap(heap->tabla,heap->cantidad,heap->cmp);
	heap->cantidad++;
	return true;
}
size_t heap_cantidad(const heap_t *heap){
	return(heap->cantidad);
}
bool heap_esta_vacio(const heap_t *heap){
	if(heap->cantidad == 0)return true;
	return false;
}
void *heap_ver_max(const heap_t *heap){
	if(!heap)return NULL;
	if(heap->cantidad == 0)return NULL;
	return(heap->tabla[POSICION_DEL_MAX]);
}
void *heap_desencolar(heap_t *heap){
	if(!heap) return NULL;
	if(heap->cantidad == 0 )return NULL;
	if(heap->cantidad < heap->capacidad/TAMANIO_RELATIVO && CAPACIDAD_INICIAL < heap->cantidad){
		size_t tam_nuevo = heap->capacidad/REDIMENSIONADOR;
		if(!_redimenzinar_heap(heap,tam_nuevo)){
			return false;
		}
	}
	void* elem = heap->tabla[POSICION_DEL_MAX];
	
	size_t pos_ultimo_elemento = heap->cantidad-1;
	_swap(heap->tabla[POSICION_DEL_MAX],heap->tabla[pos_ultimo_elemento]);
	heap->tabla[pos_ultimo_elemento] = NULL;
	-- heap->cantidad;
	-- pos_ultimo_elemento; 
	_downheap(heap->tabla,pos_ultimo_elemento,POSICION_DEL_MAX,heap->cmp);
	
	return elem;
}
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while(!heap_esta_vacio(heap)){
		void* elem = heap_desencolar(heap);
		if(destruir_elemento){
			destruir_elemento(elem);
		}
	}
	free(heap->tabla);
    free(heap);
}

