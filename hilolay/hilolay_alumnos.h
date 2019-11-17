#ifndef hilolay_alumnos_h__
#define hilolay_alumnos_h__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <commons/log.h>
#include <Functions.h>
#include <signal.h>
#include "hilolay.h"

int sock;

	/**
	 * TODO: Interface for alumnos (what they should implement in orde to make this work)
	 * Interfaz para alumnos (qué deben implementar en orden para que esto funcione)
	 */
typedef struct hilolay_operations {
		int (*suse_create) (int);
		int (*suse_schedule_next) (void);
		int (*suse_join) (int);
		int (*suse_close) (int);
		 //suse_wait
	     //suse_signal
	} hilolay_operations;

	hilolay_operations *main_ops;


void init_internal(struct hilolay_operations*);

#endif // hilolay_alumnos_h__
