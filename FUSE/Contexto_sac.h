/*
 * Contexto_fuse.h
 *
 *  Created on: 19 sep. 2019
 *      Author: utnso
 */

#ifndef CONTEXTO_SAC_H_
#define CONTEXTO_SAC_H_

#include<string.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<signal.h>
#include<stdarg.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include "commons/config.h"
#include "/home/utnso/tp-2019-2c-The-PowerFuse-girls/Biblioteca_chicas_superpoderosas/Functions.h"

/* Key config file*/
#define KEY_CONFIG_LISTEN_PORT "LISTEN_PORT"

extern int listen_port;

extern t_log* fuse_logger;
extern t_config* config;


#endif /* CONTEXTO_SAC_H_ */
