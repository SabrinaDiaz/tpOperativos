/*
 * Contexto_muse.h
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#ifndef CONTEXTO_MUSE_H_
#define CONTEXTO_MUSE_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<commons/log.h>
#include<signal.h>
#include<stdarg.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/config.h>
#include <commons/bitarray.h>
#include<string.h>
#include <fcntl.h>
#include <errno.h>
#include <Functions.h>


/* Keys config file*/
#define KEY_CONFIG_LISTEN_PORT "LISTEN_PORT"
#define KEY_CONFIG_MEMORY_SIZE "MEMORY_SIZE"
#define KEY_CONFIG_PAGE_SIZE "PAGE_SIZE"
#define KEY_CONFIG_SWAP_SIZE "SWAP_SIZE"


extern int listen_port;
extern int memory_size;
extern int page_size;
extern int swap_size;

extern t_log* muse_logger;
extern t_config* config;
extern char* UPCM;
extern t_list* clientes_conectados;
extern t_bitarray *bitmap_marcos=NULL;
extern t_list * tabla_de_segmentos;

struct entrada_tabla_segmentos{
	int base_logica;
	int tamanio; //limite
	t_list * tabla_de_paginas;
};
typedef struct entrada_tabla_segmentos t_entrada_tabla_segmentos;

struct entrada_tabla_paginas{
	int numero_de_pagina;
	int bit_de_presencia;
	int frame; //o posicion en SWAP
};
typedef struct entrada_tabla_paginas t_entrada_tabla_paginas;

struct heap_metadata{
	uint32_t size;
	bool esta_libre;
};
typedef struct heap_metadata t_heap_metadata;


#endif /* CONTEXTO_MUSE_H_ */
