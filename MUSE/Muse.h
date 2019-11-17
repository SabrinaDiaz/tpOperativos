/*
 * Muse.h
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#ifndef MUSE_H_
#define MUSE_H_

#include "Contexto_muse.h"
#include "Herramientas_muse.h"
#include "Manejo_conexiones_y_seg_pag.h"

void atender_muse_init(int, int);
void atender_muse_close(int, int);
void atender_muse_alloc(int, int);
void atender_muse_free(int, int);
void atender_muse_get(int, int);
void atender_muse_cpy(int, int);
void atender_muse_map(int, int);
void atender_muse_sync(int, int);
void atender_muse_unmap(int, int);
void recibir_un_mensaje_char(int, int);
void decidir_que_hacer_con_el_cliente(int, t_header);
char* reservar_UPCM();
void inicializar_server_multihilo(int);
void * escuchar_mensajes_entrantes(int);

#endif /* MUSE_H_ */
