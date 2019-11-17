/*
 * Manejo_conexiones_y_seg_pag.h
 *
 *  Created on: 6 oct. 2019
 *      Author: utnso
 */

#ifndef MANEJO_CONEXIONES_Y_SEG_PAG_H_
#define MANEJO_CONEXIONES_Y_SEG_PAG_H_

#include "Contexto_muse.h"

void agregar_cliente_a_lista_de_clientes_conectados();
void eliminar_cliente_de_lista_de_clientes_conectados();
void inicializar_listas_de_muse();
int obtener_tamanio_marco();
int obtener_cantidad_marcos_en_MP(int);
void liberar_bitmap_marcos();
void inicializar_bitmap_marcos();
int obtener_marco_libre_del_bitmap();
void ocupar_marco_en_el_bitmap(int);
void inicializar_tabla_segmentos();

#endif /* MANEJO_CONEXIONES_Y_SEG_PAG_H_ */
