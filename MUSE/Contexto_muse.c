/*
 * Contexto_muse.c
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#include "Contexto_muse.h"

/* Global variables*/
int listen_port;
int memory_size;
int page_size;
int swap_size;

t_log* muse_logger;
t_config* config;
char* UPCM;
t_list* clientes_conectados;
t_bitarray *bitmap_marcos=NULL;
t_list * tabla_de_segmentos;
