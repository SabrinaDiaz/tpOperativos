/*
 * Contexto.c
 *
 *  Created on: 17 nov. 2019
 *      Author: utnso
 */

#include "Contexto.h"

/* Global variables*/
int listen_port;
int metrics_timer;
int max_multiprog;
char** sem_ids;
char** sem_init;
char** sem_max;
char* alpha_sjf;

t_log* suse_logger;
t_config* config;
t_conexion_cliente conexiones_clientes[MAX_CLIENTES];


