/*
 * Contexto.h
 *
 *  Created on: 17 nov. 2019
 *      Author: utnso
 */

#ifndef CONTEXTO_H_
#define CONTEXTO_H_

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
#include<string.h>
#include <fcntl.h>
#include <errno.h>
#include <Functions.h>

struct conexion_cliente {
	int pid;
	int socket;
	struct sockaddr_in direccion;
};
typedef struct conexion_cliente t_conexion_cliente;

/* Keys config file*/
#define KEY_CONFIG_LISTEN_PORT "LISTEN_PORT"
#define KEY_CONFIG_METRICS_TIMER "METRICS_TIMER"
#define KEY_CONFIG_MAX_MULTIPROG "MAX_MULTIPROG"
#define KEY_CONFIG_SEM_IDS "SEM_IDS"
#define KEY_CONFIG_SEM_INIT "SEM_INIT"
#define KEY_CONFIG_SEM_MAX "SEM_MAX"
#define KEY_CONFIG_ALPHA_SJF "ALPHA SJF"
#define MAX_CLIENTES 20
#define NO_SOCKET -1


extern int listen_port;
extern int metrics_timer;
extern int max_multiprog;
extern char** sem_ids;
extern char** sem_init;
extern char** sem_max;
extern char* alpha_sjf;


extern t_log* suse_logger;
extern t_config* config;
extern t_conexion_cliente conexiones_clientes[MAX_CLIENTES];

#endif /* CONTEXTO_H_ */
