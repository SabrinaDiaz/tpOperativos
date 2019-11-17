/*
 * Manejo_conexiones_y_seg_pag.c
 *
 *  Created on: 6 oct. 2019
 *      Author: utnso
 */

#include "Manejo_conexiones_y_seg_pag.h"

void agregar_cliente_a_lista_de_clientes_conectados(){

}

void eliminar_cliente_de_lista_de_clientes_conectados(){

}

void inicializar_listas_de_muse(){

}

int obtener_tamanio_marco(){
	return page_size;
}

int obtener_cantidad_marcos_en_MP(int tamanio_marco){
	return memory_size/tamanio_marco;
}

void inicializar_bitmap_marcos(){
	int tamanio_bitmap = obtener_cantidad_marcos_en_MP(page_size);
	void * bits_bitmap = malloc(tamanio_bitmap);
	bitmap_marcos = bitarray_create_with_mode(bits_bitmap, tamanio_bitmap,  LSB_FIRST);
	for(int i=0;i<tamanio_bitmap;i++){
		bitarray_clean_bit(bitmap_marcos,i);
	}
}

void liberar_bitmap_marcos(){
	free(bitmap_marcos->bitarray);
	bitarray_destroy(bitmap_marcos);
}

int obtener_marco_libre_del_bitmap(){
	/* Retorna un numero de marco libre en el bitmap
	 * Si no hay mas marcos libres retorna -1 */
	int i;
	for(i=0;i<obtener_cantidad_marcos_en_MP(obtener_tamanio_marco());i++){
		if(!bitarray_test_bit(bitmap_marcos,i)){
			logger(escribir_loguear, l_trace,"El marco %d esta libre", i);
			return i;
		}
	}
	logger(escribir_loguear, l_warning,"No hay mas marcos libres");
	return -1;
}

void ocupar_marco_en_el_bitmap(int marco){
	bitarray_set_bit(bitmap_marcos,marco);
}

void inicializar_tabla_segmentos(){
	tabla_de_segmentos=list_create();
}

int devolver_rdo_de_dividir(int tam, int tamanio_de_un_marco){
	float div = tam/tamanio_de_un_marco;
	return ceil(div);
}

int chequear_cuantos_marcos_se_requieren(uint32_t tam){
	int tamanio_de_un_marco = obtener_tamanio_marco;
	if(tamanio_de_un_marco < (int)tam){
		int rdo = devolver_rdo_de_dividir((int)tam, tamanio_de_un_marco);
		return rdo;
	}else{
		return 1;
	}
}

t_entrada_tabla_segmentos * crear_segmento_heap(uint32_t tam){
	int cant_marcos_a_usar = chequear_cuantos_marcos_se_requieren(tam);
	for(int i; i<cant_marcos_a_usar;i++){
		//devolver los marcos
		//devolver la metadata??
	}
	//crear la tabla de paginas

}








